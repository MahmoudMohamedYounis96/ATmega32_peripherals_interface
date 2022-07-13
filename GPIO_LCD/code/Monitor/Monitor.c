/*
 * Monitor.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Mahmoud_Mohamed
 */
#include "Monitor.h"

/****************************************************
 *   init_mointor()
 *
 *   	type....
 *   	 void
 *
 *   	Description
 *   	 A function to set pointer to function addresses in the above structure.
 */
void init_monitor(Liquid_Crystal_Display_16x2 monitor){
	LCD_ALPHANUMERIC_16X2 lcd;
	monitor.obj = &lcd;

	monitor.cfg = &lcd_alphnumeric_16x2_cfg;

	monitor.init = &lcd_alphnumeric_16x2_init;

	monitor.print = &lcd_alphnumeric_16x2_print;
}

