/*
 * pruebaBotonServo.cpp
 *
 * Created: 04/18/2020 5:16:25 p. m.
 * Author : rober
 */ 


#define F_CPU 8000000UL	 //frecuencia del CPU
//librerias necesarias	
#include <avr/io.h>		
#include <stdio.h>		
#include <util/delay.h>		



int main(void)
{
	uint8_t ESTADO = true;  //variable de estado para el pulsador de la garra
	//Entradas
	DDRA &=~ (1<<PA0);
	DDRA &=~ (1<<PA1);
	DDRA &=~ (1<<PA2);
	DDRA &=~ (1<<PA3);
	DDRA &=~ (1<<PA4);
	
	
	//Salidas
	DDRD |= (1<<PD7);
	DDRD |= (1<<PD5);
	DDRB |= (1<<PB3);
	DDRD |= (1<<PD4);
		
	TCNT1 = 0;		//timer1 count en 0
	ICR1 = 2499;	//El top value del timer1 en el registro ICR1

	//establecemos el fast PWM para el pin del servo 1
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	//fast PWM para el pin del servo 2
	TCCR2 |= (0<<FOC2)|(1<<WGM20)|(1<<WGM21)|(0<<COM20)|(1<<COM21)|(1<<CS20)|(0<<CS21)|(1<<CS22);
	uint8_t i = 150;  //posicion por defecto del servo 1
	uint8_t j = 65;   //posicion por defecto del servo 2
	while(1)
	{
		
		if (PINA & (1<<PA4))		//pulsador de la garra presionado
		{
			if (ESTADO == true)		//si el estado es true
			{
				PORTB |= (1<<PB3);		//pin que sa al driver que hace girar el motor en una direcion
				_delay_ms(500);
				PORTB &=~ (1<<PB3);		//el otro pin que hace que el motor gire en sentido contrario apagado
				while (PINA & (1<<PA4))
				{
					//esperar a que se deje de presionar el pulsador
					
				}
				ESTADO = !ESTADO;		//cambiar el estado
			}
			//lo mismo pero en estado diferente de true
			else{
				PORTD |= (1<<PD4);
				_delay_ms(500);
				PORTD &=~ (1<<PD4);
				while (PINA & (1<<PA4))
				{
					
				}
				ESTADO = !ESTADO;
			}

		}
		OCR1A = i;		//valor de i asignado al pin del servo 1
		OCR2 = j;		//valor de j asignado al pin del servo 2
		
		//mientras el pulsador determinado esta presionado dismunuir el valor de la posicion
		while(PINA & (1<<PA0)){
			OCR1A = i;
			_delay_ms(50);
			i = i - 1;
		}
		//mientras el pulsador determinado este presionado, el valor de la posicion aumentara
		while(PINA & (1<<PA1)){
			OCR1A = i;
			_delay_ms(50);
			i = i + 1;
		}
		//igual pero para el otro servo
		while(PINA & (1<<PA2)){
			OCR2 = j;
			_delay_ms(50);
			j = j - 1;
		}
		while(PINA & (1<<PA3)){
			OCR2 = j;
			_delay_ms(50);
			j = j + 1;
		}
			
}
}
