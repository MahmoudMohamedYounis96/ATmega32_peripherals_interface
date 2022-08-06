/*
 * timer_delay.c
 *
 *  Created on: Jul 31, 2022
 *      Author: Mahmoud_Mohamed
 */
// Standard Libraries.
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// AVR AT_Mega32 Libraries.
#include <avr/io.h>
#include <avr/interrupt.h>

// Local Header Files.
#include "timer_delay.h"

/*====================== Functions Declarations ======================*/
void Timer0_Delay_us(uint32_t time){

	while(time != 0){
		// Load TCCR0 with the control values.
		//{Normal mode, OC0 is disconnected, and F_CPU/1 frequency prescaler.}
		TCCR0 = (uint8_t)0x1;

		// Load TCNT0 with the initial value.
		TCNT0 = (uint8_t)0xF8;

		// Wait until Timer0 Overflow.
		while(! (TIFR&(1<<TOV0)) );

		// Stop timer0.
		TCCR0 = (uint8_t)0x0;

		// Clear TOV0.
		TIFR |= (1<<TOV0);

		// Decrement the time.
		time--;
	}

	// Exit the function.
	return;
}

void Timer0_Delay_ms(uint32_t time){

	while(time != 0){
		// Load TCCR0 with the control values.
		//{Normal mode, OC0 is disconnected, and F_CPU/64 frequency prescaler.}
		TCCR0 = (uint8_t)0x3;

		// Load TCNT0 with the initial value.
		TCNT0 = (uint8_t)0x83;

		// Wait until Timer0 Overflow.
		while(! (TIFR&(1<<TOV0)) );

		// Stop timer0.
		TCCR0 = (uint8_t)0x0;

		// Clear TOV0.
		TIFR |= (1<<TOV0);

		// Decrement the time.
		time--;
	}

	// Exit the function.
	return;
}
