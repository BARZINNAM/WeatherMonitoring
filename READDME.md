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

## Running the applications :

Inside the build folder please execute the following command for starting the WeatherMonitoring application :

./WeatherMonitoring.exe

Inside the build folder please execute the following command for performing the unit tests :

./TestWeatherMonitoring.exe

