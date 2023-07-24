## CubeMX setup

This guide will walk you through the steps to set up the MAX6675 thermocouple temperature sensor using CubeMX for an STM32 microcontroller. The MAX6675 communicates over SPI, so we'll configure the SPI peripheral and the necessary GPIOs.


SPI configuration for  blocking mode :

Note: The MAX6675 thermocouple sensor has a maximum SPI clock speed of 4.3MHz. When setting the prescaler, ensure that the SPI clock frequency does not exceed this maximum value. Adjust the prescaler appropriately to achieve a baud rate for reliable communication. 

![configurationBlocking](https://github.com/kekecjan1/MAX6675-library/assets/21065314/7effae31-a2fc-4426-a527-70843919ca8b)

Choose a GPIO pin for the MAX6675. This pin will control the CS signal to the MAX6675 during SPI communication.
The CS signal must be an output initially as high.
   - In the "Pinout & Configuration" tab, select an available GPIO pin (e.g., GPIOA Pin X) and configure it as "GPIO_Output" in the Mode dropdown menu.

![GPIO_blocking](https://github.com/kekecjan1/MAX6675-library/assets/21065314/a56b1d30-8394-482f-b88d-f7dd142f86bb)


