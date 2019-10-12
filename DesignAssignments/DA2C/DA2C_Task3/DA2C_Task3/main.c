/*
 * DA2C_Task3.c
 *
 * Created: 10/11/2019 12:39:36 AM
 * Author : jreed
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t OVF_COUNT = 0;
uint8_t OVF_LIMIT = 16;

int main(void)
{
	DDRB = 0xFF; //all registers in DDRB are outputs
	DDRC = 0x00; //all registers in DDRC are inputs
	PORTB = 0xFF; //turn on all LEDs
	OCR0A = 244; //normal operation
	TCNT0 = 0;
	TCCR0A |= (1 << WGM01) | (1 << COM1A0);
	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescalar to 1024
	TIMSK0 |= (1 << OCIE0A);
	sei();
	
	while (1)
	{
		
	}
}

ISR (TIMER0_COMPA_vect)
{
	OVF_COUNT++;
	if (OVF_COUNT == OVF_LIMIT)
	{
		PORTB ^= (1 << 3);
		PORTB |= (1 << 2);
		if(OVF_LIMIT == 16)
		{
			OVF_LIMIT = 24;
			if(!(PINC & (1 << 3)))
			{
				OVF_LIMIT = 85;
				PORTB |= (1 << 3);
				PORTB &= ~(1 << 2);
			}
		}

		else
		{
			OVF_LIMIT = 16;
			if(!(PINC & (1 << 3)))
			{
				OVF_LIMIT = 85;
				PORTB |= (1 << 3);
				PORTB &= ~(1 << 2);
			}
		}
		OVF_COUNT = 0;
	}
	TCNT0 = 0;
}

