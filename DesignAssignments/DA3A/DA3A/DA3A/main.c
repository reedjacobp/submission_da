/*
 * DA3A.c
 *
 * Created: 10/16/2019 9:43:39 PM
 * Author : jreed
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART_init(void);
unsigned char USART_receive(void);
void USART_send(unsigned char data);
void USART_send_rand(int n);
void USART_putstring(char* StringPtr);
float pi = 3.14;

char String[] = "DA3A";
char newline[] = "\n";
char buffer[5];
char pi_buffer[4];
uint8_t OVF_COUNT = 0;
uint8_t OVF_LIMIT = 250;

int main(void)
{
	USART_init();
	
	TCCR0A = 0x00; //normal operation
	TCCR0B |= (1 << CS02); //set prescalar to 256
	TCNT0 = 16; //TOP = 256-250 = 16
	TIMSK0 |= (1 << TOIE0);
	sei();
	
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

// C program for implementation of ftoa()
#include<stdio.h>
#include<math.h>

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
	int i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.';  // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

ISR (TIMER0_OVF_vect)
{
	OVF_COUNT++;
	if (OVF_COUNT == OVF_LIMIT)
	{
		USART_putstring(String);
		USART_putstring(newline);
		itoa(rand(), buffer, 10);
		USART_putstring(buffer);
		USART_putstring(newline);
		ftoa(pi, pi_buffer, 2);
		USART_putstring(pi_buffer);
		USART_putstring(newline);
		USART_putstring(newline);
		OVF_COUNT = 0;
	}
	TCNT0 = 16;
}