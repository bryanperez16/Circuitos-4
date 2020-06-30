#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRB &=~ (1<<PB0);
	
	DDRB |= (1<<PB1);
	DDRB |= (1<<PB2);
    
    while (1) 
    {
		if (PINB & (1<<PB0))
		{
			PORTB &=~ (1<<PB1);
			PORTB |= (1<<PB2);
		}
		
		else{
			PORTB &=~ (1<<PB2);
			PORTB |= (1<<PB1);
		}
    }
}

