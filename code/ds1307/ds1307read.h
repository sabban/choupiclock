/*
 * ATmega 16/32 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "I2C_Master_H_file.h"
#include "LCD16x2_4Bit.h"

#define Device_Write_address	0xD0				/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address	0xD1				/* Make LSB bit high of slave address for read operation */
#define TimeFormat12		0x40				/* Define 12 hour format */
#define AMPM			0x20


int second,minute,hour,day,date,month,year;

bool IsItPM(char hour_);
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);
