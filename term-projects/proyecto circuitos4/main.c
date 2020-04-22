/*
 * GccApplication1.c
 *
 * Created: 4/20/2020 7:02:21 PM
 * Author : ianmock
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>




int main(void)
{
	
	DDRB |= (1<<PB0);   
	DDRB &= ~(1<<PB3);	
	PORTB=
	(0 << PB0) |  
	(1<<PB3);	

	
    /* Replace with your application code */
    while (1) 
    { 
		if(PINB &(1<<PB3))
		{
			PORTB|=(1<<PB0);
			_delay_ms(100);
    }
	else 
	{ 
		PORTB &= ~(1<<PB0);
		_delay_ms(100);
}
}
}




#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>


int main(void)

{
	DDRB |= (1<<PB0); //buzzer

	DDRB &= ~(1<<PB3); //switch

	PORTB=
	(0 << PB0) //buzzer off
	| (1<<PB3); //switch pulled on

	while (1)

	{

		if(PINB &(1<<PB3))

		{
			PORTB|=(1<<PB0);
			_delay_ms(1000);
		}
		else
		{
			PORTB &= ~(1<<PB0);
			_delay_ms(1000);
		}
	}
}