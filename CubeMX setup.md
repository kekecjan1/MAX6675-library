# CubeMX setup

This guide will walk you through the steps to set up the MAX6675 thermocouple temperature sensor using CubeMX for an STM32 microcontroller. The MAX6675 communicates over blocking and none-blocking SPI , so we'll configure the SPI peripheral, the necessary GPIOs and timer for interrupt.

## Clock configuration

![clockConfig](https://github.com/kekecjan1/MAX6675-library/assets/21065314/d745f408-abce-45d3-8ba7-af9a5732447d)

## SPI configuration for blocking mode (polling) :

Note: The MAX6675 thermocouple sensor has a maximum SPI clock speed of 4.3 MHz. When setting the prescaler, ensure that the SPI clock frequency does not exceed this maximum value. Adjust the prescaler appropriately to achieve a baud rate for reliable communication. 

![configurationBlocking](https://github.com/kekecjan1/MAX6675-library/assets/21065314/7effae31-a2fc-4426-a527-70843919ca8b)

Choose a GPIO pin for the MAX6675. This pin will control the CS signal to the MAX6675 during SPI communication.
The CS signal must be an output initially as high.
   - In the GPIO tab or in Pinout view, select an available GPIO pin and configure it as "GPIO_Output".

![GPIO_blocking](https://github.com/kekecjan1/MAX6675-library/assets/21065314/a56b1d30-8394-482f-b88d-f7dd142f86bb)

## ( NOTE ) conversion timer in blocking mode (polling):
After each temperature conversion use `HAL_Delay(Delay)` function where Delay is between 170 ms and 220 ms (conversion time) !

## SPI configuration for none-blocking mode (interrupt):

Note: The MAX6675 thermocouple sensor has a maximum SPI clock speed of 4.3MHz. When setting the prescaler, ensure that the SPI clock frequency does not exceed this maximum value. Adjust the prescaler appropriately to achieve a baud rate for reliable communication. 

![configurationNoneBlocking](https://github.com/kekecjan1/MAX6675-library/assets/21065314/f4176111-2775-4dd9-99e2-01711213f93c)
![configurationNoneBlockingInterrupt](https://github.com/kekecjan1/MAX6675-library/assets/21065314/a474c27b-750a-451a-9336-357417a47ea7)

## Timer configuration for none-blocking mode (interrupt):

Due to the conversion time of the MAX6675 thermocouple sensor, which typically ranges from a minimum of 170 ms to a maximum of 220 ms, it is essential to use a timer to read temperature data at appropriate intervals. In your project, configure a timer to trigger temperature readings from the MAX6675 periodically. For example, you can use the STM32's Timer peripheral in interrupt mode to read from the sensor at specific intervals. In the timer's interrupt handler, call the necessary functions to read and process temperature data from the MAX6675 sensor.

![configurationTimer2](https://github.com/kekecjan1/MAX6675-library/assets/21065314/800ae48d-1d1e-48c3-862e-1ea0d8018a4f)

Note : In my example code i set the timer2 interrupt occurrence every 200 ms.

$` n_{counter}=T\bullet2\bullet\frac{f_{CLK}}{prescaler}=0.2\bullet2\bullet\frac{50\ MHz}{5000}=4000 `$




