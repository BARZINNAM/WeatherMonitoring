#include "IWeatherDataSource.h"
#include "WeatherData.h"
#include <random>
#include <chrono>
#include <memory>

class LocalSensor : public IWeatherDataSource {
public:
    explicit LocalSensor(unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()): 
    eng_(seed), 
    tempDist_(10.0, 30.0), 
    humDist_(30.0, 90.0), 
    windDist_(0.0, 10.0) 
    {}

    double getTemperature() override {
        return tempDist_(eng_);
    }

    double getHumidity() override {
        return humDist_(eng_);
    }

    double getWindSpeed() override {
        return windDist_(eng_);
    }

    std::string name() const override { return "LocalSensor"; }

    void seed(unsigned s) { eng_.seed(s); }

private:

    std::mt19937 eng_;
    std::uniform_real_distribution<double> tempDist_;
    std::uniform_real_distribution<double> humDist_;
    std::uniform_real_distribution<double> windDist_;
};

// Factory helper
std::shared_ptr<IWeatherDataSource> createLocalSensor(unsigned seed) {
    if (seed==0) return std::make_shared<LocalSensor>();
    return std::make_shared<LocalSensor>(seed);
}
