/*
 * DA2C_Task1.c
 *
 * Created: 10/9/2019 10:56:08 PM
 * Author : jreed
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>

int main(void)
{
	DDRB = 0xFF; //all registers in DDRB are outputs
	DDRC = 0x00; //all registers in DDRC are inputs
	PORTB = 0xFF; //turn on all LEDs
	TCCR0A = 0x00; //normal operation
	TCNT0 = 0x00; //start the timer
	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescaler to 1024
	int count = 0; //use this to count overflow
	
	//The fout for this is about 61Hz
	
	while(1)
	{
		count = 0;
		TCNT0 = 0x00; //start the timer
		while(count < 23) //60% off
		{
			if(TCNT0 == 0xFF) //check to see if TOP(255) has been reached
			{
				count++; //upon overflow, count it, then reset timer
				TCNT0 = 0x00; //reset timer
			}
			
			else if(!(PINC & (1 << 3))) //check if SW3 is pushed
			{
				PORTB |= (1 << 3); //turn off LED @ PB3
				PORTB &= ~(1 << 2); //turn on LED @ PB2
				TCNT0 = 0x00; //reset timer if switch is pushed
				count = 0;
				while(count < 82) //1.333 seconds
				{
					if(TCNT0 == 0xFF)
					{
						count++;
						TCNT0 = 0x00;
					}
				}
				PORTB |= (1 << 2); //turn off LED @ PB2
			}
		}
		PORTB ^= (1 << 3); //once overflow has been counted 23 times, turn off LED by XOR
		count = 0; //reset the count
		TCNT0 = 0x00; //since timer is constantly incrementing, I must reset right before a loop uses it
		while(count < 15) //40% on
		{
			if(TCNT0 == 0xFF) //check to see if TOP(255) has been reached
			{
				count++; //upon overflow, count it, then reset timer
				TCNT0 = 0x00; //reset timer
			}
			else if(!(PINC & (1 << 3))) //check if SW3 is pushed
			{
				PORTB |= (1 << 3);
				PORTB &= ~(1 << 2);
				count = 0;
				TCNT0 = 0x00; //reset timer if switch is pushed
				while(count < 82) //1.333 seconds
				{
					if(TCNT0 == 0xFF)
					{
						count++;
						TCNT0 = 0x00;
					}
				}
				PORTB |= (1 << 2); 
			}			
		}
		PORTB ^= (1 << 3); //once overflow has been counted 12 times, turn on LED by XOR
	}
	return 0;
}

