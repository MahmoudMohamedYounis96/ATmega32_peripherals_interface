/*
 * Push_Button.c
 *
 *  Created on: Jul 1, 2022
 *      Author: Mahmoud_Mohamed
 */

/*================================== Includes =============================*/
#include "Push_Button.h"

/*************************************************************
 *		push_button_cfg
 *
 *	Description
 *		used to set push button configurations.
 */
void btn_cfg(GPIO_PUSH_BUTTON *btn, volatile uint8_t* DDR, volatile uint8_t* PIN, uint8_t pin){

	btn->DDR = DDR;	// set data direction register.
	kick();

	btn->PIN = PIN;	// set input data register.
	kick();

	btn->pin = pin;	// set hardware connected pin.
	kick();

	return;	// exit the function.
}

/*************************************************************
 *		btn_init
 *
 *	Description
 *		used to initialize push button configured pin.
 */
void btn_init(GPIO_PUSH_BUTTON *btn){

	*btn->DDR &= ~(1<<btn->pin);	// configure button's pin as an input pin.
	kick();

	return; // exit the function.
}

/*************************************************************
 *		btn_read
 *
 *	Description
 *		used to initialize led configured pin.
 */
void btn_read(GPIO_PUSH_BUTTON *btn, volatile uint8_t* _value){

	volatile uint8_t pin = '\0';	// define a variable to store PIN register value, and initialize it to NULL.

	pin = ( (*btn->PIN) & (1<<btn->pin) ) >> btn->pin;
	kick();

	*_value = pin;	// store read value to the memory.

	return; // exit the function.
}

