/*
 * Demo5_ExtInterrupts.c
 *
 * Created: 10/06/2020 0:14:33
 * Author : Pablo González Robles
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect){
	if( (PINB & (1<<PINB2)) == 0){
		PORTB |= (1<<PB0);
		}else{
		PORTB &= ~(1<<PB0);
	}
}


int main(void)
{
	DDRB |= (1<<PB0) | (1<<PB4);
	DDRB &= ~(1<<PB2);

	PORTB |=(1<<PB2);

	PORTB &= ~(1<<PB0);

	GIMSK |= (1<<INT0);
	sei();

	MCUCR |=(1<<ISC00);
	MCUCR &= ~(1<<ISC01);

	while(1)
	{
		PORTB ^= (1<<PB4);
		_delay_ms(200);
	}
}

