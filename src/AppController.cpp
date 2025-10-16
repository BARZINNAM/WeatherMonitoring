#include "AppController.h"
#include "IWeatherDataSource.h"
#include "IForecastStrategy.h"
#include "IWeatherListener.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>

// forward declarations for actual implementations from src/
std::shared_ptr<IWeatherDataSource> createLocalSensor(unsigned seed);
std::shared_ptr<IWeatherDataSource> createAPIClient();
std::shared_ptr<IForecastStrategy> createSimpleForecast();
std::shared_ptr<IForecastStrategy> createAdvancedForecast();
std::shared_ptr<IWeatherListener> createConsoleLogger();

AppController::AppController()
    : m_weatherMonitor(WeatherMonitor::instance()) {
    m_weatherMonitor.addListener(createConsoleLogger());
    m_weatherMonitor.setDataSource(createLocalSensor(123));
    m_weatherMonitor.setStrategy(createSimpleForecast());
}

void AppController::showMenu() {
    std::cout << "============================\n";
    std::cout << " Weather Monitor Main Menu \n";
    std::cout << "============================\n";
    std::cout << "1. Use LocalSensor (random)\n";
    std::cout << "2. Use APIClient (static data)\n";
    std::cout << "3. SimpleForecast\n";
    std::cout << "4. AdvancedForecast\n";
    std::cout << "5. Update data once\n";
    std::cout << "6. Auto update (5 iterations)\n";
    std::cout << "0. Exit\n";
    std::cout << "> ";
}

void AppController::handleChoice(int choice) {
    switch (choice) {
        case 1:
            m_weatherMonitor.setDataSource(createLocalSensor(42));
            std::cout << "Data source set to LocalSensor.\n";
            break;
        case 2:
            m_weatherMonitor.setDataSource(createAPIClient());
            std::cout << "Data source set to APIClient.\n";
            break;
        case 3:
            m_weatherMonitor.setStrategy(createSimpleForecast());
            std::cout << "Strategy set to SimpleForecast.\n";
            break;
        case 4:
            m_weatherMonitor.setStrategy(createAdvancedForecast());
            std::cout << "Strategy set to AdvancedForecast.\n";
            break;
        case 5:
            m_weatherMonitor.updateData();
            break;
        case 6:
            for (int i = 0; i < 5; ++i) {
                m_weatherMonitor.updateData();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}

void AppController::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        handleChoice(choice);
    }
}

// ---------------------------------------------------------------------------
// Factory passthroughs (connect AppController methods to global functions)
// ---------------------------------------------------------------------------

std::shared_ptr<IWeatherDataSource> AppController::createLocalSensor(unsigned seed) {
    return ::createLocalSensor(seed); // call the global one
}

std::shared_ptr<IWeatherDataSource> AppController::createAPIClient() {
    return ::createAPIClient();
}

std::shared_ptr<IForecastStrategy> AppController::createSimpleForecast() {
    return ::createSimpleForecast();
}

std::shared_ptr<IForecastStrategy> AppController::createAdvancedForecast() {
    return ::createAdvancedForecast();
}

std::shared_ptr<IWeatherListener> AppController::createConsoleLogger() {
    return ::createConsoleLogger();
}
