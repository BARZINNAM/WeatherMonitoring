#include <gtest/gtest.h>
#include "IForecastStrategy.h"
#include "WeatherData.h"
#include "IWeatherListener.h"
#include "IWeatherDataSource.h"
#include "WeatherMonitor.h"

// forward factory functions
std::shared_ptr<IForecastStrategy> createSimpleForecast();
std::shared_ptr<IForecastStrategy> createAdvancedForecast();
std::shared_ptr<IWeatherDataSource> createAPIClient();
std::shared_ptr<IWeatherDataSource> createLocalSensor(unsigned seed);

// simple mock listener
class MockListener : public IWeatherListener {
public:
    void onWeatherDataUpdated(const WeatherData& d) override {
        called = true;
        lastData = d;
        // Retrieve latest forecast from WeatherMonitor
        lastResult = WeatherMonitor::instance().getLastForecast();
    }
    bool called{false};
    WeatherData lastData;
    ForecastResult lastResult;
};

// 1️- Test forecast strategies with different data
TEST(SimpleForecastTest, SimpleForecastProducesAverage) {
    auto strat = createSimpleForecast();
    WeatherData d1{20.0, 50.0, 2.0};
    WeatherData d2{30.0, 60.0, 2.0};
    auto res1 = strat->forecast(d1);
    auto res2 = strat->forecast(d2);

    EXPECT_NEAR(res1.predictedTemperatureC, 20.0, 1e-6);
    EXPECT_NEAR(res2.predictedTemperatureC, 25.0, 1e-6);
}

TEST(AdvancedForecastTest, AdvancedForecastVariesWithHumidity) {
    auto strat = createAdvancedForecast();
    WeatherData d1{20.0, 30.0, 2.0};
    WeatherData d2{20.0, 80.0, 2.0};
    auto r1 = strat->forecast(d1);
    auto r2 = strat->forecast(d2);
    EXPECT_NE(r1.predictedTemperatureC, r2.predictedTemperatureC);
}

// 2️- Test that WeatherMonitor notifies listeners
TEST(ObserverTest, ConsoleLoggerIsCalled) {
    // reuse ConsoleLogger and a deterministic source
    auto src = createLocalSensor(42);
    auto strat = createSimpleForecast();

    // small local WeatherMonitor (use the singleton)
    auto &wm = WeatherMonitor::instance();
    wm.setDataSource(src);
    wm.setStrategy(strat);

    auto listener = std::make_shared<MockListener>();
    wm.addListener(listener);
    wm.updateData();
    EXPECT_TRUE(listener->called);
}

// 3️- Singleton behavior
TEST(SingletonTest, OnlyOneInstanceExists) {
    WeatherMonitor &a = WeatherMonitor::instance();
    WeatherMonitor &b = WeatherMonitor::instance();
    EXPECT_EQ(&a, &b);
}

// 4️- Plugging in different data sources and strategies
TEST(IntegrationTest, SwitchingSourcesAndStrategiesWorks) {
    auto &wm = WeatherMonitor::instance();

    wm.setDataSource(createLocalSensor(100));
    wm.setStrategy(createSimpleForecast());
    wm.updateData();
    auto first = wm.getLastForecast();

    wm.setDataSource(createAPIClient());
    wm.setStrategy(createAdvancedForecast());
    wm.updateData();
    auto second = wm.getLastForecast();

    EXPECT_NE(first.strategyName, second.strategyName);
}

// (additional) Iterating over given WeatherData
TEST(APIClientTest, CyclesThroughData) {
    auto api = createAPIClient();
    auto t1 = api->getTemperature();
    auto t2 = api->getTemperature();
    auto t3 = api->getTemperature();
    auto t4 = api->getTemperature();
    // d4 should equal d1 (cycle)
    EXPECT_DOUBLE_EQ(t1, t4);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
