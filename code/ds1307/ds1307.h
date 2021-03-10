/*
 * ATmega 16/32 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../i2c/i2c.h"

#define Device_Write_address 0xD0   /* Define RTC DS1307 slave address for write operation */
#define Device_Read_address 0xD1   /* Make LSB bit high of slave address for read operation */
#define hour_12_AM  0x40
#define hour_12_PM  0x60
#define hour_24   0x00
#define Device_Write_address 0xD0    /* Define RTC DS1307 slave address for write operation */
#define Device_Read_address 0xD1    /* Make LSB bit high of slave address for read operation */
#define TimeFormat12  0x40    /* Define 12 hour format */
//#define AMPM 0x20

bool IsItPM(char hour_);
void RTC_Read_Clock(int* buf);
uint8_t RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM);
void RTC_Calendar_Write(char _day, char _date, char _month, char _year); /* function for calendar */
