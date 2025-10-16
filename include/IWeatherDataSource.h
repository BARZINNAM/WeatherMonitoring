#pragma once
#include "WeatherData.h"


class IWeatherDataSource {
public:
    virtual ~IWeatherDataSource() = default;
    virtual double getTemperature() = 0;
    virtual double getHumidity() = 0;
    virtual double getWindSpeed() = 0;
    virtual std::string name() const = 0;
};
