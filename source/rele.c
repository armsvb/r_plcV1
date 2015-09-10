/******************************************************************************
     * File: f_rele.c
     * Description: основной модуль, функция main
     * Created: 01 авг 2015
     * Copyright:
     * Author: Александр Шабуров
     * Email: alex38779@gmail.com

******************************************************************************/

/*частота работы мк*/
#define F_CPU 8000000UL

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

/*настройка IO*/
void gpio_init()
{
  DDRD |= (1<<rele1) |  (1<<rele2) | (1<<rele3) | (0<<btn_start_menu) | (0<<btn_up) | (0<<btn_down) | (0<<btn_ok) | (0<<btn_back);
  PORTD |= rele_off | (1 << btn_start_menu) | (1<<btn_up) | (1<<btn_down) | (1<<btn_ok) | (1<<btn_back);
  DDRB=0xff;
  DDRC=0xff;
}

/*настройка SPI*/
void spi_init()
{
  SPCR = 0b01110011;
}

/*настройка таймеров*/
void timer_init()
{
  /*таймер Т0*/
  TCCR0 |= 1<<CS01;
  TCNT0 = 0xff;
  TIMSK |= 1<<TOIE0;
  /*таймер Т1*/
}

/*обработка нажатий кнопки меню-старт*/
void working_button()
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
  gpio_init();
  spi_init();
  timer_init();
  sei();
  while(1)
  {
    //sei();
    while(!auto_menu)
    {
      send_buffer(0,1,2,3);
	    working_button();
	    //_delay_ms(50);
    }
	  while(auto_menu)
    {
  		//menu_init();
  		working_button();
  		menu();
  		//_delay_ms(50);
    }
  }
}
