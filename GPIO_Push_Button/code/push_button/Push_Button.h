/*
 * Push_Button.h
 *
 *  Created on: Jul 1, 2022
 *      Author: Mahmoud_Mohamed
 */

#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_
/*************************** Includes *******************************/
#include <avr/io.h>
#include <util/delay.h>
#include "../LED/LED.h"
/*************************** Definitions ****************************/
// used for synchronization
#ifndef kick
#define kick()	asm("NOP")
#endif

/*************************************************************
 *	struct to define push button registers and pin.
 */
typedef struct push_button{
	// Data Direction register.
	volatile uint8_t* DDR;

	// PIN register.
	volatile uint8_t* PIN;

	// LED pin.
	uint8_t pin;

}GPIO_PUSH_BUTTON;

/*************************************************************
 *		push_button_cfg
 *
 *	Description
 *		used to set push button configurations.
 */
void btn_cfg(GPIO_PUSH_BUTTON *btn, volatile uint8_t* DDR, volatile uint8_t* PIN, uint8_t pin);

/*************************************************************
 *		btn_init
 *
 *	Description
 *		used to initialize push button configured pin.
 */
void btn_init(GPIO_PUSH_BUTTON *btn);

/*************************************************************
 *		btn_read
 *
 *	Description
 *		used to initialize led configured pin.
 */
void btn_read(GPIO_PUSH_BUTTON *btn, volatile uint8_t* _value);

#endif /* PUSH_BUTTON_H_ */
