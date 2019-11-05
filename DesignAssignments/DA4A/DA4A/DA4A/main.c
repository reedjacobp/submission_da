/*
 * DA4A.c
 *
 * Created: 10/31/2019 4:26:26 PM
 * Author : jreed
 */ 

#define F_CPU 16000000UL	// 16MHz
#include <avr/io.h>		    //  
#include <avr/interrupt.h>  // 
#include <util/delay.h>		// 

void init_adc(void);
int control;	//  VARIABLE FOR ADC VALUE (NOT NEEDED)
int toggle = 0; // USED TO DETERMINE IF BUTTON SHOULD BE ON OR OFF

int main()
{
	DDRB |= (1 << DDRB1) | (1 << DDRB2); //make PB1 and PB2 as output
	DDRD |= (1 << DDRD6); //make PD6 as output for PWM
	DDRC &= ~(1 << DDRC0); //PC0 is an input
	DDRC &= ~(1 << DDRC1); //PC1 is an input
	PORTC |= (1 << PORTC1);	// ENABLE PULL-UP RESISTOR
	TCCR0A=0x83; //set up for fast PWM and clear OC0A on compare match
	TCCR0B=0x05; //prescalar of 1024
	PCICR = 0x02; //enable PCIE1 for PCMSK1 to work
	PCMSK1 = 0x02; //enable pin changes on PC1 (PCINT9)

	sei(); //enable interrupts
	ADMUX = (1<<REFS0); //reference voltage at AREF
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //set up for ADC conversion
	
	while (1)
	{
		//wait here
	}
}

ISR(PCINT1_vect){
	if(!(PINC & (1<<PINC1))){
		if(toggle == 0){
			OCR0A = 0;
			PORTB &= ~(1<<PORTB2);
			_delay_ms(1000);
		}
		if (toggle == 1){
			while((ADCSRA&(1<<ADIF))==0); // wait for conversion
			
			control = ADC;				  // ADC Conversion
			OCR0A = control;			  // Output to converted value to 0CR0A
			PORTB |= (1 << PORTB2);
			_delay_ms(1000);
		}
		toggle ^= 1; //update state of motor to on
	}
}
