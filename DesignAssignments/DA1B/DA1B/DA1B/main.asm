;
; DA1B.asm
;
; Created: 9/22/2019 3:13:07 PM
; Author : jreed
;

	.equ STARTADDS = 0x0200 ; set starting address
	.equ FIVEADDS = 0x0300 ; set address for numbers divisible by 5
	.equ ELSEADDS = 0x0500 ; set address for any other number
	ldi	ZL, LOW(STARTADDS)  ; ZL=0x00
	ldi ZH, HIGH(STARTADDS) ; ZH=0x02
	ldi R20, 0x05			; load R20 with starting value to store (decimal 5)
	ldi R21, 0xFA			; load R21 with counter value (decimal 255)


L1:	st	Z+, R20				; Z=R20 then increment pointer (e.g. 0x0200 -> 0x0201)
				inc R20					; increment value to be stored (e.g. 5 -> 6)
				dec	R21					; R21 -= 1
				brne L1		; loop until R21=0 (255 iterations)
; the code above should store each incremented value as the pointer moves

; --- SEPARATING AND ADDING VALUES ---
	ldi	ZL, LOW(STARTADDS)  ; ZL=0x00
	ldi ZH, HIGH(STARTADDS) ; ZH=0x02
	ldi YL, LOW(FIVEADDS)	; YL=0x00
	ldi YH, HIGH(FIVEADDS)	; YH=0x03
	ldi XL, LOW(ELSEADDS)	; XL=0x00
	ldi XH, HIGH(ELSEADDS)	; XH=0x05
	ldi R16, 0				; initialize sum register to zero
	ldi R17, 0				; initialize sum register to zero
	ldi R18, 0				; initialize sum register to zero
	ldi R19, 0				; initialize sum register to zero
	ldi R20, 250			; load R20 with counter value
	ldi R22, 0
	ldi R23, 0				; used to add carry

PARSE:			ld	R21, Z+				; R21=Z then inc Z
				mov	R22, R21			; R22=R21

DIVFIVE:		subi R21, 0x05		; R21 -= 5 to check for divisibility
				breq DIV			; branch if R21 = 0 (divisible by 5)
				brsh DIVFIVE		; branch if R21 >= 5, continue parsing

				st	X+, R22				; store value not divisible by 5
				add	R18, R22			; add value to running sum
				adc	R19, R23			; add carry

				rjmp CONT_PARSE			; jump to continue parsing

DIV:		st	Y+, R22				; store value divisible by 5
			add	R16, R22			; add value to running sum
			adc	R17, R23			; add carry

CONT_PARSE:	dec	R20					; R20 -= 1
			brne PARSE				; loop until R20=0

END: jmp END			; end of program
