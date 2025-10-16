#include "IWeatherDataSource.h"
#include "WeatherData.h"
#include <vector>
#include <memory>

class APIClient : public IWeatherDataSource {
public:
    APIClient() {
        // deterministic sample data useful for tests
        m_data = {
            {20.0, 50.0, 3.0},
            {21.5, 55.0, 2.5},
            {19.8, 60.0, 4.0}
        };
    }

    double getTemperature() override { 
        return next().temperatureC;
    }
    double getHumidity() override {
        return next().humidityPercent;
    }
    double getWindSpeed() override {
        return next().windSpeedMps;
    }

    std::string name() const override { return "APIClient"; }

    void setData(const std::vector<WeatherData>& v) { m_data = v; m_idx = 0; }

private:

    WeatherData next() 
    {
        if (m_data.empty()) return WeatherData{};
        WeatherData d = m_data[m_idx % m_data.size()];
        ++m_idx;
        return d;
    }
    // TODO m_data
    std::vector<WeatherData> m_data;
    size_t m_idx{0};
};

std::shared_ptr<IWeatherDataSource> createAPIClient() { return std::make_shared<APIClient>(); }
