/*
 * keypad4x4.c
 *
 *  Created on: Jul 16, 2022
 *      Author: Mahmoud_Mohamed
 */
#include "keypad4x4.h"

/***************************************************************************************************
 * Key Map
 */
static const char map[4][4] = {
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'c', '0', '=', '+'}
};

/*=================================================================================================*/

void Keypad_Cfg(KeyPad_4x4* Ptr_Keypad, REGISTER row_DDR, REGISTER row_PIN,  REGISTER row_PORT, uint8_t row_pins[], REGISTER col_DDR, REGISTER col_PORT, uint8_t col_pins[]){

	Ptr_Keypad->row.DDR = row_DDR;

	Ptr_Keypad->row.PORT = row_PORT;

	Ptr_Keypad->row.PIN = row_PIN;

	for(uint8_t i=0; i<NUM_ROW; i++){
		Ptr_Keypad->row.pins[i] = row_pins[i];
	}

	// ****=****=****=****=****=****

	Ptr_Keypad->col.DDR = col_DDR;

	Ptr_Keypad->col.PORT = col_PORT;

	for(uint8_t i=0; i<NUM_COL; i++){
		Ptr_Keypad->col.pins[i] = col_pins[i];
	}

	return;
}

/*=================================================================================================*/

void Keypad_Init(KeyPad_4x4* Ptr_Keypad){

	/* Rows */
	for (uint8_t i=0; i<NUM_ROW; i++) {
		// 1.Configure all row_pins as input pins.
		*Ptr_Keypad->row.DDR &= ~(1<<Ptr_Keypad->row.pins[i]);
		kick();

		// 2.Activate all pull-up resistors.
		*Ptr_Keypad->row.PORT |= (1<<Ptr_Keypad->row.pins[i]);
		kick();
	}

	/* Columns */

	for (uint8_t i=0; i<NUM_COL; i++) {
		// 1.Configure all row_pins as output pins.
		*Ptr_Keypad->col.DDR |= (1<<Ptr_Keypad->col.pins[i]);
		kick();

		// 2.Set all pins to logic one.
		*Ptr_Keypad->col.PORT &= ~(1<<Ptr_Keypad->col.pins[i]);
		kick();
	}

	/* Initialize key value */

	Ptr_Keypad->key = '\0';

	return;
}

/*=================================================================================================*/

void Keypad_Read(KeyPad_4x4* Ptr_Keypad){
	/* Idea: activate only one row then read all columns.
	 * when a key is pressed i already know it's row and
	 * it's column.
	 * Note that: row is active low.
	 */
	for(uint8_t C=0; C<NUM_ROW; C++){
		// 1.Deactivate all columns.
		*Ptr_Keypad->col.PORT |= (1<<Ptr_Keypad->col.pins[0]);
		*Ptr_Keypad->col.PORT |= (1<<Ptr_Keypad->col.pins[1]);
		*Ptr_Keypad->col.PORT |= (1<<Ptr_Keypad->col.pins[2]);
		*Ptr_Keypad->col.PORT |= (1<<Ptr_Keypad->col.pins[3]);

		// 2.Activate specific columns.
		*Ptr_Keypad->col.PORT &= ~(1<<Ptr_Keypad->col.pins[C]);

		// 3.Read all rows then return key value.
		for(uint8_t R=0; R<NUM_COL; R++){
			if( (_Bool)( (*Ptr_Keypad->row.PIN)&(1<<Ptr_Keypad->row.pins[R]) ) == 0 ){
				// Set key value.
				Ptr_Keypad->key = map[R][C];

				// Debouncing the switch.
				while( (_Bool)( (*Ptr_Keypad->row.PIN)&(1<<Ptr_Keypad->row.pins[R]) ) == 0 );
			}
		}

		// Insert kick for synchronization
		kick();
	}
}
