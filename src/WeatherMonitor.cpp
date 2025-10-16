#include "WeatherMonitor.h"
#include <iostream>

WeatherMonitor& WeatherMonitor::instance() {
    static WeatherMonitor inst;
    return inst;
}

void WeatherMonitor::setDataSource(std::shared_ptr<IWeatherDataSource> src) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_source = std::move(src);
}

void WeatherMonitor::setStrategy(std::shared_ptr<IForecastStrategy> strat) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_strategy = std::move(strat);
}

void WeatherMonitor::addListener(std::shared_ptr<IWeatherListener> listener) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_listeners.push_back(std::move(listener));
}

void WeatherMonitor::updateData() {
    std::shared_ptr<IWeatherDataSource> src;
    std::shared_ptr<IForecastStrategy> strat;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        src = m_source;
        strat = m_strategy;
    }
    if (!src) {
        std::cerr << "No data source set\n";
        return;
    }
    if (!strat) {
        std::cerr << "No forecast strategy set\n";
        return;
    }

    WeatherData data;
    data.temperatureC = src->getTemperature();
    data.humidityPercent = src->getHumidity();
    data.windSpeedMps = src->getWindSpeed();

    ForecastResult res = strat->forecast(data);

    {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_lastForecast = res;  // store latest forecast
    }

    // notify listeners
    std::vector<std::shared_ptr<IWeatherListener>> listenersCopy;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        listenersCopy = m_listeners;
    }
    for (auto &l : listenersCopy) {
        if (l) l->onWeatherDataUpdated(data);
    }
}

ForecastResult WeatherMonitor::getLastForecast() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_lastForecast;
}

