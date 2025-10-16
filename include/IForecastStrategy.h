#pragma once
#include "WeatherData.h"
#include <string>
struct ForecastResult {
    std::string strategyName;
    std::string usedDataDescription; // e.g., "temp=..., hum=..."
    double predictedTemperatureC; // sample output
};
class IForecastStrategy {
public:
    virtual ~IForecastStrategy() = default;
    virtual ForecastResult forecast(const WeatherData& d) = 0;
    virtual std::string name() const = 0;
};
