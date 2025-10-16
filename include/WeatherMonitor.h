#pragma once
#include <memory>
#include <vector>
#include <mutex>
#include "IWeatherDataSource.h"
#include "IForecastStrategy.h"
#include "IWeatherListener.h"


class WeatherMonitor {
public:
    static WeatherMonitor& instance();

    void setDataSource(std::shared_ptr<IWeatherDataSource> src);
    void setStrategy(std::shared_ptr<IForecastStrategy> strat);
    void addListener(std::shared_ptr<IWeatherListener> listener);

    void updateData(); // fetch -> forecast -> notify

    ForecastResult getLastForecast();

private:
    WeatherMonitor() = default;
    ~WeatherMonitor() = default;
    WeatherMonitor(const WeatherMonitor&) = delete;
    WeatherMonitor& operator=(const WeatherMonitor&) = delete;

    std::shared_ptr<IWeatherDataSource> m_source;
    std::shared_ptr<IForecastStrategy> m_strategy;
    std::vector<std::shared_ptr<IWeatherListener>> listeners_;
    std::mutex m_mutex;
    ForecastResult m_lastForecast;
};
