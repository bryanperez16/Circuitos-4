/*
 * Demo4_Interrupts.c
 *
 * Created: 18/06/2020 15:23:09
 * Author : Pablo González Robles
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define int_btn0 PORTD2
#define int_btn1 PORTD3
#define led0 PORTD0
#define led1 PORTD1

int main(void)
{
	
	DDRD |= (1<<led0) | (1<<led1); //set as output
	DDRD &= ~(1<<int_btn0)& ~(1<<int_btn1); //set as input and enable pull-up resistor on btn

	
	EICRA |= (0<<ISC11) | (1<<ISC10) | (0<<ISC01) | (1<<ISC00);
	EIMSK |= (1<<INT1) | (1<<INT0);
	sei();
		
    while (1) 
    {
    }
}


ISR(INT0_vect)
{
	if((PIND & (1<<int_btn0))== 0){
		PORTD |= (1<<led0); //when btn is pressed, int get in
	}
	else{
		PORTD &= ~(1<<led0); //when btn is released, we got a logical change again, int get in again and reset led to off
	}
}

ISR(INT1_vect)
{
	if((PIND & (1<<int_btn1))== 0){
		PORTD |= (1<<led1); //when btn is pressed, int get in
	}
	else{
		PORTD &= ~(1<<led1); //when btn is released, we got a logical change again, int get in again and reset led to off
	}
}