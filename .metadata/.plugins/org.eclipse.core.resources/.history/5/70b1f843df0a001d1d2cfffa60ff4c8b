/*
 * keypad4x4.h
 *
 *  Created on: Jul 16, 2022
 *      Author: Mahmoud_Mohamed
 */

#ifndef KEYPAD4X4_H_
#define KEYPAD4X4_H_

/************************************* Includes *************************************/
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

/************************************* Definitions ***********************************/
#ifndef kick
#define kick()	__asm__("nop");
#endif /* Kick */

#ifndef REGISTER
#define REGISTER	volatile uint8_t*
#endif /* REGISTER */

#ifndef NUM_ROW
#define NUM_ROW		4
#endif /* NUM_ROW */

#ifndef NUM_COL
#define NUM_COL		4
#endif /* NUM_COL */

// Note that: the rows will be used as input pins.
typedef struct __row{

	REGISTER DDR;

	REGISTER PORT;

	REGISTER PIN;

	uint8_t pins[4];

}__ROW;

// Note that: the columns will be used as output pins.
typedef struct __col{

	REGISTER DDR;

	REGISTER PORT;

	uint8_t pins[4];

}__Col;


typedef struct keypad4x4{

	__ROW row;

	__Col col;

	uint8_t key;

}KeyPad_4x4;

/********************************** Functions ***************************************************/

/*=================================================================================================*/

void Keypad_Cfg(KeyPad_4x4* Ptr_Keypad, REGISTER row_DDR, REGISTER row_PIN, REGISTER row_PORT, uint8_t row_pins[],
				REGISTER col_DDR, REGISTER col_PORT, uint8_t col_pins[]);

/*=================================================================================================*/

void Keypad_Init(KeyPad_4x4* Ptr_Keypad);

/*=================================================================================================*/

void Keypad_Read(KeyPad_4x4* Ptr_Keypad);

#endif /* KEYPAD4X4_H_ */
