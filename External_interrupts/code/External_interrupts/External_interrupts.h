/*
 * External_interrupts.h
 *
 *  Created on: Jul 30, 2022
 *      Author: Mahmoud_Mohamed
 */

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

/*=========================== Includes ================================*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*=========================== Definitions ================================*/
#ifndef kick
#define Kick()	__asm__("nop");
#endif /* Kick */

/*=========================== Data Types ================================*/
typedef enum ext_int_state{
	LOW_LEVEL, ANY_LOGICAL, FALLING_EDGE, RISING_EDGE
}EXT_INT_STATE;

/*=========================== Inline Functions ================================*/
inline void Enable_Global_Interrupt(void){
	sei();
	Kick();
}
inline void Disable_Global_Interrupt(void){
	cli();
	Kick();
}
/************************************************************
 * External Interrupt Request0
 * */
void Int0_Init(EXT_INT_STATE state);

void Int0_Start(void);

void Int0_Stop(void);


/************************************************************
 * External Interrupt Request1
 * */
void Int1_Init(EXT_INT_STATE state);

void Int1_Start(void);

void Int1_Stop(void);


/************************************************************
 * External Interrupt Request2
 * */

void Int2_Init(EXT_INT_STATE state);

void Int2_Start(void);

void Int2_Stop(void);

#endif /* EXTERNAL_INTERRUPTS_H_ */
