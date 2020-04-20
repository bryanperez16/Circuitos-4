/*
 * FINAL.c
 *
 * Created: 04/19/2020 5:40:12 p. m.
 * Author : Anel Bultron
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define FINE PB3
#define BUZZ PB1
#define Read PB2
#define DANGER PB4


volatile unsigned int analogResult = 0; // variable de ADC
volatile int VelResult; // variable de division 1024/4

uint8_t width = 0; // Ancho de pulso






int main(void)
{
	
	ADMUX =
	(0 << REFS1) |  (0 << REFS0) |   // Sets ref. voltage to VCC
	(0 << ADLAR) |				     // 0: right adjust, 1: left adjust
	(0 << MUX3)  |	(0 << MUX2)  |	(0 << MUX1)  |	(1 << MUX0);  //  ADC1 (PB2)
	
	
	ADCSRA =
	(1 << ADEN)  |     // Enable ADC
	(1 << ADSC)  |     // Start Conversion
	(1 << ADATE)  |     // Enable Auto trigger
	(0 << ADIF)  |     //
	(1 << ADIE)  |     //ADC interrupt enable
	(0 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);  // set prescaler to 8
	
	ADCSRB =
	(0<<ADTS2)|		//Free running mode bit 2
	(0<<ADTS1)|		//Free running mode bit 1
	(0<<ADTS0);		//Free running mode bit 0
	sei();
	
	
	TCCR0A = (0<< COM0A1) | (0<< COM0A0) |
	(1<< COM0B1) | (0<< COM0B0) | //Fast PWM. OCnX as PWM pin, no inverted
	(1<< WGM01) | (1<< WGM00); //Fast PWM, Top:0xFF, Update OCR0 at Bottom (0x00), TOV Flag set on MAX (0xFF)
	
	TCCR0B = (0<< WGM02) | //Fast PWM, 0xff, Bottom, max
	(0<<CS02) | (0<<CS01) | (1<<CS00); //No prescaling
	
	//Output duty cycle = (OCR0B+1)/256}
	uint8_t ancho = 0;
	OCR0B = ancho;
	
	
	while(1){
		
		
		VelResult = analogResult/4;
		OCR0B = VelResult;
		
		DDRB|= (1<<BUZZ)|(1<<DANGER)|(1<<FINE); // pb0 , pb1 , pb3 son salidas
		DDRB &= ~(1<<Read); // lectura de adc
		
		PORTB |= (1<<Read);
		
		
		if(analogResult<=350) //value 0-100 (0-0.94V)
		{
			_delay_ms(250);
			PORTB|=(1<<FINE)|(1<<BUZZ);
			PORTB&=~(1<<DANGER);
			
		}
		else if(analogResult>=800) //value 900-1023 (4.22 - 4.8 V)
		{
			_delay_ms(250);
			PORTB|=((1<<DANGER)|(1<<BUZZ));
			PORTB&=~(1<<FINE);
		}
		else
		{
			_delay_ms(250);
			PORTB|=((1<<FINE)|(1<<DANGER));
			PORTB|=(1<<BUZZ);
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


void reset(void)
{
	
}