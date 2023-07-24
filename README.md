MAX6675 Thermocouple Library for STM32Fx

This library provides functions to interface with the MAX6675 thermocouple temperature sensor on STM32Fx microcontrollers.
It allows users to read temperature data from the MAX6675 sensor using SPI communication.
The library supports both blocking and none-blocking modes for temperature readings, making it versatile for different application scenarios.

Features:
- Read temperature in degrees Celsius from the MAX6675 sensor
- Supports both blocking and none-blocking temperature readings
- Lightweight and optimized for STM32Fx microcontrollers

Usage:
1. Include "MAX6675.h" in your project
2. Initialize the MAX6675 sensor using MAX6675_init()
3. Read temperature data using MAX6675_ReadTemperatureFloatDeg() or other appropriate functions

License: MIT License

