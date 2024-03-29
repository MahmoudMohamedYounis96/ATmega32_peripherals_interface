/*
 * main.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Mahmoud_Mohamed
 */
#include "External_interrupts/External_interrupts.h"

inline static void toggle_bit(volatile uint8_t* reg, uint8_t bit){
	*reg ^= (1<<bit);
}

int main(void){
	// Initialize LEDs's DDR.
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2);

	// LEDs are initially low.
	PORTC &= ~(1<<PC0) & ~(1<<PC1) & ~(1<<PC2);

	// External Interrupt0.
	Int0_Init(LOW_LEVEL);
	Enable_Global_Interrupt();
	Int0_Start();

	// External Interrupt1.
	Int1_Init(ANY_LOGICAL);
	Int1_Start();

	// External Interrupt2.
	Int2_Init(RISING_EDGE);
	Int2_Start();

	while(1);

	return 0;
}

ISR(INT0_vect){
	toggle_bit(&PORTC, PC0);
}

ISR(INT1_vect){
	toggle_bit(&PORTC, PC1);
}

ISR(INT2_vect){
	toggle_bit(&PORTC, PC2);
}
