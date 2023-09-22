/* 
 * File:   ecu_keypad.c
 * Author: ENG HOSAM
 *
 * Created on July 23, 2023, 1:46 AM
 */

#include "ecu_keypad.h"

static const uint8 btn_value[ECU_KEYBAD_ROW][ECU_KEYBAD_COLUMNS]={
                                                                    {'7', '8', '9', '/'},
                                                                    {'4', '5', '6', '*'},
                                                                    {'1', '2', '3', '-'},
                                                                    {'#', '0', '=', '+'},
                                                                 };


/**
 * @brief Initialize the assigned pin to be OUTPUT 
 * @param _keypad_obj
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0, columns_counter = 0;
    if(NULL == _keypad_obj){
       ret = E_NOT_OK; 
    }
    else{
        for(rows_counter = 0; rows_counter < ECU_KEYBAD_ROW; rows_counter++){
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = 0; columns_counter < ECU_KEYBAD_COLUMNS; columns_counter++){
            ret = gpio_pin_direction_initialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}
/**
 * 
 * @param _keypad_obj
 * @param value
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_rows_counter = 0, l_columns_counter = 0, l_counter = 0;
    uint8 column_logic = 0;
    if((NULL == _keypad_obj) || (NULL == value)){
       ret = E_NOT_OK; 
    }
    else{
        for(l_rows_counter = 0; l_rows_counter < ECU_KEYBAD_ROW; l_rows_counter++){
            for(l_counter = 0; l_counter < ECU_KEYBAD_ROW; l_counter++){
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
            }
            gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
            for(l_columns_counter = 0; l_columns_counter < ECU_KEYBAD_COLUMNS; l_columns_counter++){
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic){
                    *value = btn_value[l_rows_counter][l_columns_counter];
                }
            }
        }
    }
    return ret;
}