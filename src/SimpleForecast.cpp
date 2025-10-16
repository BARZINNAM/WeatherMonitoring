#include "IForecastStrategy.h"
#include "SimpleForecast.h"
#include <memory>
#include <string>
#include <vector>
#include <numeric> // for std::accumulate


std::string SimpleForecast::name() const { return "SimpleForecast"; }

ForecastResult SimpleForecast::forecast(const WeatherData& d){

    m_previousTemps.push_back(d.temperatureC);
    double sum = std::accumulate(m_previousTemps.begin(), m_previousTemps.end(), 0.0);
    double avgTemp = sum / m_previousTemps.size();

    ForecastResult r;
    r.strategyName = name();
    r.usedDataDescription = 
        "temp=" + std::to_string(d.temperatureC) +
        ", hum=" + std::to_string(d.humidityPercent) +
        ", wind=" + std::to_string(d.windSpeedMps);
    r.predictedTemperatureC = avgTemp;
    return r;
    }


std::shared_ptr<IForecastStrategy> createSimpleForecast() { return std::make_shared<SimpleForecast>(); }
