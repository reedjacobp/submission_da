/*
 * DA3B.c
 *
 * Created: 10/20/2019 8:48:28 PM
 * Author : jreed
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART_init(void); //function to initialize USART
unsigned char USART_receive(void); //function to receive through USART
void USART_send(unsigned char data); //function to send through USART
void USART_putstring(char* StringPtr); //function to scan through the string

float temp;
uint8_t OVF_COUNT = 0; //initialize the overflow count for interrupt
uint8_t OVF_LIMIT = 250; //set the limit the count can reach to set 1 sec delay

int main(void)
{
	USART_init(); //initialize USART
	
 	ADCSRA = 0x84;
 	ADMUX = 0x44;
	
	TCCR0A = 0x00; //normal operation
	TCCR0B |= (1 << CS02); //set prescalar to 256
	TCNT0 = 16; //TOP = 256-250 = 16
	TIMSK0 |= (1 << TOIE0);
	sei(); //enable interrupt
	
    while (1) 
    {		
    }
}

void USART_init(void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

unsigned char USART_receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void USART_send(unsigned char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void USART_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00)
	{
		USART_send(*StringPtr);
		StringPtr++;
	}
}

ISR (TIMER0_OVF_vect)
{
	OVF_COUNT++; //increment the overflow counter
	if (OVF_COUNT == OVF_LIMIT) //check to see if the limit was reached
	{
		ADCSRA |= (1 << ADSC);
		while((ADCSRA & (1 << ADIF)) == 0)
		{
			ADCSRA |= (1 << ADIF);
			int temp = ADCL;
			temp = temp | (ADCH<<8);
			temp = (temp/1024.0) * 5000/10;
			temp = (temp*2)+32; //equation to convert celsius to farenheit. can't use used 2 instead of 9/5
			//USART_send((a/100)+'0');
			temp = temp % 100;
			USART_send((temp/10)+'0');
			temp = temp % 10;
			USART_send((temp)+'0');
			//USART_send('\r');
			USART_send('\n');
		}
		OVF_COUNT = 0; //reset overflow counter
	}
	TCNT0 = 16; //reset TOP
}