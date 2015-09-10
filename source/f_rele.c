/*
 * f_rele.cpp
 *
 * Created: 03.08.2015 9.28
 *  Author: Alexander Shaburov
 */

#include "rele.h"

/*идентификаторы реле*/
#define r1 1
#define r2 2
#define r3 3
#define r4 4
/*состояние реле
* 0 - откл
* 1 - в работе
* 2 - в ожидании
*/
uint8_t sost_rele_1 = 0;
/*режим отображения меню*/
uint8_t mode_indication = 0;
/*вкл -выкл реле  1*/
bool on_r1 = false;
/*основные парметры, настройки реле*/
/*можно ли использовать реле 1*/
uint8_t parametr1_0 = setting_rele[r1][0];
bool work_r1 = false;
/*режим работы первого реле*/
uint8_t parametr1_1 = setting_rele[r1][1];
static uint8_t rejim_r1;
/*p2 - параметр 2, во сколько включить часов*/
uint8_t parametr1_2 = setting_rele[r1][2];
uint8_t time_on_hour_r1;
/*р3 - во сколько минут*/
uint8_t parametr1_3 = setting_rele[r1][3];
uint8_t time_on_minute_r1;
/*р4 - во сколько выключить часов*/
uint8_t parametr1_4 = setting_rele[r1][4];
uint8_t time_of_hour_r1;
/*р5 - во сколько выключить часов*/
uint8_t parametr1_5 = setting_rele[r1][5];
uint8_t time_of_minute_r1;
/*берем текущее время*/
uint8_t time_hour,
        time_minute;
/*p6 - параметр 6, кол-во повторений*/
uint8_t parametr1_6 = setting_rele[r1][6];
uint8_t povtor_r1;

/*конвертор int to bool*/
bool int_to_bool(uint8_t int_to){
	if(int_to == 1){
		return true;
	}
	else{
		return false;
	}
}

/*индикация*/
void indication_rele(uint8_t r_1, uint8_t mode_ind){
	;
}

void f_init_rele_1(){
	work_r1 =  int_to_bool(parametr1_0);
	rejim_r1 = parametr1_1;
	if(rejim_r1 == 0){		
		time_on_hour_r1 = parametr1_2;
		time_on_minute_r1 = parametr1_3;
		time_of_hour_r1 = parametr1_4;
		time_of_minute_r1 = parametr1_5;
		povtor_r1 = parametr1_6;
	}
}

void work_rele_1(){
  switch (work_r1) {
    /*можно*/
    case true:
	  f_init_rele_1();
      switch (rejim_r1) {
        /*0  режим*/
        case 0:
          /*включаем реле по времени*/
          if((time_on_hour_r1 == time_hour) and (time_on_minute_r1 == time_minute)){
            on_r1 = true;
          }
          /*выключаем реле по времени*/
          if((time_of_hour_r1 == time_hour) and (time_of_minute_r1 == time_minute)){
            on_r1 = false;
            povtor_r1--;
          }
          /*повторяем н раз*/
          if(povtor_r1 != 0){
            work_r1 = false;
          }
          break;
        /*первый режим*/
        case 1:
          ;
          break;    
      }
      break;
    /*нельзя*/
    case false:
      on_r1 = false;
      break;
  }
}

void sost_rele(){
	indication_rele(sost_rele_1, mode_indication);
	/*вкл выкл реле 1*/
	if(on_r1 == true){
		PORTD |= rele1_start;
	 }
	if(on_r1 == false){
		PORTD |= rele1_stop;
	}	
}	