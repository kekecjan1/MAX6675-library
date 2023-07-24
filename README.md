# MAX6675 Thermocouple Library for STM32Fx

This library provides functions to interface with the MAX6675 thermocouple temperature sensor on STM32Fx microcontrollers.
It allows users to read temperature data from the MAX6675 sensor using SPI communication.
The library supports both blocking and non-blocking modes for temperature readings, making it versatile for different application scenarios.

## Tested Platform

The MAX6675 library has been tested extensively on the STM32F411 board, and it has been verified to work correctly on this platform.
It was tested at a maximum microcontroller clock frequency of 100 MHz.


## Compatibility

While the library has been tested on the STM32F411 board, there is a high degree of confidence that it should work seamlessly on other STM32 microcontrollers as well. The library uses standard STM32 HAL drivers and follows industry best practices for portability. As long as the target STM32 microcontroller is supported by the STM32 HAL, it should be compatible with the MAX6675 library.

Conversion time of the MAX6675 thermocouple sensor is between 170 ms and 220 ms ! If you are reading to fast it might be sending zeros or it will be sending you the first read value and others would be the same.


- In blocking mode, all prescaler values (including the maximum prescaler of 16 to achieve maximum frequency for reliable communication with MAX6675) have been tested and work reliably with the MAX6675.
- In non-blocking mode, the library has been tested with prescaler values from 64 to 16 and works reliably. If needed or if user wants to go for lower SPI speed, adjust the value in for-loop with higher number (for my purpouse 150 was enough)  in the `MAX6675_ConversionCplt_IT()` function to accommodate higher prescaler values for their specific setup.
- 
## Recommendations

- When using non-blocking mode with higher prescaler values, it's advisable to verify the behavior of SPI signals (MISO, CLK and CS) using an oscilloscope. Ensure that the CS signal remains low during SPI communication to prevent data integrity issues.


## Reading Process of MAX6675

To read temperature data from the MAX6675, follow these steps:

    1. Force the Chip Select (CS) signal low to initiate the read process. This stops any ongoing conversion process.

    2. Apply a clock signal at the Serial Clock (SCK) pin to the MAX6675.
    The MAX6675 will provide the temperature data on the Serial Output (SO) pin during each clock cycle.

    3. Read the temperature data from the Serial Output (SO) pin by receiving the SPI data.

    4. After reading the temperature data, initiate a new conversion process by forcing the Chip Select (CS) signal high.

- Note: The CS signal must be low during the entire SPI communication process to ensure successful data retrieval from the MAX6675.



## Features

- Read temperature in degrees Celsius from the MAX6675 sensor
- Supports both blocking and non-blocking temperature readings
- Lightweight and optimized for STM32Fx microcontrollers

## Usage

1. Include "MAX6675.h" in your project
2. Initialize the MAX6675 sensor using MAX6675_init()
3. Read temperature data using MAX6675_ReadTemperatureFloatDeg() or other appropriate functions
   ...

License: MIT License

