cmake_minimum_required(VERSION 3.14)
project(WeatherMonitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# Add a library
add_library(WeatherMonitorLib
    src/AdvancedForecast.cpp
    src/APIClient.cpp
    src/ConsoleLogger.cpp
    src/LocalSensor.cpp
    src/SimpleForecast.cpp
    src/WeatherMonitor.cpp
    src/AppController.cpp
)

# Main app
add_executable(WeatherMonitor src/main.cpp)

target_link_libraries(WeatherMonitor 
    PRIVATE pthread
    WeatherMonitorLib)



# ---- Unit Testing ----
enable_testing()

# Add GoogleTest from local folder
add_subdirectory(Third-party/googletest)

include_directories(
    ${gtest_SOURCE_DIR}/include
   ${gmock_SOURCE_DIR}/include
)

add_executable(TestWeatherMonitoring 
    test/Test.cpp
)

target_link_libraries(TestWeatherMonitoring
    WeatherMonitorLib
    gmock
    gtest
    gtest_main
    pthread
)

add_test(NAME TestWeatherMonitoring COMMAND TestWeatherMonitoring)