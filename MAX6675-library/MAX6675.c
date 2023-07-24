/**
 * @file max6675.c
 * @author kekecjan
 * @brief Library for interfacing with the MAX6675 thermocouple temperature sensor.
 *
 * This file contains the implementation of functions for the MAX6675 thermocouple temperature sensor library.
 * The library provides functions to initialize, read temperature data, and handle interrupts
 * for the MAX6675 sensor using the STM32F4 microcontroller.
 *
 * @attention This library assumes that the SPI peripheral and GPIOs have been correctly configured
 *            for communication with the MAX6675 sensor. Ensure proper configuration before using this library.
 *
 * @note This library is intended for use with STM32F4 microcontrollers.
 */

#include "MAX6675.h"

/*
 *
 * Initilize function
 * parameters:
 * make new structure
 * write SPIx you are using and CS port & pin
 *
 * */


/**
 * @brief Initializes the MAX6675 sensor structure.
 *
 * This function initializes the MAX6675 sensor structure with the provided SPI handle,
 * GPIO port, and pin for chip select (CS) control.
 *
 * @param struc Pointer to the MAX6675 structure.
 * @param spiHandle Pointer to the SPI_HandleTypeDef struct for communication with the MAX6675.
 * @param GPIO_PORT_nCS GPIO port for chip select (CS) pin control.
 * @param GPIO_nCS_Pin GPIO pin for chip select (CS) control.
 */
void MAX6675_Init(MAX6675 *struc, SPI_HandleTypeDef *spiHandle, GPIO_TypeDef* GPIO_PORT_nCS, uint16_t GPIO_nCS_Pin){

	struc->spiHandle = spiHandle;
	struc->GPIO_PORT_PIN = GPIO_PORT_nCS;
	struc->GPIO_Pin = GPIO_nCS_Pin;
	struc->endOfConversion = 0;

  	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_SET);

}

/**
 * @brief Reads raw data from the MAX6675 sensor.
 *
 * This function reads raw data from the MAX6675 sensor using the provided SPI handle
 * and GPIO port/pin for chip select (CS) control. The raw data is stored in the sensor structure.
 *
 * @param struc Pointer to the MAX6675 structure.
 */

void MAX6675_ReadRawData(MAX6675 *struc){

	uint16_t rawData = 0;

	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_RESET);
	HAL_SPI_Receive(struc->spiHandle, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);
	for(int i=0; i<=100;i++){
		__NOP();
	}
  	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_SET);

  	struc->rawSPIdata = rawData;

}


/**
 * @brief Converts raw data from the MAX6675 sensor to an integer temperature value in degrees Celsius.
 *
 * This function converts the raw data from the MAX6675 sensor, stored in the provided MAX6675 structure,
 * to an integer value representing the temperature in degrees Celsius. The raw data is 16 bits,
 * and the function right-shifts the data by 5 bits to obtain the temperature value.
 *
 * @param struc Pointer to the MAX6675 structure containing the raw data to be converted.
 * @return An unsigned 16-bit integer representing the temperature in degrees Celsius.
 */

uint16_t MAX6675_ConvertRawDataToTempIntDeg(MAX6675 *struc){
	uint16_t rawData = 0, temperatureIntDeg = 0;

	rawData = struc->rawSPIdata;

	temperatureIntDeg = (rawData>>5);

    return temperatureIntDeg;

}

/**
 * @brief Converts raw data from the MAX6675 sensor to a floating-point temperature value in degrees Celsius.
 *
 * This function converts the raw data from the MAX6675 sensor, stored in the provided MAX6675 structure,
 * to a floating-point value representing the temperature in degrees Celsius. The raw data is 16 bits,
 * and the function performs appropriate bit manipulation to obtain the temperature value with fractional parts.
 *
 * @param struc Pointer to the MAX6675 structure containing the raw data to be converted.
 * @return A floating-point value representing the temperature in degrees Celsius.
 */

float MAX6675_ConvertRawDataToTempFloatDeg(MAX6675 *struc){
	uint16_t rawData = 0, temperatureIntDeg = 0, tempData = 0;
	uint8_t temperatureIntToFloatDeg=0;
	float temperatureFloatDeg;

	rawData = struc->rawSPIdata;

	tempData = (rawData>>3);
	temperatureIntDeg = (tempData>>2);
	temperatureIntToFloatDeg = (tempData & 0x0003);

		 if(temperatureIntToFloatDeg == 0){      temperatureFloatDeg = (float)temperatureIntDeg;			  }
	else if(temperatureIntToFloatDeg == 0x0003){ temperatureFloatDeg = (float)temperatureIntDeg + (float)0.75;}
	else if(temperatureIntToFloatDeg == 0x0002){ temperatureFloatDeg = (float)temperatureIntDeg + (float)0.50;}
	else if(temperatureIntToFloatDeg == 0x0001){ temperatureFloatDeg = (float)temperatureIntDeg + (float)0.25;}

	return temperatureFloatDeg;
}

/**
 * @brief Checks if the MAX6675 sensor detects an open thermocouple.
 *
 * This function checks the raw data from the MAX6675 sensor, stored in the provided MAX6675 structure,
 * to determine if the sensor detects an open thermocouple. It examines the specific bit responsible for
 * indicating an open thermocouple in the raw data and returns the result as a boolean value (0 or 1).
 *
 * @param struc Pointer to the MAX6675 structure containing the raw data to be checked.
 * @return An unsigned 8-bit integer (0 or 1) indicating if an open thermocouple is detected.
 *         - 0: No open thermocouple detected.
 *         - 1: Open thermocouple detected.
 */

