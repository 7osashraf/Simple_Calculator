/* 
 * File:   ecu_keypad.h
 * Author: ENG HOSAM
 *
 * Created on July 23, 2023, 1:46 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
/* ------------------Includes------------------*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL/GPIO/hal_gpio.h"
/* ------------------Macro Declarations------------------*/
#define ECU_KEYBAD_ROW      4
#define ECU_KEYBAD_COLUMNS  4

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYBAD_ROW];
    pin_config_t keypad_columns_pins[ECU_KEYBAD_COLUMNS];
}keypad_t;
/* ------------------Software Interface Declarations------------------*/
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);


#endif	/* ECU_KEYPAD_H */

