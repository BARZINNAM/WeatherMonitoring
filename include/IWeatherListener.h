#pragma once
#include "WeatherData.h"

struct ForecastResult;

class IWeatherListener {
public:
    virtual ~IWeatherListener() = default;
    virtual void onWeatherDataUpdated(const WeatherData& d) = 0;
};
