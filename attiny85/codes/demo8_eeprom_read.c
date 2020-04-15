/*
 * Demo8_eepromRead.c
 *
 *
 * Created: 3/03/2020 9:32:20
 * Author : Pablo Gonzalez Robles
 * ATtiny85 eeprom size 512 bytes (0~1FF)
 */

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>//eeprom management library inside avr-libc

#define startLed	   PB0 //green led
#define blinkingLed	   PB1 //green led


uint8_t Read_byte(int idx)
{
	uint8_t stored_byte ;
	stored_byte = eeprom_read_byte((uint8_t*) idx) ;
	return stored_byte;
}

uint16_t Read_word(int idx)
{
	uint16_t stored_word;
	stored_word = eeprom_read_word((uint16_t*) idx);
	return stored_word;

}

uint8_t* Read_block(int starting_idx)
{
	uint8_t stored_string [10];
	eeprom_read_block (( void *) stored_string , (const void*)starting_idx,10) ;
	return stored_string;
}

float Read_float(int idx)
{
	float f;
	f = eeprom_read_float((float*) idx) ;
	return f;
}

int main(void)
{
	cli();
	DDRB |= (1<<startLed) | (1<<blinkingLed);
	PORTB |= (1 << startLed);
	_delay_ms(1000);
	PORTB ^= (1 << startLed);
	uint8_t stored_byte = Read_byte(0x12);
	if(stored_byte == 0xFF)
	{
		PORTB |= (1 << blinkingLed);
		_delay_ms(2000);
	}
    while (1) 
    {
    }
}

