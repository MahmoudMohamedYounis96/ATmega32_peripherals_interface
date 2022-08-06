/*
 * main.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Mahmoud_Mohamed
 */

/*============================= Includes ==========================*/
#include <stdio.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer_Delay/timer_delay.h"
/*============================= Main Function  ==========================*/
int main(void){

	DDRD = 0x01;

	while(1){
		PORTD ^= 0x01;
		Timer0_Delay_ms(1000);
		//Timer0_Delay_us(1000000);
	}
	return 0;
}
