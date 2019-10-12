/*
 * DA2C_Task2.c
 *
 * Created: 10/10/2019 10:33:17 PM
 * Author : jreed
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t OVF_COUNT = 0;
uint8_t OVF_LIMIT = 16;

int main(void)
{
	//int count = 0;
	DDRB = 0xFF; //all registers in DDRB are outputs
	DDRC = 0x00; //all registers in DDRC are inputs
	PORTB = 0xFF; //turn on all LEDs
	TCCR0A = 0x00; //normal operation
	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescalar to 1024
	TCNT0 = 12;
	TIMSK0 |= (1 << TOIE0);
	sei();
	
    while (1) 
    {
		
    }
}

ISR (TIMER0_OVF_vect)
{
	OVF_COUNT++;
	if (OVF_COUNT == OVF_LIMIT)
	{
		PORTB ^= (1 << 3);
		PORTB |= (1 << 2);
		if(OVF_LIMIT == 16)
		{
			OVF_LIMIT = 24;
		}
		if(!(PINC & (1 << 3)))
		{
			OVF_LIMIT = 85;
			PORTB |= (1 << 3);
			PORTB &= ~(1 << 2);
		}
		else
		{
			OVF_LIMIT = 16;
		}
		OVF_COUNT = 0;
	}
	TCNT0 = 12;
}

