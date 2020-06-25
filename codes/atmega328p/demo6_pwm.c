/*
 * Demo6_pwm.c
 *
 * Created: 17/06/2020 9:33:33
 * Author : Pablo González Robles
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1 << PORTD6);// PORTD6 set as output (OC0A - Timer/Counter0 Output Compare Match A Output)
	DDRD |= (1 << PORTD5); // PORTD5 set as output  OC0B
	
	DDRB |= (1 << PORTB2); //OC1B
	DDRB |= (1 << PORTB1); 
	
	OCR0A = 127; // set at 50% duty cycle
	OCR0B = 63; // set at 25% duty cycle


	TCCR0A |= (1 << COM0A1) | (0 << COM0A0) // configured as no-inverting mode
			| (1 << COM0B1) | (0 << COM0B0)
			| (1 << WGM01) | (1 << WGM00); // configured as fast PWM Mode
	
	TCCR0B |=(0 << CS02) |(1 << CS01) |(0 << CS00); // set pre-scaler to 8 and starts PWM
	
	/*
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0) // configured as no-inverting mode
			| (1 << WGM11)  | (0 << WGM10); // configured as phase correct
	TCCR1B |= (0 << CS12)| (1 << CS11)| (0 << CS10); // set pre-scaler to 8 a
	
	OCR1B=101;//set at 20% pwm duty cycle
*/
		//Fast pwm Pval=256 Fsys = 1Mhz 50% dutty cycle Ppwm = 1Hz
		TCCR1A |= (1 << COM1A1) | (0 << COM1A0)
		| (1 << WGM11)  | (0 << WGM10);
		TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12)| (0 << CS11)| (0 << CS10);
		

		ICR1 = 3905; //Top value  Fsys /(Pval * 1Hz) - 1
		OCR1A = 1952; // 50%

	while (1);
	{
		
	}
}

