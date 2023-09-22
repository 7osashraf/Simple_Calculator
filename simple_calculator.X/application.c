/* 
 * File:   application.c
 * Author: ENG HOSAM
 *
 * Created on July 4, 2023, 12:50 AM
 */



#include "application.h"

/*	Initialize LCD & KEYPAD		*/

chr_lcd_4bit_t lcd_1 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.logic = GPIO_LOW,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin = GPIO_PIN2,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin = GPIO_PIN3,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin = GPIO_PIN4,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin = GPIO_PIN5,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW,
};
keypad_t key_1 = {
    .keypad_row_pins[0].port = PORTD_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[1].port = PORTD_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[2].port = PORTD_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[3].port = PORTD_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,  
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
};


/*  Function prototypes     */
void clearDataArrays(uint8 arr[], uint8 size);
uint16 Number_return(uint8 arr[], uint8 count);

 



/*  Global Variable     */
uint8 KeypadValue = '\0';
uint8 FirstNumber[4];
uint8 SecondNumber[4];
uint16 number1 = 0, number2 = 0;
uint8 operation = 0;
uint8 result[6];
uint8 counter = 0;




int main() {
    Std_ReturnType ret = E_NOT_OK;
    /*  Initialize Lcd & KeyPad     */
    app_initialize();
    /*  Start message   */
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 3, "Simple Calculator");
    __delay_ms(2000);
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    
    while(1){
        
        
        /*  Clear   */
        KeypadValue = '\0';
            
        clearDataArrays(FirstNumber, 4);
        clearDataArrays(SecondNumber, 4);
            
        operation = 0;
        counter = 0;
       
        /*  Get number one  */
        while(1){
 
            do{
                ret = keypad_get_value(&key_1, &KeypadValue);
                __delay_ms(200);
            }while(KeypadValue == '\0');
            
            if(KeypadValue == '/' || KeypadValue == '*' || KeypadValue == '-' || KeypadValue == '+'){
                operation = KeypadValue;
                ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter+1, KeypadValue);
                KeypadValue = '\0';
                break;
            }
            FirstNumber[counter] = KeypadValue;
            counter++;
            ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter, KeypadValue);
            KeypadValue = '\0';
        }
        
        
        /*  Get number two  */
        uint8 counter2 = counter + 1;
        uint8 counter3 = 0;
        while(1){
            do{
                ret = keypad_get_value(&key_1, &KeypadValue);
                __delay_ms(200);
            }while(KeypadValue == '\0');
            
            if(KeypadValue == '='){
                ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter2+1, KeypadValue);
                KeypadValue = '\0';
                break;
            }
            
            SecondNumber[counter3] = KeypadValue;
            counter2++;
            counter3++;
            ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, counter2, KeypadValue);
            KeypadValue = '\0';
        }
        
        /*  Convert number one and number two from string to numbers    */
        number1 = Number_return(FirstNumber, counter);
        number2 = Number_return(SecondNumber, counter3);
        
        /*  Operation   */
        switch(operation){
            case '/' : 
                ret = convert_short_to_string((number1 / number2), result);
                break;
            case '*' : 
                ret = convert_short_to_string((number1 * number2), result);
                break;
            case '-' : 
                ret = convert_short_to_string((number1 - number2), result);
                break;
            case '+' : 
                ret = convert_short_to_string((number1 + number2), result);
                break;
        }
        
        /*  Show result on LCD  */
        ret = lcd_4bit_send_string_pos(&lcd_1, 1, counter2+3, result);
        
        /*  Clear LCD to do another calculation */
        __delay_ms(3000);
		ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
           
    }
    return (EXIT_SUCCESS);
}



void app_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd_1);
    ret = keypad_initialize(&key_1);
}

/*  Implement the clearDataArrays function   */
void clearDataArrays(uint8 arr[], uint8 size) {
    for (uint8 i = 0; i < size; i++) {
        arr[i] = '\0';
    }
}

/*  Implement the Number_return function  */
uint16 Number_return(uint8 arr[], uint8 count){
    uint16 num = 0;
    for(int i = 0; i < count; i++){
        num = num * 10 + (arr[i] - '0'); // Convert character to integer
    }
    return num;
}

