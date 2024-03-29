/*
 * External_interrupts.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Mahmoud_Mohamed
 */
#include "External_interrupts.h"

/*=========================== Static functions ================================*/
inline static void set_bit(volatile uint8_t* reg, uint8_t bit){
	*reg |= (1<<bit);
}

inline static void clear_bit(volatile uint8_t* reg, uint8_t bit){
	*reg &= ~(1<<bit);
}

/************************************************************
 * External Interrupt Request0
 * */
void Int0_Init(EXT_INT_STATE state){
	// Set Int0 state.
	switch(state){
	case LOW_LEVEL:
		clear_bit(&MCUCR, ISC00);
		clear_bit(&MCUCR, ISC01);
		break;

	case ANY_LOGICAL:
		set_bit  (&MCUCR, ISC00);
		clear_bit(&MCUCR, ISC01);
		break;

	case FALLING_EDGE:
		clear_bit(&MCUCR, ISC00);
		set_bit  (&MCUCR, ISC01);
		break;

	case RISING_EDGE:
		set_bit(&MCUCR, ISC00);
		set_bit(&MCUCR, ISC01);
		break;

	default:
		break;
	}

	return;
}

void Int0_Start(void){

	// Enable external interrupt0.
	set_bit(&GICR, INT0);

	// Exit the function.
	return;
}

void Int0_Stop(void){

	// Disable external interrupt0;
	clear_bit(&GICR, INT0);

	// Exit the function.
	return;
}


/************************************************************
 * External Interrupt Request1
 * */
void Int1_Init(EXT_INT_STATE state){
	// Set Int1 state.
	switch(state){
	case LOW_LEVEL:
		clear_bit(&MCUCR, ISC10);
		clear_bit(&MCUCR, ISC11);
		break;

	case ANY_LOGICAL:
		set_bit  (&MCUCR, ISC10);
		clear_bit(&MCUCR, ISC11);
		break;

	case FALLING_EDGE:
		clear_bit(&MCUCR, ISC10);
		set_bit  (&MCUCR, ISC11);
		break;

	case RISING_EDGE:
		set_bit(&MCUCR, ISC10);
		set_bit(&MCUCR, ISC11);
		break;

	default:
		break;
	}
}

void Int1_Start(void){

	// Enable external interrupt1.
	set_bit(&GICR, INT1);

	// Exit the function.
	return;

}

void Int1_Stop(void){

	// Enable external interrupt1.
	clear_bit(&GICR, INT1);

	// Exit the function.
	return;
}


/************************************************************
 * External Interrupt Request2
 * */

void Int2_Init(EXT_INT_STATE state){
	// Set Int2 state.
	switch(state){
	case FALLING_EDGE:
		clear_bit(&MCUCSR, ISC2);
		break;

	case RISING_EDGE:
		set_bit(&MCUCSR, ISC2);
		break;

	default:
		break;
	}
}

void Int2_Start(void){

	// Enable external interrupt2.
	set_bit(&GICR, INT2);

	// Exit the function.
	return;
}

void Int2_Stop(void){

	// Enable external interrupt2.
	clear_bit(&GICR, INT2);

	// Exit the function.
	return;
}


