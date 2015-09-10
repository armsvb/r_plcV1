/******************************************************************************
     * File: f_rele.c
     * Description: модуль организации обработки меню
     * Created: 01 авг 2015
     * Copyright:
     * Author: Александр Шабуров
     * Email: alex38779@gmail.com

******************************************************************************/

/*инклудим*/
#include "rele.h"

/*параметры для чтения массива настроек*/
#define MENU_GROUP1 0
#define MENU_GROUP2 1
#define MENU_GROUP3 2
#define MENU_PARAMETR0 0
#define MENU_PARAMETR1 1
#define MENU_PARAMETR2 2
#define MENU_PARAMETR3 3
#define MENU_PARAMETR4 4
#define MENU_PARAMETR5 5
#define MENU_PARAMETR6 6
#define MENU_PARAMETR7 7

/*переменные для обработки переходов по меню*/
static uint8_t menu_lvl;
static uint8_t menu_lvl_1 = 0;
static uint8_t menu_lvl_2 = 0;
static uint8_t menu_lvl_setting = 0;
static uint16_t menu_setting;

/*параметры меню*/
/*настройка года*/
uint8_t menuYear;
/*настройка месяца*/
uint8_t menuMoon
/*настройка дня*/
uint8_t menuDay;
/*настройка часов*/
uint8_t menuHour;
/*настройка минут*/
uint8_t menuMinute;
/*настройка режима индикации*/
uint8_t menuRejimIndication;
/*реле 1 активно ли*/
uint8_t menuSostRele1;
/*режим работы 1 реле*/
uint8_t menuRejimWorkRele1;
/*1 параметр*/
uint8_t menuParametrRele1;
/*2 параметр*/
uint8_t menuParametrRele2;
/*3 параметр*/
uint8_t menuParametrRele3;
/*4 параметр*/
uint8_t menuParametrRele4;
/*5 параметр*/
uint8_t menuParametrRele5;
/*версия прошики*/
uint8_t menuVersion;
/*серийный номер*/
uint8_t menuSerNumber;
/*дата прошивки*/
uint8_t menuDateFrimware;
/*коррекция хода часов*/
uint8_t menuCoreectionTime;

/*загрузка параметров меню*/
void menuInit()
{
	/*1 группа*/
	menuYear = setting_rele[MENU_GROUP1][MENU_PARAMETR0];
	menuMoon = setting_rele[MENU_GROUP1][MENU_PARAMETR1];
	menuDay = setting_rele[MENU_GROUP1][MENU_PARAMETR2];
	menuHour = setting_rele[MENU_GROUP1][MENU_PARAMETR3];
	menuMinute = setting_rele[MENU_GROUP1][MENU_PARAMETR4];
	menuRejimIndication = setting_rele[MENU_GROUP1][MENU_PARAMETR5];
	menuCoreectionTime = setting_rele[MENU_GROUP1][MENU_PARAMETR6];
	/*2 группа*/
	menuSostRele1 = setting_rele[MENU_GROUP2][MENU_PARAMETR0];
	menuRejimWorkRele1 = setting_rele[MENU_GROUP2][MENU_PARAMETR1];
	//menuParametrRele1 = setting_rele[MENU_GROUP2][MENU_PARAMETR2];
	//menuParametrRele2 = setting_rele[MENU_GROUP2][MENU_PARAMETR3];
	//menuParametrRele3 = setting_rele[MENU_GROUP2][MENU_PARAMETR4];
	//menuParametrRele4 = setting_rele[MENU_GROUP2][MENU_PARAMETR5];
	//menuParametrRele5 = setting_rele[MENU_GROUP2][MENU_PARAMETR6];
	/*3 группа*/
	menuVersion = setting_rele[MENU_GROUP3][MENU_PARAMETR0];
	menuSerNumber = setting_rele[MENU_GROUP2][MENU_PARAMETR1];
	menuDateFrimware = setting_rele[MENU_GROUP2][MENU_PARAMETR2];
}

/*обработка кнопок*/
void menu_button()
{
	/*первый уровень*/
	if(menu_lvl == 0)
	{
		/*вверх по меню*/
		if((PIND & (1<<btn_up))==0)
		{
			menu_lvl_1++;
			if(menu_lvl_1 > lengthFirstMenuGr)
			{
				menu_lvl_1 = 3;
			}
			_delay_ms(150);
		}
		if((PIND & (1<<btn_down))==0)
		{
			menu_lvl_1--;
			if(menu_lvl_1 < 0)
			{
				menu_lvl_1 = 0;
			}
			_delay_ms(150);
		}
		if((PIND & (1<<btn_ok))==0)
		{
			menu_lvl = 1;
			_delay_ms(150);
		}
	}
	/*второй уровень*/
	if(menu_lvl == 1)
	{
		if((PIND & (1<<btn_up))==0)
		{
			menu_lvl_2++;
			if(menu_lvl_2 > lengthMenuSecond[menu_lvl_1])
			{
				menu_lvl_2 = lengthMenuSecond[menu_lvl_1];
			}
			_delay_ms(150);
		}
		if((PIND & (1<<btn_down))==0)
		{
			menu_lvl_2--;
			if (menu_lvl_2 == 0)
			{
				menu_lvl_2 = 0;
			}
			_delay_ms(150);
		}
		if((PIND & (1<<btn_ok))==0)
		{
			menu_setting = setting_rele[menu_lvl_1][menu_lvl_2];
			menu_lvl = 2;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_back))==0)
		{
			menu_lvl = 0;
			_delay_ms(150);
		}
	}
	/*третий уровень*/
	if(menu_lvl == 2)
	{
		if((PIND & (1<<btn_up))==0)
		{
			menu_setting++;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_down))==0)
		{
			menu_setting--;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_ok))==0)
		{
			//menu_lvl = 1;
			setting_rele[menu_lvl_1][menu_lvl_2] = menu_setting;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_back))==0)
		{
			menu_lvl = 1;
			_delay_ms(150);
		}
	}
}

/*обработка меню*/
void menu()
{
	menuInit();
	switch (menu_lvl)
	{
		/*первый уровень*/
		case 0:
			menu_button();
			send_buffer(11, 10, 0, menu_lvl_1);
			break;
		/*второй уровень*/
		case 1:
			menu_button();
			send_buffer(11, menu_lvl_1, 10, menu_lvl_2);
			break;
		/*третий уровень*/
		case 2:
		/*тест*/
			menu_button();
			/*if ((menu_lvl_1 == 1) and (menu_lvl_2 == 0))
			{
				send_buffer(17,10,10,menu_setting);
			}
			send_buffer(0, 0, 0, menu_setting);
			*/
			/*если больше*/
			if(setting_rele[menu_lvl_1][menu_lvl_2] > settingMenuUp[menu_lvl_1][menu_lvl_2])
			{
				setting_rele[menu_lvl_1][menu_lvl_2] = settingMenuUp[menu_lvl_1][menu_lvl_2]
			}
			/*если меньше*/
			if(setting_rele[menu_lvl_1][menu_lvl_2] == settingMenuDown[menu_lvl_1][menu_lvl_2])
			{
				setting_rele[menu_lvl_1][menu_lvl_2] = settingMenuDown[menu_lvl_1][menu_lvl_2]
			}
			/*выводим на индикатор*/
			/*продумать режим индикации параметров*/
			break;
	}
}
