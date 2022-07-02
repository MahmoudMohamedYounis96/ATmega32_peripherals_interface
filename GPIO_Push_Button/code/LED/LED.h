/*
 * LED.h
 *
 *  Created on: Jun 28, 2022
 *      Author: Mahmoud_Mohamed
 */

#ifndef LED_H_
#define LED_H_

/*************************** Includes *******************************/
#include <avr/io.h>
#include <util/delay.h>

/*************************** Definitions ****************************/
// used for synchronization
#ifndef kick
#define kick()	asm("NOP")
#endif

/*************************************************************
 * enum to define the connection state of the LED.
 */
typedef enum led_state{
	PULL_UP, PULL_DOWN
}LED_STATE;

/*************************************************************
 *	struct to define LED registers and pin.
 */
typedef struct _led{
	// Data Direction register.
	volatile uint8_t* DDR;

	// PORT register.
	volatile uint8_t* PRT;

	// LED pin.
	uint8_t pin;

	// the state of connected pin.
	LED_STATE state;

}GPIO_LED;

/*************************************************************
 *		led_cfg
 *
 *	Description
 *		used to set LED configurations.
 */
void led_cfg(GPIO_LED *_led, volatile uint8_t* DDR, volatile uint8_t* PRT, uint8_t pin, LED_STATE state);

/*************************************************************
 *		led_init
 *
 *	Description
 *		used to initialize led configured pin.
 */
void led_init(GPIO_LED *led);

/*************************************************************
 *		led_turn_on
 *
 *	Description
 *		used to set LED on.
 */
void led_turn_on(GPIO_LED *led);

/*************************************************************
 *		led_turn_off
 *
 *	Description
 *		used to set LED off.
 */
void led_turn_off(GPIO_LED *led);

/*************************************************************
 *		led_toggle
 *
 *	Description
 *		used to toggle LED in a constant time periods.
 */
#define toggle_ms
#ifdef toggle_us

#define wiat_us(time)	_delay_us(time)
void led_toggle(GPIO_LED *led, uint32_t time);

#else
#ifdef toggle_ms

#define wait_ms(time)	_delay_ms(time)
void led_toggle(GPIO_LED *led, uint16_t time);

#else

#define wait_s(time)	_delay_ms(1000*time)
void led_toggle(GPIO_LED *led, uint8_t time);

#endif // end toggle_us
#endif // end toggle_ms

#endif /* LED_H_ */
