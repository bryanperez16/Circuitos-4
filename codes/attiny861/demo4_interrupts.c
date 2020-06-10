/*
 * Demo4_Interrupts.c
 *
 * Created: 09/06/2020 21:45:06
 * Author : Pablo Gonzalez Robles
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define int_btn PORTB6
#define led_blue PORTB0
#define led_green PORTA3
#define led_yellow PORTA5		
#define pot PORTA1		
volatile unsigned int analogResult = 0;

int main(void)
{
	DDRA |= (1<<led_green)|(1<<led_yellow);   //Set the Data Direction Register to output (PB3 = yellow led , PB6 = green led)
	DDRA &= ~(1<<pot);	//Set the Data Direction Register for the POT to input
	
	DDRB |= (1<<led_blue); //set as output
	DDRB &= ~(1<<int_btn); //set as input and enable pull-up resistor on btn

	ADMUX =
	(0 << REFS1) |  (0 << REFS0) |   // Sets ref. voltage to VCC
	(0 << ADLAR) |				     // 0: right adjust, 1: left adjust
	(0 << MUX4) | (0 << MUX3) | (0 << MUX2)  |	(0 << MUX1)  |	(1 << MUX0);   // ADC1 working
	
	
	ADCSRA =
	(1 << ADEN)  |     // Enable ADC
	(1 << ADSC)  |     // Start Conversion
	(1 << ADATE)  |     // Enable Auto trigger
	(0 << ADIF)  |     //
	(1 << ADIE)  |     //ADC interrupt flag
	(1 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);  // set pre-scaler to 128
	
	ADCSRB =
	(0<<ADTS2)|		//Free running mode bit 2
	(0<<ADTS1)|		//Free running mode bit 1
	(0<<ADTS0);		//Free running mode bit 0
	
	GIMSK = (1<<INT0);
	
	MCUCR = (0<<ISC01) | (1<<ISC00);

	sei();
	
	while (1)
	{
		if(analogResult<=200) 
		{
			PORTA|=(1<<led_yellow);
			PORTA&=~(1<<led_green);
			_delay_ms(100);
		}
		else if(analogResult>=800)
		{
			PORTA&=~(1<<led_yellow);
			PORTA|=(1<<led_green);
			_delay_ms(100);
		}
		else
		{
			PORTA &=~((1<<led_green)|(1<<led_yellow));
		}
	}
}


ISR(ADC_vect) //interrupt function
{
	//The ADC generates a 10-bit result
	//which can be found in the ADC Result Registers, ADCH and ADCL
	unsigned int binary_weighted_voltage_low = ADCL; //Read 8 low bits first
	unsigned int binary_weighted_voltage_high = ((unsigned int)(ADCH << 8)); //Read 2 high bits
	analogResult = binary_weighted_voltage_low | binary_weighted_voltage_high;
}

ISR(INT0_vect)
{
	if((PINB & (1<<int_btn))== 0){
		PORTB |= (1<<led_blue); //when btn is pressed, int get in 
	}
	else{
		PORTB &= ~(1<<led_blue); //when btn is released, we got a logical change again, int get in again and reset led to off
	}
}