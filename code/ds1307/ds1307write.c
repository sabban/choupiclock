/*
 * ATmega 16/32 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "ds1307.h"
#include "../i2c/i2c.h"

uint8_t RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM)
{
  uint8_t ret;
  _hour |= AMPM;
  I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
  ret = I2C_Write(0) << 6;								/* Write on 0 location for second value */
  ret |= I2C_Write(_second) << 4;							/* Write second value on 00 location */
  ret |= I2C_Write(_minute) << 2;							/* Write minute value on 01 location */
  ret |= I2C_Write(_hour);							/* Write hour value on 02 location */
  I2C_Stop();									/* Stop I2C communication */
  return ret;
}

void RTC_Calendar_Write(char _day, char _date, char _month, char _year)	/* function for calendar */
{
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(3);								/* Write on 3 location for day value */
	I2C_Write(_day);							/* Write day value on 03 location */
	I2C_Write(_date);							/* Write date value on 04 location */
	I2C_Write(_month);							/* Write month value on 05 location */
	I2C_Write(_year);							/* Write year value on 06 location */
	I2C_Stop();									/* Stop I2C communication */
}

