/*
 * GccApplication2.c
 *
 * Created: 17.10.2020 17:25:28
 * Author : Borissimus
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#define TIME_MODE 1
#define SETUP_MODE 0
//#define NUM_OF_DIGITS 5
#define START_DIGIT_PIN PIND0
#define END_DIGIT_PIN PIND5
#define PORT_SIZE 8
#define COM_ANODE_TYPE 1
#define COM_CATHODE_TYPE 0

void setBit(uint8_t *port, const uint8_t pin){
	*port |= (1 << pin);
}
void clrBit(uint8_t *port, const uint8_t pin){
	*port &= ~(1 << pin);
}

int main(void)
{
	uint8_t disp_type = COM_CATHODE_TYPE;
	volatile uint8_t active_digit_mask[END_DIGIT_PIN - START_DIGIT_PIN + 1];
	volatile uint8_t mask = ~(0), inv_mask = 0; 
	mask = ((mask << START_DIGIT_PIN) & (mask >> (PORT_SIZE - END_DIGIT_PIN - 1)));
	inv_mask = ~mask;
	uint8_t i = 0, k = 0;
	DDRD |= mask; 
	for (i = START_DIGIT_PIN, k = 0; i <= END_DIGIT_PIN; i++, k++) {
		if (disp_type == COM_ANODE_TYPE) {
			active_digit_mask[k] = ~(1 << i);
		} else {
			active_digit_mask[k] = (1 << i);
		}
	}
	PORTD = mask;
    /* Replace with your application code */
    while (1) 
    {
		for (i = 0; i <= END_DIGIT_PIN - START_DIGIT_PIN; i++) {
			if (disp_type == COM_ANODE_TYPE) {
				PORTD |= mask;
				PORTD &= active_digit_mask[i];
			} else {
				PORTD &= inv_mask;
				PORTD |= active_digit_mask[i];
			}
		}
    }
}

