#include "IForecastStrategy.h"
#include <cmath>
#include <memory>

class AdvancedForecast : public IForecastStrategy {
public:
    std::string name() const  { return "AdvancedForecast"; }

    ForecastResult forecast(const WeatherData& d)  {
        ForecastResult r;
        r.strategyName = name();
        r.usedDataDescription = 
            "temp=" + std::to_string(d.temperatureC) +
            ", hum=" + std::to_string(d.humidityPercent) +
            ", wind=" + std::to_string(d.windSpeedMps);

        // toy algorithm: weighted temperature adjusted by humidity & wind
        double adj = (100.0 - d.humidityPercent) * 0.02 + d.windSpeedMps * 0.05;
        double pred = d.temperatureC * 0.75 + (d.temperatureC + adj) * 0.25;
        // small smoothing
        r.predictedTemperatureC = std::round(pred * 10.0) / 10.0;
        return r;
    }

};
std::shared_ptr<IForecastStrategy> createAdvancedForecast() { return std::make_shared<AdvancedForecast>(); }

