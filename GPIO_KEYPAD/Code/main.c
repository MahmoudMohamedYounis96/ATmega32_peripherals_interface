/*
 * main.c
 *
 *  Created on: Jul 16, 2022
 *      Author: Mahmoud_Mohamed
 */
#include "keypad/keypad4x4.h"
#include "Monitor/Monitor.h"

int main(void){

	// Create Keypad, and Monitor object.
	Liquid_Crystal_Display_16x2 lcd;
	KeyPad_4x4 keypad;

	// Initialize the monitor.
	Monitor_Init(&lcd);

	// Define data pins.
	uint8_t data_pins[4] = {PB0, PB1, PB2, PB3};
	uint8_t row_pins[]   = {PD0, PD1, PD2, PD3};
	uint8_t col_pins[]   = {PC0, PC1, PC2, PC3};

	// keypad, and lcd configuration .
	Keypad_Cfg(&keypad, &DDRD, &PIND, &PORTD, row_pins, &DDRC, &PORTC, col_pins);
	lcd.Cfg(lcd.obj, &DDRB, &PORTB, &DDRB, &PORTB, data_pins, PB4, PB5, MODE_4_BITS);

	// keypad, and lcd initialization.
	lcd.Init(lcd.obj);
	Keypad_Init(&keypad);

	// variable used to display the pressed key.
	volatile uint8_t pressed_key = '\0';

	// Endless Loop.
	for(;;){
		// Make CPU to poll the keypad.
		Keypad_Read(&keypad);

		if(keypad.key != '\0'){
			// Print the pressed key.
			lcd.Print(lcd.obj, &keypad.key, _c);

			// return variable to NULL.
			keypad.key = '\0';

			// Wait a nop.
			kick();
		}
	}
	return 0;
}

