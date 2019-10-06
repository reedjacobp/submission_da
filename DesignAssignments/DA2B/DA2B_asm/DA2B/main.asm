;
; DA2B.asm
;
; Created: 10/5/2019 6:03:29 PM
; Author : jreed
;


.ORG 0x00
JMP MAIN
.ORG 0x02
JMP TASK2
MAIN:
	LDI R20, HIGH(RAMEND) ; initialize the stack
	OUT SPH, R20
	LDI R20, LOW(RAMEND)
	OUT SPL, R20

	LDI R20, 0x02 ; trigger interrupt on falling edge
	STS EICRA, R20

	SBI DDRB, 3 ; make DDRB3 output
	SBI PORTB, 3 ; make PORTB3 high
	SBI PORTD, 2 ; INT0
	CBI DDRC, 3 ; make DDRC3 input
	SBI PORTC,3 ; make PORTC3 high

	LDI R20, 1<<INT0
	OUT EIMSK, R20
	SEI ; enable interrupt

START:

CBI PORTB, 3 ; turn on PB5/D1

; 250 ms delay loop
		LDI  R18, 21
		LDI  R19, 75
		LDI  R20, 191
DELAY1: DEC  R20
		BRNE DELAY1
		DEC  R19
		BRNE DELAY1
		DEC  R18
		BRNE DELAY1
		NOP

SBI PORTB, 3 ; turn off PB5/D1

; 375 ms delay loop
		LDI  R18, 31
		LDI  R19, 113
		LDI  R20, 31
DELAY2: DEC  R20
		BRNE DELAY2
		DEC  R19
		BRNE DELAY2
		DEC  R18
		BRNE DELAY2
		NOP


JMP START ; if switch is not pressed, go back to the beginning of code

TASK2:

	IN R21, PORTB
	LDI R22, (1<<2)
	EOR R21, R22
	OUT PORTB, R21

; 1.333 sec delay
		LDI  R18, 109
		LDI  R19, 51
		LDI  R20, 106
DELAY3: DEC  R20
		BRNE DELAY3
		DEC  R19
		BRNE DELAY3
		DEC  r18
		BRNE DELAY3

RETI ; return from interrupt
