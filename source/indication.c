/*
 * indication.cpp
 *
 * Created: 01.08.2015 11:37:53
 *  Author: Alexander Shaburov
 */ 

#include "rele.h"

/*индикатор ОК
*
*		a
*	f		b
*		g	
*	e		c
*		d		h
*/
uint8_t number_ok[20] = {
  /*0babcdefgh*/
    0b00000011, /*0*/
    0b10011111, /*1*/
    0b00100101, /*2*/
    0b00001101, /*3*/
    0b10011001, /*4*/
    0b01001001, /*5*/
    0b01000001, /*6*/
    0b00011111, /*7*/
    0b00000001, /*8*/
    0b00001001, /*9*/
	0b11111101, /*- - 10*/
	0b00110001, /*P - 11*/
	0b01100011, /*c - 12*/
	0b11100001, /*t - 13*/
	0b01100001, /*E - 14*/
	0b11000001, /*b - 15*/
	0b10000101, /*d - 16*/
	0b11010001, /*h - 17*/
	0b10010001, /*H - 18*/
	0b00010001, /*R - 19*/
};

uint8_t digit_ok[5] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
};

/*буффер для вывода через  spi*/
uint8_t buff[4];
uint8_t buff_index = 0;

void send_spi(){
  PORTB &= ~(1<<PB0);
  SPDR = digit_ok[1];
  while(!(SPSR &(1<<SPIF)));
  SPDR = digit_ok[3];
  while(!(SPSR &(1<<SPIF)));
  PORTB |= (1<<PB0);
}

void send_spi_data(uint16_t data){
  /*1234 buff[0] = 4, buff[1] = 3.......*/
  buff[0] = data % 10;
  data = data / 10;
  buff[1] = data % 10;
  data = data / 10;
  buff[2] = data % 10;
  buff[3] = data / 10;
  send_spi();
}

void send_buffer_data_2(uint8_t n1, uint8_t n2, uint8_t data){
	buff[0] = n1;
	buff[1] = n2;
	buff[2] = data % 10;
	buff[3] = data / 10;
}

void send_buffer(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4){
	buff[3] = num1;
	buff[2] = num2;
	buff[1] = num3;
	buff[0] = num4;
}

void send_buffer_spi(){
  PORTB &= ~(1<<PB0);
  SPDR = digit_ok[buff_index];
  while(!(SPSR &(1<<SPIF)));
  SPDR = number_ok[buff[buff_index]];
  while(!(SPSR &(1<<SPIF)));
  PORTB |= (1<<PB0);
  buff_index++;
  _delay_us(100);
  if(buff_index==4){
    buff_index=0;
  }
}
