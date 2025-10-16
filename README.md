# WeatherMonitoring

A C++ project simulating a forcasting weather application.  
GoogleTest is added as a submodule to this project from github. Please first execute the following command: 

1) git clone https://github.com/BARZINNAM/WeatherMonitoring.git  
2) cd WeatherMonitoring  
3) git submodule update --init --recursive  



## Unit test :

Please execute the following commands to build the necessary libraries for Google test.

1) cd Third-party/googletest  
2) mkdir build && cd build  ..
3) cmake ..  
4) cmake --build . --config Release  


## Building the whole project :

1) mkdir build && cd build  
2) cmake ..  
3) make

## Running the application:

Inside the build folder please execute the following command for starting the WeatherMonitoring application :

./WeatherMonitoring.exe  

You'll see a menu like this:  

============================
 Weather Monitor Main Menu
============================
1. Use LocalSensor (random)
2. Use APIClient (static data)
3. SimpleForecast
4. AdvancedForecast
5. Update data once
6. Auto update (5 iterations)
0. Exit
> 

| Key   | Action                      | Description                                                                                                         |
| ----- | --------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| **1** | Use LocalSensor (random)    | Switches to a simulated **local sensor** that generates random temperature, humidity, and wind data.                |
| **2** | Use APIClient (static data) | Switches to a mock **API data source** that cycles through predefined weather samples.                              |
| **3** | SimpleForecast              | Activates the **Simple Forecast strategy**, which predicts temperature as the **average of all past readings**.     |
| **4** | AdvancedForecast            | Activates the **Advanced Forecast strategy**, which adjusts predicted temperature based on humidity and wind speed. |
| **5** | Update data once            | Reads one new data sample from the active data source, runs the current forecast strategy, and prints the result.   |
| **6** | Auto update (5 iterations)  | Repeats the update 5 times automatically (half a second apart), simulating periodic weather monitoring.             |
| **0** | Exit                        | Closes the application cleanly.                                                                                     |


## Running the unit tests:

Inside the build folder please execute the following command for performing the unit tests :

./TestWeatherMonitoring.exe




