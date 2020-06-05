/*
 * Demo2_Digital_IOs.c
 *
 * Created: 03/06/2020 17:35:15
 * Author : Pablo González Robles
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<PORTB3);   //Set the Data Direction Register to output
	DDRA &= ~(1<<PORTA7);	//Set the Data Direction Register for the switch to input
	
	PORTB = (0 << PORTB3); //Output LOW state (Sink)
	PORTA = (1<<PORTA7);	//Enable the pull-up resistor for the switch
	
	while (1)
	{
		if (PINA & (1<<PORTA7))
		{
			PORTB|=(1<<PORTB3);
			_delay_ms(100);
		}
		
		else
		{
			PORTB &=~(1<<PORTB3);
			_delay_ms(100);
		}

	}
}

