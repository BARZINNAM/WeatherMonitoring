#include "IWeatherListener.h"
#include "WeatherData.h"
#include "IForecastStrategy.h"
#include "WeatherMonitor.h"
#include <iostream>
#include <memory>

class ConsoleLogger : public IWeatherListener {
public:
    void onWeatherDataUpdated(const WeatherData& d) override {
        auto forecast = WeatherMonitor::instance().getLastForecast();

        std::cout << "Strategy: " << forecast.strategyName << "\n";
        std::cout << "Data: temperature=" << d.temperatureC << "C, humidity=" << d.humidityPercent
                  << "%, windSpeed=" << d.windSpeedMps << "m/s\n";
        std::cout << "Forecast result: predictedTemperature=" << forecast.predictedTemperatureC << "C\n";
        std::cout << "---\n";
    }
};

std::shared_ptr<IWeatherListener> createConsoleLogger() { return std::make_shared<ConsoleLogger>(); }
