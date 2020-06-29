/*
 * Midterm_q2_20.c
 *
 * Created: 23/06/2020 16:25:03
 * Author : Pablo González Robles
 
 Asignación sumativa:
 Control de servo motor usando attiny861 / atmega328p
 Servo: 0 a 180 grados / 50Hz / 1ms a 2ms
 Considerar una Fsys de 1Mhz
 Usar el Fast pwm mode (Timer1 es el recomendado)
 Usar pot en el canal ADC2 para hacerlo rotar gradualmente entre los límites
 
 */ 

#define F_CPU 1000000UL		
#include <avr/io.h>	
#include <avr/interrupt.h>	
#include <util/delay.h>	

#define servopwm PORTB1
#define pot PORTC2
volatile unsigned int analogResult = 0;	


void init_adc(void)
{
	/*
	ADC Pre-scaler needs to be set so that the ADC input frequency is between 50 - 200kHz.
	Clock   Available pre-scaler values
	1 MHz   8 (125kHz), 16 (62.5kHz)
	*/
	
	DDRC &= ~(1<<pot);	//Set the Data Direction Register for the pot 
	
	ADMUX |=
	(0 << REFS1) |  (0 << REFS0) |   // Sets ref. voltage to VCC
	(0 << ADLAR) |				   // 0: right adjust, 1: left adjust
	(0 << MUX3) | (0 << MUX2) | (1 << MUX1)  |	(0 << MUX0);   //  MUX bits ADC2; 0010, PC2
	
	ADCSRA |=
	(1 << ADEN)  |     // Enable ADC
	(1 << ADSC)  |     // Start Conversion
	(1 << ADATE)  |     // Enable Auto trigger
	(0 << ADIF)  |     // ADC interrupt flag
	(1 << ADIE)  |     //ADC Interrupt Enable
	(0 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);  // set pre-scaler to 8, thus, adc fq =125kHz OK
	
	
	ADCSRB |=
	(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);  //Free running mode
}

void init_servo(void)
{
	DDRB |= (1<<servopwm);	//set pwm pin (OC1A)
	TCNT1 = 0;		// timer 1 register to 0
	ICR1 = 2499;	// counting till icr1 value


	TCCR1A |= 
	(1<<COM1A1) |(0<<COM1A0) //Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
	|(1<<WGM11) |(0<<WGM10); //waveform generation mode #14 (Fast PWM, TOP = ICR1, UPDATE OCR1A at BOTTOM, TOV1 FLAG set on TOP )
	
	TCCR1B |= 
	(1<<WGM13) | (1<<WGM12) //waveform generation mode #14 complementary bits
	|(0<<CS12) |(1<<CS11)|(0<<CS10); //clock pre-scaler for pwm fq
}

int main(void)
{
	cli();
	init_servo();
	init_adc();
	sei();
	
	while(1)
	{

		
		/*
		OCR1A = 125;	// Set 1ms / 5% of dc 
		_delay_ms(1000);
		OCR1A = 187;	// Set 1.5ms / 7.5% of dc 
		_delay_ms(1000);
		OCR1A = 250;	// Set 2ms / 10% of dc 
		_delay_ms(1000);
		*/
		
		OCR1A =(uint8_t) (0.1222*analogResult + 125); // y = 125/1023*x + 125
		_delay_ms(500);
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

