/*
 * Demo7_eepromWrite.c
 *
 * Created: 23/06/2020 10:15:54
 * Author : Pablo Gonzalez Robles
 */ 

#define F_CPU 1000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>//eeprom management library inside avr-libc



#define blinkingLed	   PB0 //orange led
#define defined_address 0x12c //random register . Register 300
uint8_t EEMEM eeprom_var1; //memory char or byte variable
uint8_t EEMEM own_string[10] ;


void alert()
{
	PORTB ^= (1 << blinkingLed);
	_delay_ms(2000);
}

void Write_byte_simple(int idx, int value)
{
	uint8_t byte2write ;
	byte2write = value ;
	eeprom_update_byte (( uint8_t *) idx , byte2write );
	alert();
}

void Write_word_simple (int idx, int value)
{
	uint16_t word2write ;
	word2write = value ; //0xabcd saved as 1st register = cd, 2nd register = ab 
	eeprom_update_word (( uint16_t *) idx , word2write ) ;
	alert();
}


void Write_float_simple(int idx, float value)
{
	eeprom_write_float(( float*) idx,value);
}

void Write_EEMEM()
{
	char tmp[] = "p#B1o,!";
	eeprom_write_block(tmp, own_string, sizeof(tmp));
	eeprom_write_byte(&eeprom_var1,0xbb); //1 byte en la siguiente línea disponible
	alert();
}


void Write_byte_properly(int idx, int value)
{
	uint8_t byte2write ;
	byte2write = value ;
	eeprom_update_byte (( uint8_t *) idx , byte2write);
	alert();
}


int main(void)
{
	cli();
	DDRB |= (1<<blinkingLed);   
	Write_EEMEM(); //p#B1o, + bb hex value stored in available space
	Write_float_simple(20,3.141592); //float value to hex value stored at address 20
	Write_word_simple(30, 0x6543); // over 1 byte value using little-endian
	Write_byte_simple(40,0x12); //12 hex value stored at address 40
	Write_byte_properly(41,0x24); // 24 hex value stored at address 41


    while (1) 
    {
    }
}





