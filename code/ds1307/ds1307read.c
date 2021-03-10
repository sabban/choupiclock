/*
 * ATmega 16/32 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../i2c/i2c.h"
#include "ds1307.h"

#define AMPM 0x20

#define READ_CLOCK_ADDRESS 0x00
#define READ_CALENDAR_ADDRESS 0x03

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(int* buf)
{
  I2C_Start(Device_Write_address);				/* Start I2C communication with RTC */
  I2C_Write(READ_CLOCK_ADDRESS);					/* Write address to read */
  I2C_Repeated_Start(Device_Read_address);		/* Repeated start with device read address */
  
  buf[0] = I2C_Read_Ack();						/* Read second */
  buf[1] = I2C_Read_Ack();						/* Read minute */
  buf[2] = I2C_Read_Ack();							/* Read hour with Nack */
  buf[3] = I2C_Read_Ack();							/* Read day */ 
  buf[4] = I2C_Read_Ack();							/* Read date */
  buf[5] = I2C_Read_Ack();							/* Read month */
  buf[6] = I2C_Read_Nack();							/* Read the year with Nack */
  I2C_Stop();										/* Stop i2C communication */

}
