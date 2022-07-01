/*
 * File  : main.c
 *
 *  Purpose : Generic application start
 *
 *   Created on: Jun 28, 2022
 *
 *      Author: Mahmoud_Mohamed
 */

/*********************** includes ***************************/
#include <avr/io.h>
#include <util/delay.h>
#include "LED/LED.h"

/*********************************************************
 * 		main()
 *
 * 	Description : Application entry point.
 */

int main(void)
{
	// create a GPIO_LED object.
	GPIO_LED green_led;

	// set green led configuration.
	led_cfg(&green_led, &DDRD, &PORTD, PD0, PULL_UP);

	// init green led;
	led_init(&green_led);

	/******************************************************************************
	 * Super Loop
	 */
	for(;;){

		// toggle LED every one second.
		led_toggle(&green_led, 1);
	}
	return 0;
}


