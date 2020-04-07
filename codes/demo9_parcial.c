/*
 * exam.c
 *
 * Created: 26/03/2020 13:10:08
 * Author : Pablo Gonzalez Robles
 * Examen: Juego de pulsaciones. 
	Juego empieza después de un par de segundos.
	Mientras empieza, el jugador puede ajustar el nivel (1,2,3) de 0 a 1023
	Al terminarse el tiempo de setting, el jugador es indicado con el GREEN LED de qué nivel está jugando
	El jugador debe pulsar la cantidad de veces necesarias del nivel (5,10,20) y dependiendo del current value, el pwm led incrementa su intensidad
	Al llegar al número de pulsaciones necesarias, avisar al jugador de que el nivel ha concluido
	
	Debound time = 20ms
	 
 */ 

#define F_CPU 1000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define blinkingLed PB0 //orange led
#define pwmLed PB1		//red led
#define pot PB2			//potentiometer
#define pushBtn PB3		//switch button
#define startLed PB4	//green led



void setFlag(int);
int getFlag();

volatile unsigned int analogResult = 0;
volatile unsigned int level = 0;

volatile int flag = 0; 
volatile int TCNT1_initial_val = 0;

volatile uint8_t counter = 0;
uint8_t previousReading  = 1;
uint8_t buttonWasPressed = 1;

uint8_t width = 0; //width modulation variable
uint8_t push_lv1 = 5;
uint8_t push_lv2 = 10;
uint8_t push_lv3 = 20;

void init_adc(void)
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
	(1 << ADIE)  |     //ADC interrupt flag
	(0 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);  // set prescaler to 8
	
	ADCSRB =
	(0<<ADTS2)|		//Free running mode bit 2
	(0<<ADTS1)|		//Free running mode bit 1
	(0<<ADTS0);		//Free running mode bit 0
}

void howmany(void)
{
	PORTB &=~(1<<startLed);
	if(analogResult<=300) //value 0-100 (0-0.94V)
	{
		level = 1;
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		
	}
	else if(analogResult<=700) //value 900-1023 (4.22 - 4.8 V)
	{
		level = 2;
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
	}
	else
	{
		level = 3;
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
		PORTB^=(1<<startLed);
		_delay_ms(500);
	}
}

void init_pwm(void)
{
	TCCR0A = (0<< COM0A1) | (0<< COM0A0) |
	(1<< COM0B1) | (0<< COM0B0) | //Fast PWM. OCnX as PWM pin, no inverted
	(1<< WGM01) | (1<< WGM00); //Fast PWM, Top:0xFF, Update OCR0 at Bottom (0x00), TOV Flag set on MAX (0xFF)
		
	TCCR0B = (0<< WGM02) | //Fast PWM, 0xff, Bottom, max
	(0<<CS02) | (0<<CS01) | (1<<CS00); //No prescaling
		
	OCR0B = width; //Output duty cycle = (OCR0B+1)/256
}

void init_game(void)
{
	cli();
	DDRB |= (1<<blinkingLed) | (1<<startLed) | (1<<pwmLed) | (0<<pot) | (0<<pushBtn) ;   //Set the Data Direction Register to output
	_delay_ms(3500);
	PORTB|=(1<<blinkingLed) | (1<<pot);//Enable the pull-up resistor for the Pot
	init_adc();
	sei();
	_delay_ms(1000);
	PORTB ^= (1 << blinkingLed);
	_delay_ms(1000);
	PORTB ^= (1 << blinkingLed);
	_delay_ms(1000);
	PORTB ^= (1 << blinkingLed);
	_delay_ms(1000);
	PORTB ^= (1 << blinkingLed);
	_delay_ms(3000);
	PORTB ^= (1 << blinkingLed);
	_delay_ms(250);
	howmany();
	PORTB|= (1<<pushBtn); //Enable the pull-up resistor for the switch btn
	init_pwm();
	
}

void init_t1(void)
{
	TCNT1_initial_val = 251; //256 - ((1e6*retardo)/4096) //251 for 20ms, 207 for 200ms, 196 for 250ms
	TCCR1 = (1<<CS13)|(1<<CS12)|(0<<CS11)|(1<<CS10); //Pre-scaler = 4096
	TIMSK |= (1<<TOIE1); // Overflow Interrupt Enable
	TIFR = (1<<TOV1); /* Clearing overflow flag */
	TCNT1 = TCNT1_initial_val;
}

ISR(ADC_vect) //adc interrupt function
{
	unsigned int binary_weighted_voltage_low = ADCL; //Read 8 low bits first
	unsigned int binary_weighted_voltage_high = ((unsigned int)(ADCH << 8)); //Read 2 high bits
	analogResult = binary_weighted_voltage_low | binary_weighted_voltage_high;
}

ISR(TIM1_OVF_vect)
{
	TCNT1 = TCNT1_initial_val;
	//PORTB ^= (1 << pwmLed); //Checking if timing was OK207 for 200ms
	if ((PINB & (1 << pushBtn)) != previousReading)
	{
		if (!buttonWasPressed)
		{
			if (counter < 255)
			{
				counter++;
			}
			else
			{
				counter = 0;
			}
			buttonWasPressed = 1;
		}
		else
		{
			buttonWasPressed = 0;
		}
		previousReading = (PINB & (1 << pushBtn)); 
	}
}

void reset_game(void)
{
	
}


int main(void)
{
    init_game();
	init_t1();
    while (1) 
    {
		if(getFlag() == 0)
		{
			if (level == 1)
			{
				if (counter == push_lv1)
				{

					PORTB |= (1 << blinkingLed);
					counter = 0;
					setFlag(1);	//when done
				}

				//OCR0B = (uint8_t)(51*counter);
				OCR0B = (uint8_t) ((float) counter / (float) push_lv1 * 255.0);
			}
			else if (level == 2)
			{
				if (counter == push_lv2)
				{
					PORTB |= (1 << blinkingLed);
					counter = 0;
					setFlag(1);	
				}
				//OCR0B = (uint8_t)(25*counter);
				OCR0B = (uint8_t) ((float) counter / (float) push_lv2 * 255.0);
			}
			else if (level == 3)
			{
				if (counter == push_lv3)
				{
					PORTB |= (1 << blinkingLed);
					counter = 0;
					setFlag(1);
				}
				//OCR0B = (uint8_t)(12*counter);
				OCR0B = (uint8_t) ((float) counter / (float) push_lv3 * 255.0);
			}
		}//end if flag
		else
		{
			//do when game is over
			PORTB |= (1 << startLed);
		}
    } // end while
} //end main

void setFlag(int f)
{
	flag = f;
}

int getFlag()
{
	return flag;
}