uint8_t MAX6675_CheckOpenThermocouple(MAX6675 *struc){

	return 	(struc->rawSPIdata & 0x0004)>>2;

}

/**
 * @brief Reads the temperature as an integer value in degrees Celsius from the MAX6675 sensor.
 *
 * This function reads the temperature from the MAX6675 sensor and returns the result as an integer value
 * representing the temperature in degrees Celsius. The function first retrieves the raw data from the sensor
 * using SPI communication and then processes the raw data to obtain the temperature value.
 *
 * @param struc Pointer to the MAX6675 structure containing the necessary configuration.
 * @return An unsigned 16-bit integer representing the temperature in degrees Celsius.
 */

uint16_t MAX6675_ReadTemperatureIntegerDeg(MAX6675 *struc){

	uint16_t rawData, temperatureIntDeg = 0;

	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_RESET);

  	HAL_SPI_Receive(struc->spiHandle, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);

	for(int i=0; i<=100;i++){
		__NOP();
	}
  	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_SET);

    temperatureIntDeg = (rawData>>5);

    return temperatureIntDeg;
}

/**
 * @brief Reads the temperature as a floating-point value in degrees Celsius from the MAX6675 sensor.
 *
 * This function reads the temperature from the MAX6675 sensor and returns the result as a floating-point value
 * representing the temperature in degrees Celsius. The function first retrieves the raw data from the sensor
 * using SPI communication and then processes the raw data to obtain the temperature value with fractional parts.
 *
 * @param struc Pointer to the MAX6675 structure containing the necessary configuration.
 * @return A floating-point value representing the temperature in degrees Celsius.
 */

float MAX6675_ReadTemperatureFloatDeg(MAX6675 *struc){

	uint16_t rawData, tempData, temperatureIntDeg = 0;
	uint8_t temperatureIntToFloatDeg=0;
	float temperatureFloatDeg;


	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_RESET);

  	HAL_SPI_Receive(struc->spiHandle, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);

	for(int i=0; i<=100;i++){
		__NOP();
	}
  	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_SET);

	tempData = (rawData>>3);
	temperatureIntDeg = (tempData>>2);
	temperatureIntToFloatDeg = (tempData & 0x0003);

		 if(temperatureIntToFloatDeg == 0){      temperatureFloatDeg = (float)temperatureIntDeg;			  }
	else if(temperatureIntToFloatDeg == 0x0003){ temperatureFloatDeg = (float)temperatureIntDeg + (float)0.75;}
	else if(temperatureIntToFloatDeg == 0x0002){ temperatureFloatDeg = (float)temperatureIntDeg + (float)0.50;}
	else if(temperatureIntToFloatDeg == 0x0001){ temperatureFloatDeg = (float)temperatureIntDeg + (float)0.25;}


    return temperatureFloatDeg;
}


/**
 * @brief Reads if the thermocouple is open or closed from the MAX6675 sensor.
 *
 * This function reads the MAX6675 sensor to determine if the thermocouple is open or closed.
 * It checks the specific bit in the raw data from the sensor, which indicates the status of the thermocouple,
 * and returns the result as a boolean value (0 or 1).
 *
 * @param struc Pointer to the MAX6675 structure containing the necessary configuration.
 * @return An unsigned 8-bit integer (0 or 1) indicating if the thermocouple is open or closed.
 *         - 0: Thermocouple is closed (no open circuit detected).
 *         - 1: Thermocouple is open (open circuit detected).
 */

uint8_t MAX6675_ReadIfThermocoupleOpen(MAX6675 *struc){

	uint16_t rawData, checkOpenThermocouple = 0;

	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_RESET);

  	HAL_SPI_Receive(struc->spiHandle, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);
	for(int i=0; i<=100;i++){
		__NOP();
	}
  	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_SET);

  	checkOpenThermocouple = (rawData & 0x0004)>>2;

  	return checkOpenThermocouple;

}



#ifdef MAX6675_SPI_INTERRUPT_MODE

/**
 * @brief Starts the temperature conversion using the MAX6675 sensor in interrupt mode.
 *
 * This function starts the temperature conversion using the MAX6675 sensor in interrupt mode.
 * It sets the chip select (CS) pin low to select the sensor and initiates the SPI receive in interrupt mode.
 * The raw data from the sensor will be stored in the MAX6675 structure.
 *
 * @param struc Pointer to the MAX6675 structure containing the necessary configuration.
 */

void MAX6675_StartConversion_IT(MAX6675 *struc){

HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_RESET);
HAL_SPI_Receive_IT(struc->spiHandle, (uint8_t *)&struc->rawSPIdata, 1);

}

/**
 * @brief Callback function for the completion of temperature conversion using the MAX6675 sensor in interrupt mode.
 *
 * It sets the 'endOfConversion' flag in the MAX6675 structure to indicate that the conversion is complete.
 * The function is triggered when the interrupt occurs, indicating that new data is available.
 *
 * @param struc Pointer to the MAX6675 structure containing the necessary configuration and status flags.
 */

void MAX6675_ConversionCplt_IT(MAX6675 *struc){

	struc->endOfConversion = 1;
	for(int i=0;i<=150;i++) __NOP();  //UNCOMENT THIS LINE IF DATA AND CLK AREN'T INSIDE nCS LOW AND YOU CAN CHANGE NUMBER IN FOR LOOP

	HAL_GPIO_WritePin(struc->GPIO_PORT_PIN, struc->GPIO_Pin, GPIO_PIN_SET);


}

#endif

