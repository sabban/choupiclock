/* ---- Code for Digital Clock with Alarm using AVR Microcontroller ------ */ 

#define F_CPU 8000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <string.h>

#include "ds1307/ds1307.h"
#include "i2c/i2c.h"


#define enable            5
#define registerselection 6

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);
void gotoxy(char x,char y);

/* ISR(TIMER1_COMPA_vect); */

static volatile int SEC =0;
static volatile int MIN =0;
static volatile int HOU =0;

int main(void)
{
  int second,minute,hour,day,date,month,year;
  int* clock;
  int ret1, ret2;
  uint8_t ret;
  char buffer[20];
  DDRA = 0b11000000;
  DDRB = 0xFF;
  DDRD = 0xFF;
  _delay_ms(1000);
  TCCR1B |=(1<<CS12)|(1<<CS10)|(1<<WGM12);

  send_a_command(0x01); //Clear Screen 0x01 = 00000001
  _delay_ms(50);
  send_a_command(0x38);
  _delay_ms(50);
  /* send_a_command(0b00001111); */
  /* _delay_ms(50); */
  send_a_command(0x0C);
  _delay_ms(50);
  send_a_string("Bonjour Basile");

  _delay_ms(500);
  send_a_command(0x01); //Clear Screen 0x01 = 00000001
  _delay_ms(50);

  I2C_Init();
  ret = RTC_Clock_Write(0x11, 0x59, 0x00, hour_24);/* Write Hour Minute Second Format */
  if (ret != 0){
      sprintf(buffer, "Clk write error: %d", ret);
      send_a_string(buffer);
      _delay_ms(5000);      
      send_a_command(0x01); //Clear Screen 0x01 = 00000001
      _delay_ms(50);
    }
  RTC_Calendar_Write(0x07, 0x31, 0x12, 0x16);	/* Write day date month and year */
  
  send_a_command(0x01); //Clear Screen 0x01 = 00000001
  _delay_ms(50);

  clock = malloc(7*sizeof(int));
  while(1)
    {
      I2C_Init();
      send_a_command(0x02);
      _delay_ms(50);
      RTC_Read_Clock(clock);							/* Read the clock with second address i.e location is 0 */
      
      if (clock[2] & TimeFormat12){
	sprintf(buffer, "%02x:%02x:%02x  ", (clock[2] & 0b00011111), clock[1], clock[0]);
	if(IsItPM(clock[2]))
	  strcat(buffer, "PM");
	else
	  strcat(buffer, "AM");
	send_a_string(buffer);
      } else {
	sprintf(buffer, "%02x:%02x:%02x  ", (clock[2] & 0b00011111), clock[1], clock[0]);
      }
      gotoxy(0, 1);
      send_a_string(buffer);
      
      gotoxy(0, 2);
      sprintf(buffer, "%02x/%02x/%02x %3s ", clock[3], clock[4], clock[5], clock[6]);
      send_a_string(buffer);
      _delay_ms(500);
    }

}

void send_a_command(unsigned char command)
{
  PORTB = command;
  PORTD &= ~ (1<<registerselection);
  PORTD |= 1<<enable;
  _delay_ms(3);
  PORTD &= ~1<<enable;
  PORTB = 0xFF;
}

void send_a_character(unsigned char character)
{
  PORTB = character;
  PORTD |= 1<<registerselection;
  PORTD |= 1<<enable;
  _delay_ms(3);
  PORTD &= ~1<<enable;
  PORTB = 0xFF;
}

void send_a_string(char *string_of_characters)
{
  while(*string_of_characters > 0)
    {
      send_a_character(*string_of_characters++);
    }
}

void gotoxy(char x,char y) {
  if (x<16) {
    if (y==1) {
      send_a_command(0x80+x);
    } else {
      send_a_command(0xC0+x);
    }
  }
}
