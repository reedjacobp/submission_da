/*
 * DA4B.c
 *
 * Created: 11/10/2019 6:25:34 PM
 * Author : jreed
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void ADC_INIT(void);

int main(void)
{
	DDRD = 0xF0;        // Set PD4 - PD7 as outputs for stepper motor
	ADC_INIT();	      	// Initialize ADC
	TCCR1B = 0x0D;      // Set CTC mode and 1024 prescaler
	
	while(1)
	{
		while((ADCSRA&(1<<ADIF))==0); // wait for ADC conversion
		OCR1A = ADC;	// set OCR1A to the determined speed
		
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x90;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x80;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0xC0;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x40;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x60;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x20;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x30;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
		while((TIFR1 & (1 << OCF1A)) == 0);
		PORTD = 0x10;
		TCNT1 = 0;
		TIFR1 |= (1<<OCF1A);
	}
}

void ADC_INIT(void)
{
	ADMUX = (0<<REFS1)|	//	Reference Selection Bits
	(1<<REFS0)|	//	AVcc-external cap at AREF
	(0<<ADLAR)|	//	ADC	Left Adjust	Result
	(0<<MUX3) |
	(0<<MUX2) |	//	AnalogChannel Selection	Bits
	(0<<MUX1) |	//	ADC0 (PC0)
	(0<<MUX0);

	ADCSRA = (1<<ADEN)|	//	ADC	Enable
	(1<<ADSC) |	//	ADC	Start Conversion
	(1<<ADATE)|	//	ADC	Auto Trigger Enable
	(0<<ADIF) |	//	ADC	Interrupt Flag
	(1<<ADIE) |	//	ADC	Interrupt Enable
	(1<<ADPS2)|	//	ADC	PrescalerSelect	Bits
	(1<<ADPS1)|
	(1<<ADPS0);
}