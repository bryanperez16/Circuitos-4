/*
 * Demo5_Timers.c
 *
 * Created: 10/06/2020 14:57:02
 * Author : Pablo González Robles
 
* PARAMS: Fsys: 1MHz, 8-bit Timer, Pval = 1024
* RESULT:
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setflag(int);
int getflag();


volatile int flag = 0; //flag which control the actions timing inside the infinite loop

#define led0 PORTB1


int main(void)
{
	cli();// Disable global interrupts before initialization
	DDRB |= (1<<led0);
	PORTB &= ~(1<<led0);
	
	TCCR0B |= (1<<CS02)|(0<<CS01)|(1<<CS00); /* Pre-scaler: 1024 */
	
	TIMSK |= (1<<TOIE0); /* Enable Overflow Interrupt */
	
	TIFR |= (1<<TOV0); /* Clearing overflow flag */
	
	sei();//initialize global interrupts before beginning loop
	
	
	while (1)
	{
		if(getflag() == 1)
		{
			PORTB ^= (1<<led0);
			setflag(0); //reset flag
		}
	}
}


ISR (TIMER0_OVF_vect){
	setflag(1); /* Toggle a pin on timer overflow */
}



void setflag(int f){
	flag = f;
}

int getflag(){
	return flag;
}


