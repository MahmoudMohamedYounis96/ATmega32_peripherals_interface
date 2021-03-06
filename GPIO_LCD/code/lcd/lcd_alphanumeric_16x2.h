/*
 * lcd_alphanumeric_16x2.h
 *
 *  Created on: Jul 4, 2022
 *      Author: Mahmoud_Mohamed
 *       a Wireless Embedded Software Engineer @ El Sewedy Elctrometer Group....
 *        	Communication Team, RF solutions Firmware Developer...
 */

#ifndef LCD_ALPHANUMERIC_16X2_H_
#define LCD_ALPHANUMERIC_16X2_H_

/*======================== includes =====================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_alphanumeric_16x2_commands.h"

/*======================= definitions ====================*/

/***********************************************************
 * 	sync()
 * 		Description:-
 * 		  Macro function generate a software delay based on
 * 		   util/delay.h library, in advanced version this
 * 		   delay will be based on hardware delay (Timer).
 */
#ifndef sync
#define sync()	_delay_ms(5)
#endif

/*************************************************************
 * 	type defintion instead of volatile uint8_t*
 */
typedef volatile uint8_t* REGISTER;

/*************************************************************
 * 	Data structure.
 */
typedef struct _data{

	REGISTER DDR;	// Data Direction Register.

	REGISTER PRT;	// Output Port.

	uint8_t pins[4];	// Data pins.

}DATA;

/*************************************************************
 * 	Control structure.
 */
typedef struct _control{

	REGISTER DDR;	// Data Direction Register.

	REGISTER PRT;	// Output port.

	uint8_t RS;	// Register Selection pin.

	uint8_t EN;	// Enable pin.

}CONTROL;

/*************************************************************
 * 	cursor position structure.
 */
typedef struct _cursor_pos{

	uint8_t _row;

	uint8_t _column;

}CURSOR;

/*************************************************************
 * 	Opertaing mode enum.
 */
typedef enum lcd_alphanumeric_16x2_mode{
	MODE_4_BITS, MODE_8_BITS
}LCD_ALPHANUMERIC_16X2_MODE;

/*************************************************************
 * 	Data types enum.
 */
typedef enum lcd_alphanumeric_16x2_data_types{
	_c, _s, _d, _f
}_format;

/*************************************************************
 *  lcd16x2_alphanumeric strcture.
 */
typedef struct lcd_alphanuemric_16x2{

	DATA data;	// Data structure.

	CONTROL control;	// control structure.

	LCD_ALPHANUMERIC_16X2_MODE mode;	// Operating mode.

	CURSOR cursor_pos;	 // cursor position.

}LCD_ALPHANUMERIC_16X2;

/*====================================================================================================
 * 										Special functions
 *
 * 						These functions will used in another file that will give the user the ability
 * 						   and flexibility to use and operate the lcd alphanumeric 16x2 monitor.
 */
/***************************************************************
 * 	lcd_alphnumeric_16x2_cfg()
 *
 * 		type....
 * 		 void
 *
 * 		Description....
 * 		 a function used to set the hardware configuration of
 * 		 the lcd.
 */
void lcd_alphnumeric_16x2_cfg(LCD_ALPHANUMERIC_16X2* plcd, REGISTER data_ddr, REGISTER data_port,
		REGISTER control_ddr, REGISTER control_port, uint8_t data_pins[4], uint8_t rs, uint8_t en,LCD_ALPHANUMERIC_16X2_MODE mode);

/***************************************************************
 *  lcd_alphnumeric_16x2_int()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to initialize the configured hardware of the lcd.
 */
void lcd_alphnumeric_16x2_init(LCD_ALPHANUMERIC_16X2* plcd);

/***************************************************************
 *  lcd_alphnumeric_16x2_send_CMD()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send operating commands to the lcd.
 */
void lcd_alphnumeric_16x2_send_CMD(LCD_ALPHANUMERIC_16X2* plcd, uint8_t CMD);

/***************************************************************
 *  lcd_alphnumeric_16x2_send_char()
 *
 *  	type....
 *  	 static void
 *
 *  	 Description....
 *  	  a function used to send a one byte character to the lcd.
 */
void lcd_alphnumeric_16x2_send_char(LCD_ALPHANUMERIC_16X2* plcd, uint8_t BYTE);

/***************************************************************
 *  lcd_alphnumeric_16x2_send_string()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send an array of characters to the lcd.
 */
void lcd_alphnumeric_16x2_send_string(LCD_ALPHANUMERIC_16X2* plcd, char STR[]);

/***************************************************************
 *  lcd_alphnumeric_16x2_send_integer()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send signed integers to the lcd.
 */
void lcd_alphnumeric_16x2_send_int(LCD_ALPHANUMERIC_16X2* plcd, int NUM);

/***************************************************************
 *  lcd_alphnumeric_16x2_send_double()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send floats to the lcd.
 */
void lcd_alphnumeric_16x2_send_double(LCD_ALPHANUMERIC_16X2* plcd, double NUM);

/***************************************************************
 *  lcd_alphnumeric_16x2_move_cursor()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to move cursor to (row, column) position.
 */
void lcd_alphnumeric_16x2_move_curosr(LCD_ALPHANUMERIC_16X2* plcd, uint8_t row, uint8_t column);

/***************************************************************
 *  lcd_alphnumeric_16x2_clear()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to clear the lcd display.
 */
void lcd_alphnumeric_16x2_clear(LCD_ALPHANUMERIC_16X2* plcd);

/***************************************************************
 *  lcd_alphnumeric_16x2_print()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to print any data type on the lcd.
 */
void lcd_alphnumeric_16x2_print(LCD_ALPHANUMERIC_16X2* plcd, void *ptr_data, _format data);

/***************************************************************
 *  lcd_alphnumeric_16x2_Flush()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to internal data register of the lcd.
 */
void lcd_alphnumeric_16x2_flush(LCD_ALPHANUMERIC_16X2* plcd);

#endif /* LCD_ALPHANUMERIC_16X2_H_ */
