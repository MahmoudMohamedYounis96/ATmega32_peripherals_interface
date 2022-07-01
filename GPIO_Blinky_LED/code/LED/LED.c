/*
 * LED.c
 *
 *  Created on: Jun 28, 2022
 *      Author: Mahmoud_Mohamed
 */

/*========================= Includes =============================*/
#include "LED.h"

/*************************************************************
 *		led_cfg
 *
 *	Description
 *		used to set LED configurations.
 */
void led_cfg(GPIO_LED *_led, volatile uint8_t* DDR, volatile uint8_t* PRT, uint8_t pin, LED_STATE state){

	_led->DDR = DDR;	// set data direction register.
	kick();

	_led->PRT = PRT;	// set output port register.
	kick();

	_led->pin = pin;	// set hardware connected pin.
	kick();

	_led->state = state;

	return;	// exit function.
}

/*************************************************************
 *		led_init
 *
 *	Description
 *		used to initialize led configured pin.
 */
void led_init(GPIO_LED *led){

	*led->DDR |= (1<<led->pin);	// configure led's pin as an output pin.
	kick();

	// consider the initial state of the LED is off. SO,
	switch(led->state){

	case PULL_UP:
		*led->PRT |= (1<<led->pin);
		break;

	case PULL_DOWN:
		*led->PRT &= ~(1<<led->pin);
		break;

	default:
		break;
	}
	kick();

	return; // exit the function.
}

/*************************************************************
 *		led_turn_on
 *
 *	Description
 *		used to set LED on.
 */
void led_turn_on(GPIO_LED *led){

	// take in consideration the led connected state.
	switch(led->state){

	case PULL_UP:
		*led->PRT &= (~1<<led->pin);
		break;

	case PULL_DOWN:
		*led->PRT |= (1<<led->pin);
		break;

	default:
		break;
	}
	kick();

	return; // exit the function.
}

/*************************************************************
 *		led_turn_off
 *
 *	Description
 *		used to set LED off.
 */
void led_turn_off(GPIO_LED *led){

	// consider the initial state of the LED is off. SO,
	switch(led->state){

	case PULL_UP:
		*led->PRT |= (1<<led->pin);
		break;

	case PULL_DOWN:
		*led->PRT &= ~(1<<led->pin);
		break;

	default:
		break;
	}
	kick();

	return; // exit the function.
}

/*************************************************************
 *		led_toggle
 *
 *	Description
 *		used to toggle LED in a constant time periods.
 */
#define toggle_s
#ifdef toggle_us

#define wiat_us(time)	_delay_us(time)
void led_toggle(GPIO_LED *led, uint32_t time){

	*led->PRT ^= (1<<led->pin);
	wiat_us(time);

	return; // exit the function.
}

#else
#ifdef toggle_ms

#define wait_ms(time)	_delay_ms(time)
void led_toggle(GPIO_LED *led, uint16_t time){

	*led->PRT ^= (1<<led->pin);
	wait_ms(time);

		return; // exit the function.
}

#else

#define wait_s(time)	_delay_ms(1000*time)
void led_toggle(GPIO_LED *led, uint8_t time){

	*led->PRT ^= (1<<led->pin);
	wait_s(time);

	return; // exit the function.
}

#endif // end toggle_us
#endif // end toggle_ms
