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

void Monitor_Init(Liquid_Crystal_Display_16x2* monitor){

	monitor->obj   = (LCD_ALPHANUMERIC_16X2*)malloc(sizeof(LCD_ALPHANUMERIC_16X2));

	monitor->Cfg   = &lcd_alphnumeric_16x2_cfg;

	monitor->Init  = &lcd_alphnumeric_16x2_init;

	monitor->Print = &lcd_alphnumeric_16x2_print;

	monitor->Clear = &lcd_alphnumeric_16x2_clear;

	monitor->Goto  = &lcd_alphnumeric_16x2_move_curosr;

	monitor->Flush = &lcd_alphnumeric_16x2_flush;
}

