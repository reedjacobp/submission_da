/*
 * DA2A.c
 *
 * Created: 9/27/2019 1:37:41 AM
 * Author : jreed
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	DDRC = 0x00;
	PORTB = 0xFF;
// 	DDRB |= (1 << PORTB3);
// 	DDRB |= (1 << PORTB2);
// 	DDRC &= ~(1 << PORTC3);
	
	while(1)
	{
		PORTB |= (1 << PORTB3);
		_delay_ms(375);
		PORTB &= ~(1 << PORTB3);
		_delay_ms(250);
		if ( !(PINC & (1 << 3)))
		{
			PORTB |= (1 << PORTB3);
			PORTB &= ~(1 << PORTB2);
			_delay_ms(1333);
			PORTB |= (1 << PORTB2);
		}
	}
	return 0;
}

