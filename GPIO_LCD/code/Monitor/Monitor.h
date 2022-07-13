/*
 * Monitor.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Mahmoud_Mohamed
 */

#ifndef MONITOR_H_
#define MONITOR_H_

/* ============================ includes ============================ */
#include"../lcd/lcd_alphanumeric_16x2.h"

/* ============================ User Area ============================ */
/**************************************************
 * This structure allows the user to control lcd
 *  with some developing restrictions.
 */
typedef struct Alphanumeric_Display_16x2{
	// lcd object.
	LCD_ALPHANUMERIC_16X2 *obj;

	// Configuration  function.
	void (*cfg)(LCD_ALPHANUMERIC_16X2* plcd, REGISTER data_ddr, REGISTER data_port, REGISTER control_ddr, REGISTER control_port, uint8_t data_pins[4], uint8_t rs, uint8_t en,LCD_ALPHANUMERIC_16X2_MODE mode);

	// Initialization function.
	void (*init)(LCD_ALPHANUMERIC_16X2* plcd);

	// Print function.
	void (*print)(LCD_ALPHANUMERIC_16X2* plcd, void *ptr_data, _format data);

}Liquid_Crystal_Display_16x2;

/****************************************************
 *   init_mointor()
 *
 *   	type....
 *   	 void
 *
 *   	Description
 *   	 A function to set pointer to function addresses in the above structure.
 */
void init_monitor(Liquid_Crystal_Display_16x2 monitor);

#endif /* MONITOR_H_ */