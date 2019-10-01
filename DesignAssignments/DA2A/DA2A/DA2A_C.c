
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PB3);
	DDRB |= (1 << PB2);
	DDRC &= ~(1 << PC3);
	
	while(1)
	{
		PORTB |= (1 << PB3);
		_delay_ms(250);
		PORTB &= ~(1 << PB3);
		_delay_ms(375);
		if (PINC & (1 << 3))
		{
			PORTB |= (1 << PB3);
			_delay_ms(1333);
		}
	}
	return 1;
}

