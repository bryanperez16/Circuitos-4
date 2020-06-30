#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int POT = 0;
unsigned int BAJO;
unsigned int ALTO;



int main(void)
{
	DDRB |= (1<<PB2);
	DDRB |= (1<<PB1);
	DDRB |= (1<<PB0);
	DDRB &= ~(1<<PB3);
	
	ADMUX =
	(0<<REFS1)|(0<<REFS0)|  
	(0<<ADLAR)|	
	(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);  
	
	
	ADCSRA =
	(1<<ADEN)|   
	(0<<ADSC)|  
	(0<<ADATE)|  
	(0<<ADIF)|     
	(0<<ADIE)|    
	(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); 
	
	ADCSRB =
	(0<<ADTS2)|		
	(0<<ADTS1)|		
	(0<<ADTS0);		
	
	while (1)
	{
		ADCSRA |= (1<<ADSC);         
		while (ADCSRA & (1<<ADSC) ); 
		
		BAJO = ADCL;
		ALTO = ((unsigned int)(ADCH << 8));
		POT = BAJO | ALTO;
		
		if(POT<=341)
		{
			PORTB&=~(1<<PB0);
			PORTB&=~(1<<PB1);
			PORTB|=(1<<PB2);
			_delay_ms(100);
		}
		else if(POT>341 && POT<=682)
		{
			PORTB&=~(1<<PB0);
			PORTB|=(1<<PB1);
			PORTB&=~(1<<PB2);
			_delay_ms(100);
		}
		else
		{
			PORTB|=(1<<PB0);
			PORTB&=~(1<<PB1);
			PORTB&=~(1<<PB2);
			_delay_ms(100);
		}
	}
}
