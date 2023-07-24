/**
 * @file max6675.h
 * @author kekecjan
 * @brief Library for interfacing with the MAX6675 thermocouple temperature sensor.
 *
 * This library provides functions to initialize, read temperature data, and handle interrupts
 * for the MAX6675 thermocouple temperature sensor using the STM32F4 microcontroller.
 * The library supports both blocking and interrupt-driven modes of operation for temperature readings.
 *
 * @attention This library assumes that the SPI peripheral and GPIOs have been correctly configured
 *            for communication with the MAX6675 sensor. Ensure proper configuration before using this library.
 *
 * @note This library is intended for use with STM32F4 microcontrollers.
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

#include "main.h"

#define MAX6675_SPI_INTERRUPT_MODE  //UNCOMMENT INTERRUPT MODE IF YOU ARE USING IT


typedef struct{

	SPI_HandleTypeDef *spiHandle;
	GPIO_TypeDef* GPIO_PORT_PIN;
	uint16_t GPIO_Pin;
	uint16_t rawSPIdata;
	uint8_t endOfConversion;

}MAX6675;


void MAX6675_Init(MAX6675 *struc, SPI_HandleTypeDef *spiHandle, GPIO_TypeDef* GPIO_PORT_nCS, uint16_t GPIO_nCS_Pin);


void MAX6675_ReadRawData(MAX6675 *struc);
uint16_t MAX6675_ConvertRawDataToTempIntDeg(MAX6675 *struc);
float MAX6675_ConvertRawDataToTempFloatDeg(MAX6675 *struc);
uint8_t MAX6675_CheckOpenThermocouple(MAX6675 *struc);


uint16_t MAX6675_ReadTemperatureIntegerDeg(MAX6675 *struc);
float MAX6675_ReadTemperatureFloatDeg(MAX6675 *struc);
uint8_t MAX6675_ReadIfThermocoupleOpen(MAX6675 *struc);


void MAX6675_StartConversion_IT(MAX6675 *struc);
void MAX6675_ConversionCplt_IT(MAX6675 *struc);



#endif /* INC_MAX6675_H_ */
