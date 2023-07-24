# MAX6675 Thermocouple Library for STM32Fx

This library provides functions to interface with the MAX6675 thermocouple temperature sensor on STM32Fx microcontrollers.
It allows users to read temperature data from the MAX6675 sensor using SPI communication.
The library supports both blocking and none-blocking modes for temperature readings, making it versatile for different application scenarios.

## Tested Platform

The MAX6675 library has been tested extensively on the STM32F411 board, and it has been verified to work correctly on this platform.
It was tested at a maximum microcontroller clock frequency of 100 MHz.


## Compatibility

While the library has been tested on the STM32F411 board, there is a high degree of confidence that it should work seamlessly on other STM32 microcontrollers as well. The library uses standard STM32 HAL drivers and follows industry best practices for portability. As long as the target STM32 microcontroller is supported by the STM32 HAL, it should be compatible with the MAX6675 library.

- In blocking mode, all prescaler values (including the maximum prescaler of 16 to achieve maximum frequency for reliable communication with MAX6675) have been tested and work reliably with the MAX6675.
- In non-blocking mode, the library has been tested with prescaler values from 64 to 16 and works reliably. If needed or if user wants to go for lower SPI speed, adjust the value in for-loop with higher number (for my purpouse 150 was enough)  in the `MAX6675_ConversionCplt_IT()` function to accommodate higher prescaler values for their specific setup. 

## Recommendations

- When using non-blocking mode with higher prescaler values, it's advisable to verify the behavior of SPI signals (MISO, CLK and CS) using an oscilloscope. Ensure that the CS signal remains low during SPI communication to prevent data integrity issues.


# Features

- Read temperature in degrees Celsius from the MAX6675 sensor
- Supports both blocking and none-blocking temperature readings
- Lightweight and optimized for STM32Fx microcontrollers

## Usage

1. Include "MAX6675.h" in your project
2. Initialize the MAX6675 sensor using MAX6675_init()
3. Read temperature data using MAX6675_ReadTemperatureFloatDeg() or other appropriate functions
   ...

License: MIT License

