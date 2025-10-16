#include "IWeatherDataSource.h"
#include "WeatherData.h"
#include <vector>
#include <memory>

class APIClient : public IWeatherDataSource {
public:
    APIClient() {
        // deterministic sample data useful for tests
        data_ = {
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

    void setData(const std::vector<WeatherData>& v) { data_ = v; idx_ = 0; }

private:

    WeatherData next() 
    {
        if (data_.empty()) return WeatherData{};
        WeatherData d = data_[idx_ % data_.size()];
        ++idx_;
        return d;
    }
    // TODO m_data
    std::vector<WeatherData> data_;
    size_t idx_{0};
};

std::shared_ptr<IWeatherDataSource> createAPIClient() { return std::make_shared<APIClient>(); }
