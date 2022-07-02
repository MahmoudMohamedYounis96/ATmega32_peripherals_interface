/*
 * main.c
 *
 *  Created on: Jul 1, 2022
 *      Author: Mahmoud_Mohamed
 */

/*********************** includes ***************************/
#include <avr/io.h>
#include <util/delay.h>

#include "LED/LED.h"
#include "push_button/Push_Button.h"

/*********************************************************
 * 		main()
 *
 * 	Description : Application entry point.
 */
int main(void){

	// create led object.
	GPIO_LED green_led;

	// create push button object.
	GPIO_PUSH_BUTTON btn;

	// configure led & push button;
	led_cfg(&green_led, &DDRD, &PORTD, PD0, PULL_DOWN);
	btn_cfg(&btn, &DDRC, &PINC, PC0);

	// init led & push button.
	led_init(&green_led);
	btn_init(&btn);

	/******************************************************************************
	 * Super Loop
	 */
	volatile uint8_t value = '\0';
	for(;;){

		/********************************************************************
		 * The basic idea is if read value equal to logic one turn led on,
		 * and if read value is equal to zero turn led off.
		 */
		btn_read(&btn, &value); // read PC0 value.

		if (value == 1) {
			led_turn_on(&green_led);
			wait_ms(10);
		}else{
			led_turn_off(&green_led);
			wait_ms(10);
		}
	}

	return 0; // exit the program.
}
