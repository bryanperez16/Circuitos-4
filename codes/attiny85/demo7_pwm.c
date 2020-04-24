/*
 * Demo3_Analog_Pot.c
 *  CW turn off pot
 * Created: 25/02/2020 13:15:40
 * Author : Pablo Gonzalez Robles
 * 
 */ 

#define F_CPU 1000000UL // clock frequency
#include <avr/io.h>
#include <util/delay.h>


int main()
{
	uint8_t width = 0; //width modulation variable
	
	DDRB |= (1<<PB1) | (1<< PB2); //pin OC0B as PWM output and PB2 as indication led

	TCCR0A = (0<< COM0A1) | (0<< COM0A0) | 
			 (1<< COM0B1) | (0<< COM0B0) | //Fast PWM. OCnX as PWM pin, no inverted
			(1<< WGM01) | (1<< WGM00); //Fast PWM, Top:0xFF, Update OCR0 at Bottom (0x00), TOV Flag set on MAX (0xFF)
	
	TCCR0B = (0<< WGM02) | //Fast PWM, 0xff, Bottom, max
			 (0<<CS02) | (0<<CS01) | (1<<CS00); //No prescaling
	
	OCR0B = width; //Output duty cycle = (OCR0B+1)/256
	
	while(1)
	{
		OCR0B = width;
		width = width + 5;
		_delay_ms(100);
		if(width >= 255)
		{
			PORTB |= (1<<PB2);
			_delay_ms(3000);
			width = 0;
		}
		else
		{
			PORTB &= ~(1<<PB2);
		}
	}
	
}
