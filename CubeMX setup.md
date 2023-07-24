## CubeMX setup

This guide will walk you through the steps to set up the MAX6675 thermocouple temperature sensor using CubeMX for an STM32 microcontroller. The MAX6675 communicates over SPI, so we'll configure the SPI peripheral and the necessary GPIOs.

- create a new project on STM32CubeIDE
- enable one or two (one port for display and one for touch sensor) SPI port.

| Column 1       | Column 2       | Column 3       |
|:--------------:|:--------------:|:--------------:|
| Row 1, Col 1   | Row 1, Col 2   | Row 1, Col 3   |
| Row 2, Col 1   | Row 2, Col 2   | Row 2, Col 3   |
| Row 3, Col 1   | Row 3, Col 2   | Row 3, Col 3   |


| Mode | Choosen |
| --- | --- |
| Mode | Receive Only Master |
| Hardware NSS Signal | Disable|
