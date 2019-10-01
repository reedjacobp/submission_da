;
; DA2A_asm.asm
;
; Created: 9/27/2019 5:45:57 PM
; Author : jreed
;


.org 0x00

LDI R16, 0xFF ; R16 = 0b11111111
OUT DDRB, R16 ; make PORTB as an output
OUT PORTB, R16 ; all LEDs should turn off
LDI R16, 0x00 ; R16 = 0b00000000
OUT DDRC, R16 ; switches are inputs

START: CBI PORTB, 3 ; turn on PB5/D1

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

SBIS PINC, 3 ; skip next instruction if switch is pressed
RJMP TASK2 ; go to task 2 if switch is pressed
RJMP START ; if switch is not pressed, go back to the beginning of code

TASK2: CBI PORTB, 2 ; turn on PB2/D4

; 1.333 sec delay
		LDI  R18, 109
		LDI  R19, 51
		LDI  R20, 106
DELAY3: DEC  R20
		BRNE DELAY3
		DEC  R19
		BRNE DELAY3
		DEC  R18
		BRNE DELAY3

SBI PORTB, 2 ; turn off PB2/D4
RJMP START ; go back to the beginning of code


