/*
 * lcd_alphanumeric_16x2.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Mahmoud_Mohamed
 */

/*============================== includes =============================*/
#include "lcd_alphanumeric_16x2.h"
#include "lcd_alphanumeric_16x2_commands.h"

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
void lcd_alphnumeric_16x2_cfg(LCD_ALPHANUMERIC_16X2* lcd, REGISTER data_ddr, REGISTER data_port,
		REGISTER control_ddr, REGISTER control_port, uint8_t _data_pins[4], uint8_t rs, uint8_t en,LCD_ALPHANUMERIC_16X2_MODE mode){

	/* (1)Hardware configuration */

	// (1.1)Data configuration.
	lcd->data.DDR = data_ddr;
	lcd->data.PRT = data_port;
	for(uint8_t i=0; i<4; i++){
		lcd->data.pins[i] = _data_pins[i];
	}

	// (1.2)Control configuration.
	lcd->control.DDR = control_ddr;
	lcd->control.PRT = control_port;
	lcd->control.RS = rs;
	lcd->control.EN = en;

	return; // exit the function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_int()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to initialize the configured hardware of the lcd.
 */
void lcd_alphnumeric_16x2_init(LCD_ALPHANUMERIC_16X2* lcd){

	// Configure Data pins as output pins with logic zero as an initial value.
	*lcd->data.DDR |=  ( (1<<lcd->data.pins[0]) | (1<<lcd->data.pins[1]) | (1<<lcd->data.pins[2]) | (1<<lcd->data.pins[3]) );
	sync();
	*lcd->data.PRT &= ~( (1<<lcd->data.pins[0]) | (1<<lcd->data.pins[1]) | (1<<lcd->data.pins[2]) | (1<<lcd->data.pins[3]) );
	sync();

	// Configure Control pins as output pins with logic zero as an initial value.
	*lcd->control.DDR |=  ( (1<<lcd->control.RS) | (1<<lcd->control.EN) );
	sync();
	*lcd->control.PRT &= ~( (1<<lcd->control.RS) | (1<<lcd->control.EN) );
	sync();

	_delay_ms(20);	// lcd power on waiting time.

	/******** Send some commands to initialize lcd ********/
	lcd_alphnumeric_16x2_send_CMD(lcd, __init__);
	sync();

	lcd_alphnumeric_16x2_send_CMD(lcd, _4_bits_2_lines_5x8_dots);
	sync();

	lcd_alphnumeric_16x2_send_CMD(lcd, display_on_cursor_on_no_blinking);
	sync();

	lcd_alphnumeric_16x2_send_CMD(lcd, increment_cursor);
	sync();

	lcd_alphnumeric_16x2_send_CMD(lcd, clear_display);
	sync();

	lcd_alphnumeric_16x2_send_CMD(lcd, Return_Home);
	sync();

	return; // exit the function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_send_CMD()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send operating commands to the lcd.
 */
void lcd_alphnumeric_16x2_send_CMD(LCD_ALPHANUMERIC_16X2* plcd, uint8_t CMD){

	_Bool bit;

	// ******************************* send upper nibble of command *******************************
	for(uint8_t i=4; i<=7; i++){

		bit =  (_Bool)(CMD&(1<<i));

		if(bit == 1){
			*plcd->data.PRT |= (1<<plcd->data.pins[i-4]);
		}
		else if(bit == 0){
			*plcd->data.PRT &= ~(1<<plcd->data.pins[i-4]);
		}
		else{
			// Nothing.
		}
		asm("NOP");	// Synchronization
	}

	// RS=0, command register.
	*plcd->control.PRT &= ~(1<<plcd->control.RS);

	// Enable pulse.
	*plcd->control.PRT |= (1<<plcd->control.EN);
	_delay_us(2500);
	*plcd->control.PRT &= ~(1<<plcd->control.EN);
	_delay_us(2500);

	// ******************************* send lower nibble of command *******************************
	for(uint8_t i=0; i<=3; i++){

		bit =  (_Bool)(CMD&(1<<i));

		if(bit == 1){
			*plcd->data.PRT |= (1<<plcd->data.pins[i]);
		}
		else if(bit == 0){
			*plcd->data.PRT &= ~(1<<plcd->data.pins[i]);
		}
		else{
			// Nothing.
		}
		asm("NOP");	// Synchronization
	}

	// Enable pulse.
	*plcd->control.PRT |= (1<<plcd->control.EN);
	_delay_us(2500);
	*plcd->control.PRT &= ~(1<<plcd->control.EN);
	_delay_us(2500);

	return; // exit function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_send_string()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send an array of characters to the lcd.
 */
void lcd_alphnumeric_16x2_send_char(LCD_ALPHANUMERIC_16X2* plcd, uint8_t BYTE){

	_Bool bit;

	// ****************************** send upper nibble of character ******************************
	for(uint8_t i=4; i<=7; i++){

		bit = (_Bool)(BYTE&(1<<i));

		if(bit == 1){
			*plcd->data.PRT |= (1<<plcd->data.pins[i-4]);
		}
		else if(bit == 0){
			*plcd->data.PRT &= ~(1<<plcd->data.pins[i-4]);
		}
		else{
			// Nothing.
		}
		asm("NOP");	// Synchronization
	}

	// RS=1, data register.
	*plcd->control.PRT |= (1<<plcd->control.RS);

	// Enable pulse.
	*plcd->control.PRT |= (1<<plcd->control.EN);
	_delay_us(2500);
	*plcd->control.PRT &= ~(1<<plcd->control.EN);
	_delay_us(2500);

	// send lower nibble of command.
	for(uint8_t i=0; i<=3; i++){

		bit = (_Bool)(BYTE&(1<<i));

		if(bit == 1){
			*plcd->data.PRT |= (1<<plcd->data.pins[i]);
		}
		else if(bit == 0){
			*plcd->data.PRT &= ~(1<<plcd->data.pins[i]);
		}
		else{
			// Nothing.
		}
		asm("NOP");	// Synchronization
	}

	// Enable pulse.
	*plcd->control.PRT |= (1<<plcd->control.EN);
	_delay_us(2500);
	*plcd->control.PRT &= ~(1<<plcd->control.EN);
	_delay_us(2500);

	return; // exit function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_send_string()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send an array of characters to the lcd.
 */
void lcd_alphnumeric_16x2_send_string(LCD_ALPHANUMERIC_16X2* plcd, char STR[]){

	// Get the length of the string.
	uint8_t str_length = strlen(STR);

	// Send string byte by byte.
	for(uint8_t i=0; i<str_length; i++){
		lcd_alphnumeric_16x2_send_char(plcd, STR[i]);
	}

	return; // exit the function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_send_integer()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send integers to the lcd.
 */
void lcd_alphnumeric_16x2_send_int(LCD_ALPHANUMERIC_16X2* plcd, int NUM){

	// Destination string.
	char* NUM_str = "\0";

	// Convert number to string.
	itoa(NUM, NUM_str, 10);

	// Send string to print.
	lcd_alphnumeric_16x2_send_string(plcd, NUM_str);

	// exit the function.
	return;
}

/***************************************************************
 *  lcd_alphnumeric_16x2_send_double()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to send floats to the lcd.
 */
void lcd_alphnumeric_16x2_send_double(LCD_ALPHANUMERIC_16X2* plcd, double NUM){

	// Destination strings.
	char* str = "\0";

	// Convert the float number into string.
	int _prec = 3; 	// Determines the number of digits after the decimal sign.
	int _width = 4; // The minimum field width of the output string (including the \c '.' and the possible
					//sign for negative values) is given in \c width,
	dtostrf(NUM, _width, _prec,str);

	// Send the string to print.
	lcd_alphnumeric_16x2_send_string(plcd, str);

	// exit the function.
	return;
}

/***************************************************************
 *  lcd_alphnumeric_16x2_move_cursor()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to move cursor to (row, column) position.
 */
void lcd_alphnumeric_16x2_move_curosr(LCD_ALPHANUMERIC_16X2* plcd, uint8_t row, uint8_t column){

	if ( (row == 0) && (column < 16) ){
		// Command of first row and required position<16
		lcd_alphnumeric_16x2_send_CMD(plcd, (column & 0x0F)|force_cusror_to_start_with_1st_row);
	}
	else if ((row == 1) && (column < 16)){
		// Command of second row and required position<16
		lcd_alphnumeric_16x2_send_CMD(plcd, (column & 0x0F)|force_cusror_to_start_with_2nd_row);
	}
	else{
		// Do Nothing.
	}

	return; // exit the function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_clear()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to clear the lcd display.
 */
void lcd_alphnumeric_16x2_clear(LCD_ALPHANUMERIC_16X2* plcd){

	// Send command to clear lcd.
	lcd_alphnumeric_16x2_send_CMD(plcd, clear_display);

	// Send command to return to the home position.
	lcd_alphnumeric_16x2_send_CMD(plcd, Return_Home);

	return; // exit the function.
}

/***************************************************************
 *  lcd_alphnumeric_16x2_print()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to print any data type on the lcd.
 */
void lcd_alphnumeric_16x2_print(LCD_ALPHANUMERIC_16X2* plcd, void *ptr_data, _format data){

	// Check data type, then print.
	switch(data){

	case _c:
		lcd_alphnumeric_16x2_send_char(plcd, *(uint8_t *)ptr_data);
		break;

	case _s:
		lcd_alphnumeric_16x2_send_string(plcd, (char*)ptr_data);
		break;

	case _d:
		lcd_alphnumeric_16x2_send_int(plcd, *(int*)ptr_data);
		break;

	case _f:
		lcd_alphnumeric_16x2_send_double(plcd, *(double*)ptr_data);
		break;

	default:
		break;
	}

	// exit the function.
	return;
}

/***************************************************************
 *  lcd_alphnumeric_16x2_Flush()
 *
 *  	type....
 *  	 void
 *
 *  	 Description....
 *  	  a function used to internal data register of the lcd.
 */
void lcd_alphnumeric_16x2_flush(LCD_ALPHANUMERIC_16X2* plcd){

	uint8_t* buffer = "\0";

	lcd_alphnumeric_16x2_send_string(plcd, buffer);

}
