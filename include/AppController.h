#pragma once
#include "WeatherMonitor.h"
#include <memory>

class AppController {
public:
    AppController();

    void run();  // starts the interactive console app

private:
    void showMenu();
    void handleChoice(int choice);

    std::shared_ptr<IWeatherDataSource> createLocalSensor(unsigned seed = 0);
    std::shared_ptr<IWeatherDataSource> createAPIClient();
    std::shared_ptr<IForecastStrategy> createSimpleForecast();
    std::shared_ptr<IForecastStrategy> createAdvancedForecast();
    std::shared_ptr<IWeatherListener> createConsoleLogger();

    WeatherMonitor& m_weatherMonitor;
};
