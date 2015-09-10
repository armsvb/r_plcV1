/*
 * menu.cpp
 *
 * Created: 01.08.2015 12:54:05
 *  Author: Alexander Shaburov
 */ 

#include "rele.h"

static uint8_t menu_lvl;
uint8_t menu_lvl_1 = 0,
		menu_lvl_2 = 0,
		menu_lvl_setting = 0;
uint16_t menu_setting;

void menu_button(){
	/*первый уровень*/
	if(menu_lvl == 0){
		if((PIND & (1<<btn_up))==0){
			menu_lvl_1++;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_down))==0){
			menu_lvl_1--;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_ok))==0){
			menu_lvl = 1;
			_delay_ms(150);
		}
	}
	/*второй уровень*/
	if(menu_lvl == 1){
		if((PIND & (1<<btn_up))==0){
			menu_lvl_2++;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_down))==0){
			menu_lvl_2--;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_ok))==0){
			menu_setting = setting_rele[menu_lvl_1][menu_lvl_2];
			menu_lvl = 2;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_back))==0){
			menu_lvl = 0;
			_delay_ms(150);
		}
	}
	/*третий уровень*/
	if(menu_lvl == 2){		
		if((PIND & (1<<btn_up))==0){			
			menu_setting++;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_down))==0){
			menu_setting--;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_ok))==0){
			//menu_lvl = 1;
			setting_rele[menu_lvl_1][menu_lvl_2] = menu_setting;
			_delay_ms(150);
		}
		if((PIND & (1<<btn_back))==0){
			menu_lvl = 1;
			_delay_ms(150);
		}
	}		
}

void menu_init(){	
}

void menu(){
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
			menu_button();			
			if ((menu_lvl_1 == 1) and (menu_lvl_2 == 0))
			{
				send_buffer(17,10,10,menu_setting);
			}
			send_buffer(0, 0, 0, menu_setting);
			break;
	}	
}