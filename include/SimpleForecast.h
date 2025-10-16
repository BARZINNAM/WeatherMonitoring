#include "IForecastStrategy.h"
#include <memory>
#include <string>
#include <vector>

class SimpleForecast : public IForecastStrategy {
public:
    std::string name() const override;

    ForecastResult forecast(const WeatherData& d) override;

private:
    std::vector<double> m_previousTemps;
};

