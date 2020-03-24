/*
 * Demo3_Analog_Pot.c
 *  CW turn off pot
 * Created: 22/02/2020 10:35:52
 * Author : Pablo Gonzalez Robles
 * 
 * PARAMS: Fsys: 1MHz, 8-bit Timer, Pval = 1024
 * RESULT:   
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setFlag(int);
int getFlag();

volatile int flag = 0; //flag which control the actions timing inside the infinite loop

#define userLed	PB0

int main(void)
{
	cli();// Disable global interrupts before initialization
 	DDRB |= (1<<userLed);
 	PORTB &= ~(1<<userLed);    
    
	TCCR0B = (1<<CS02)|(0<<CS01)|(1<<CS00); /* Prescaler: 1024 */
    
    TIMSK = (1<<TOIE0); /* Enable Overflow Interrupt */
	
	TIFR = (1<<TOV0); /* Clearing overflow flag */
	
	sei();//initialize global interrupts before beginning loop
	
	while (1)
	{
		if(getFlag() == 1) 
		{
			PORTB ^= (1<<userLed);
			setFlag(0); //reset flag
		}
	}
}


ISR (TIMER0_OVF_vect)
{
	setFlag(1); /* Toggle a pin on timer overflow */
}


void setFlag(int f)
{
	flag = f;
}

int getFlag()
{
	return flag;
}
