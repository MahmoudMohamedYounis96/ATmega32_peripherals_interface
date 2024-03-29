/*
 * main.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Mahmoud_Mohamed
 */
// ==================== Includes =====================
// >> Standard AVR libraries.
#include <avr/io.h>
#include <avr/interrupt.h>

// >> Util delay library.
#include <util/delay.h>

// >> Standard integer type library.
#include <stdint.h>

/*****************************************************
 * How To generate a PWM using timer0 ?
 * !1! Initialize TCCR0.
 * !2! Load OCR0 with duty cycle value.
 * !3! Configure OC0 as an output pin.
 *
 * TCCR0 = FOC0 |	WGM00   |	COM01   |	COM00   |	WGM01   |	CS02   |   CS01   | CS00
 * 0x61  =  0	|     1     |     1     |     0     |     0     |     0    |    0     |  1
 * Waveform Generation Mode Bit Description = Fast PWM.
 * Clear OC0 on Compare Match, set OC0 at BOTTOM, (non-inverting mode).
 * Select prescaler let's say F_PWM = F_CPU/1, No prescaler.
 *
 */

// ==================== Generation function ===================
void GeneratSqaurePWM_Timer0(void){
	// Configure OC0{PB3} pin as output.
	DDRB |= (1<<PB3);

	// Load TCCR2 with the control value.
	TCCR0 = 0x61;

	// Load OCR0 with compare value, this value will give a 50% duty cycle.
	OCR0 = 127;

	// Exit the function.
	return;
}

// ==================== Main function ===================
int16_t main(void){
	// Generate square wave.
	GeneratSqaurePWM_Timer0();

	// Endless loop.
	uint8_t DutyCycler0 = 0;

	for(;;){
		for(DutyCycler0=0; DutyCycler0<255; DutyCycler0++){
			OCR0 = DutyCycler0;
			_delay_ms(10);
		}
		_delay_ms(1000);
		for(DutyCycler0=255; DutyCycler0>0; DutyCycler0--){
			OCR0 = DutyCycler0;
			_delay_ms(10);
		}
	}

	// Return value.
	return 0;
}


