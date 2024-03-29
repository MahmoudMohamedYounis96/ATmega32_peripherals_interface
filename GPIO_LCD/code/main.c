/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Mahmoud_Mohamed
 */

/*********************** includes ***************************/
#include <avr/io.h>
#include <util/delay.h>
#include "Monitor/Monitor.h"

/*********************************************************
 * 		main()
 *
 * 	Description : Application entry point.
 */
int main(void){
	// Create Monitor object.
	Liquid_Crystal_Display_16x2 lcd;

	Monitor_Init(&lcd);

	// Define data pins.
	uint8_t data_pins[4] = {PD0, PD1, PD2, PD3};

	// lcd configuration .
	lcd.Cfg(lcd.obj, &DDRD, &PORTD, &DDRB, &PORTB, data_pins, PB0, PB1, MODE_4_BITS);

	// lcd initialization.
	lcd.Init(lcd.obj);

	// print something.
	int a = 32000;

	lcd.Print(lcd.obj, &a, _d);

	while(1);

	return 0;
}

