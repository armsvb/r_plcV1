/******************************************************************************
     * File: f_rele.c
     * Description: основной модуль, функция main
     * Created: 01 авг 2015
     * Copyright:
     * Author: Александр Шабуров
     * Email: alex38779@gmail.com

******************************************************************************/

/*частота работы мк*/
//#define F_CPU 8000000UL

/*инклудим*/
#include "rele.h"

/*переменные*/
bool auto_menu = false;
uint8_t i = 0;

/*обработчик прерываний*/
ISR(TIMER0_OVF_vect)
{
  send_buffer_spi();
  sost_rele();
  //working_button();
}

/*счет секунд*/
ISR(TIMER2_OVF_vect)
{
	globalSecond++;
}

/*настройка IO*/
void gpioInit()
{
  DDRD |= (1<<rele1) |  (1<<rele2) | (1<<rele3) | (0<<btn_start_menu) | (0<<btn_up) | (0<<btn_down) | (0<<btn_ok) | (0<<btn_back);
  PORTD |= rele_off | (1 << btn_start_menu) | (1<<btn_up) | (1<<btn_down) | (1<<btn_ok) | (1<<btn_back);
  DDRB=0xff;
  DDRC=0xff;
}

/*настройка SPI*/
void spiInit()
{
  SPCR = 0b01110011;
}

/*настройка таймеров*/
void timerInit()
{
  /*таймер Т0*/
  TCCR0 |= 1<<CS01;
  TCNT0 = 0xff;
  /*таймер Т1*/
  /*таймер Т2 - часовой кварц*/
  TIMSK &= ~((1<<TOIE2) | (1<<OCIE2));
  ASSR |= 1<<AS2;
  TCNT2 = 0x00;
  TCCR2 = 0x05;
  OCR2 = 0x80;
  while(ASSR & ((1<<TCN2UB) | (1<<OCR2UB) | (1<<tCR2Ub)));
  /*прерывания*/
  TIMSK |= (1<<TOIE0) | (1<<TOIE2);
}

/*обработка нажатий кнопки меню-старт*/
void pressButton()
{
	if((PIND & (1<<btn_start_menu))==0)
  {
		i++;
		if(i>1)
    {
		  i=0;
		}
		_delay_ms(100);
	}
	if(i>0)
  {
		auto_menu = false;
	}
	else
  {
		auto_menu = true;
	}
}

/*главная функция main*/
int main(void)
{
  cli();
  gpioInit();
  spiInit();
  timerInit();
  sei();
  while(1)
  {
    //sei();
    while(!auto_menu)
    {
      send_buffer(0,1,2,3);
	    pressButton();
	    //_delay_ms(50);
    }
	  while(auto_menu)
    {
  		//menu_init();
  		pressButton();
  		menu();
  		//_delay_ms(50);
    }
  }
}
