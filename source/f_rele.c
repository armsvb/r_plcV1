/******************************************************************************
     * File: f_rele.c
     * Description: модуль управления основной логикой работы программы
     * Created: 01 авг 2015
     * Copyright:
     * Author: Александр Шабуров
     * Email: alex38779@gmail.com

******************************************************************************/

/*инклудим*/
#include "rele.h"

/*идентификаторы реле*/
#define R1 1
/*состояние реле
* 0 - откл
* 1 - в работе
* 2 - в ожидании
*/
uint8_t sostRele1 = 0;
/*режим отображения меню*/
uint8_t modeIndication = 0;
/*вкл -выкл реле  1*/
bool onRele1 = false;
/*основные парметры, настройки реле*/
/*можно ли использовать  реде*/
uint8_t useRele1;
/*режим работы 1 реле*/
uint8_t rejimWorkRele1;
/*параметр 1*/
uint8_t 1paramRele1;
/*параметр 2*/
uint8_t 2paramRele1;
/*параметр 3*/
uint8_t 3paramRele1;
/*параметр 4*/
uint8_t 4paramRele1;
/*параметр 5*/
uint8_t 5paramRele1;

/*загрузка настроек*/
void f_init_rele_1()
{
  useRele1 = setting_rele[R1][0];
  rejimWorkRele1 = setting_rele[R1][1];
  /*остальное грузим попозже*/
}

/*конвертор int to bool*/
bool int_to_bool(uint8_t int_to)
{
	if(int_to == 1)
  {
		return true;
	}
	else
  {
		return false;
	}
}

/*индикация*/
void indication_rele(uint8_t r_1, uint8_t mode_ind)
{
	;
}

/*обработка состояний реле*/
void sost_rele()
{
  ;
}

void work_rele_1()
{
  f_init_rele_1();
  switch (work_r1)
   {
    /*можно*/
    case true:
	  f_init_rele_1();
      switch (rejim_r1)
      {
        /*0  режим*/
        case 0:
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
