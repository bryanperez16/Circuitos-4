/*
* Demo6_TIMER1_ToggleLed.c
*
* Created: 21/02/2020 16:21:15
* Author : Pablo Gonzalez Robles
* Toggle led every xs using Timer 1 in ATtiny85 
*/ 


#define F_CPU 1000000UL //MCU frequency as the default 1MHz (8MHz pre-scaled by 8)
#include <avr/io.h>
#include <avr/interrupt.h>

void setFlag(int);
int getFlag();

volatile int flag = 0; //flag which control the actions timing inside the infinite loop
volatile int t0_initial_val = 12; 

int main(void)
{
        DDRB |= (1<<DDB0);
        PORTB &= ~(1<<PB0);

		TCCR1 = (1<<CS13)|(1<<CS12)|(1<<CS11)|(1<<CS10); //Pre-scaler = 1024

        TIMSK |= (1<<TOIE1); // Overflow Interrupt Enable
        TIFR = (1<<TOV1); /* Clearing overflow flag */
        sei();
        TCNT1 = t0_initial_val;
		
    while (1) 
    {
		if(getFlag() == 1) ////toggle when ISR only 
		{
			PORTB ^= (1<<PB0);
			setFlag(0); //reset flag
		}
    }
}

ISR(TIM1_OVF_vect)
{
	TCNT1 = t0_initial_val;
	setFlag(1);
}

void setFlag(int f)
{
	flag = f;

}

int getFlag()
{
	return flag;
}