/*
 * rele.h
 *
 * Created: 01.08.2015 11:36:47
 *  Author: Alexander Shaburov
 */ 

#ifndef RELE_H_
#define RELE_H_

#include <avr/io.h>
#include <stdbool.h>
#include "stdint.h"
#include "math.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

/*ОСНОВНЫЕ*/
void gpio_init();
void spi_init();
void timer_init();
void working_button();
/*ИНДИКАЦИЯ*/
void send_buffer(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4);
void send_spi();
void send_spi_data(uint16_t data);
void send_buffer_data_2(uint8_t n1, uint8_t n2, uint8_t data);
void send_buffer_spi();
void indication_rele(uint8_t r_1, uint8_t mode_ind);
/*МЕНЮ*/
void menu_button();
void menu_init();
void menu();
/*РЕЛЕ*/
/*инициализация реле*/
void f_init_rele_1();
/*работа реле*/
void work_rele_1();
/*обработка состояний реле в прерывании*/
void sost_rele();
/*преобразование int to bool*/
bool int_to_bool(uint8_t int_to);

/*настройка пинов*/
#define rele1 PD5
#define rele2 PD6
#define rele3 PD7
#define rele1_start (1<<rele1)
#define rele2_start (1<<rele2)
#define rele3_start (1<<rele3)
#define rele1_stop (0<<rele1)
#define rele2_stop (0<<rele2)
#define rele3_stop (0<<rele3)

#define led1 PC1
#define led2 PC0
#define led3 PC2
#define led1_on (1<<led1)
#define led2_on (1<<led2)
#define led3_on (1<<led3)
#define led1_off (0<<led1)
#define led2_off (0<<led2)
#define led3_off (0<<led3)
#define rele_off  led1_off | led2_off | led3_off

/*button - start-menu, up, down, back, ok*/
#define btn_start_menu PD4
#define btn_up PD3
#define btn_down PD2
#define btn_ok PD1
#define btn_back PD0

/*дискретные датчики*/
#define sensor_1  PC5
#define sensor_2  PC4
#define sensor_3  PC3

static volatile uint8_t setting_rele[6][10]; 
#endif /* RELE_H_ */