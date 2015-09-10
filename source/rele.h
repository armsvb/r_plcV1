/******************************************************************************
     * File: f_rele.c
     * Description: заголовочнй файл
     * Created: 01 авг 2015
     * Copyright:
     * Author: Александр Шабуров
     * Email: alex38779@gmail.com

******************************************************************************/

#ifndef RELE_H_
#define RELE_H_

/*инклудим*/
#include <avr/io.h>
#include <stdbool.h>
#include "stdint.h"
#include "math.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

/*основные*/
void gpioInit();
void spiInit();
void timeIinit();
void pressButton();

/*индикация*/
void send_buffer(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4);
void send_spi();
void send_spi_data(uint16_t data);
void send_buffer_data_2(uint8_t n1, uint8_t n2, uint8_t data);
void send_buffer_spi();
void indication_rele(uint8_t r_1, uint8_t mode_ind);

/*меню*/
void menu_button();
void menuInit();
void menu();

/*работа с реле*/
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

/*настройка пинов индикации*/
#define led1 PC1
#define led2 PC0
#define led3 PC2
#define led1_on (1<<led1)
#define led2_on (1<<led2)
#define led3_on (1<<led3)
#define led1_off (0<<led1)
#define led2_off (0<<led2)
#define led3_off (0<<led3)
#define led_off  led1_off | led2_off | led3_off

/*button - start-menu, up, down, back, ok*/
#define btn_start_menu PD4
#define btn_up PD3
#define btn_down PD2
#define btn_ok PD1
#define btn_back PD0

/*часы, минуты, секнды*/
uint8_t globalSecond;
uint8_t globalMinute;
uint8_t globalHour;

/*массив настроек реле*/
static volatile uint8_t setting_rele[3][8] =
{
  /*----> 1 группа, основные параметры
  * 01234567
  * 0-настройка года
  * 1-настройка месяца
  * 2-настройка дня
  * 3-настройка часов
  * 4-настройка минут
  * 5-настройка режима индикации
  *   0-
  *   1-
  * 6-коррекция хода часов
  */
  {0,0,0,0,0,0,0,},
  /*----> 2 группа, параметры 1 реле
  * 01234567
  * 0-активно ли реле
  * 1-режим работы реле
  *   0-не активно(по умолчанию)
  *   1-запуск
  *   2-
  * 2-1 параметр
  * 3-2 параметр
  * 4-3 параметр
  * 5-4 параметр
  * 6-5 параметр
  */
  {0,0,0,0,0,0,0,},
  /*----> 3 группа, системные настройки
  * часть можно редактировать, часть нет -*
  * 01234567
  * 0-* версия прошивки
  * 1-* сер номер
  * 2-* дата прошивки
  * 3-
  *
  *
  *
  */
  {0,0,0,0,0,0,0,},
};

/*допустимые пределы - верхний и нижний настроек меню*/
/*верхний предел*/
uint8_t settingMenuUp[3][8] =
{
  {99,12,31,24,60,3,99,},
  {1,3,0,0,0,0,0,},
  {0,0,0,0,0,0,0,},
}

/*нижний предел*/
uint8_t settingMenuDown[3][8] =
{
  {0,1,1,0,0,0,0,},
  {0,0,0,0,0,0,0,},
  {0,0,0,0,0,0,0,},
}

/*размер первого уровня меню*/
uint8_t lengthFirstMenuGr = 3;

/*размер 2 уровня меню*/
uint8_t lengthMenuSecond[4] = {7,7,3};

#endif /* RELE_H_ */
