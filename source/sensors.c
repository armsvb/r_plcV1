/******************************************************************************
     * File: f_rele.c
     * Description: модуль датчиков - не используется
     * Created: 03 авг 2015
     * Copyright:
     * Author: Александр Шабуров
     * Email: alex38779@gmail.com

******************************************************************************/

#include "rele.h"

/*инициализация*/
void sensors_init();
/*обработка сенсоров, думаю в прерывание, хотя хз*/
void sensors();

/*ДИСКРЕТНЫЕ ДАТЧИКИ*/
/*разрешение работы датчиков*/
bool sensors_1_work = false;
bool sensors_2_work = false;
bool sensors_3_work = false;
/*срабатывание датчиков*/
bool sensors_1_on = false;
bool sensors_2_on = false;
bool sensors_3_on = false;
/*режим реакции датчика на 0 или 1
* false - 1
* true - 0
*/
bool sensors_1_rejim_r = false;
bool sensors_2_rejim_r = false;
bool sensors_3_rejim_r = false;
/*обработка двух датчиков одновременоо ПОМЫСЛИТЬ*/
bool sensor_1_2 = false;

/*АНАЛОГОВЫЕ ДАТЧИКИ*/

void sensors_init(){

}

void sensors(){

}
