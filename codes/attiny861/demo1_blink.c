/*
 * Demo1_Blink_PB0.c
 *
 * Created: 03/06/2020 14:53:26
 * Author : Pablo González Robes
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0b00001000;          // Set PB3 (PORTB, Bit3) to be output
	//DDRB |= (1<<PORTB3);   //Set the Data Direction Register to output
    while (1) 
    {
				//Hard blinking
		/*
		PORTB = 0b00000011;    // Set PB0 HIGH
		_delay_ms(1000);
		PORTB = 0b00000000;    // set PB0 LOW
		_delay_ms(1000);
		*/
		
		//Bitwise blinking
	
		PORTB |=(1<< PORTB3);
		_delay_ms(1000);
		PORTB &= ~(1 << PORTB3);
		_delay_ms(1000);
		
		
		//Toggle led
		/*
		PORTB ^= (1 << PORTB3);
		_delay_ms(100);
		*/
    }
}

