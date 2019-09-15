;
; JR_DA1A.asm
;
; Created: 9/13/2019 1:53:31 AM
; Author : jreed
;


.org	0x00
start:
	ldi r25, 0xFF ; upper 8 bits of multiplicand
	ldi r24, 0xFF ; lower 8 bits of multiplicand
	ldi r23, 0xFF ; upper 8 bits of multiplier
	ldi r22, 0xFF ; lower 8 bits of multiplier
	ldi r20, 0x00 ; r20 and r19 are upper 16 bits of result
	ldi r19, 0x00 
	ldi r18, 0x00 ; r18 and r17 are lower 16 bits of result
	ldi r17, 0x00
	ldi r16, 0x00

upper:
	add r17, r24  ; adding lower 8 bits of multiplicand to r17
	adc r18, r25  ; if there is a carry from r17, it will carry over to r18
	adc r19, r20  ; if there is a carry from r18, it will carry over to r19
	subi r23, 1	  ; subtract 1 from upper 8 bits of the multiplier
	cpi r23, 0    ; checking to see if r23 (upper 8 bits of multiplier) is zero
	breq lower	  ; if so, branch to operate on lower 8 bits of multiplier
	jmp upper	  ; otherwise, continue in this loop

lower:
	add r18, r24  ; adding lower 8 bits of multiplicand to r18
	adc r19, r25  ; if there is carry from r18, it will carry over to r19
	adc r20, r16  ; if there is carry from r19, it will carry over to r20
	subi r22, 1	  ; subtract 1 from lower 8 bits of multiplier
	cpi r22, 0	  ; checking to see if r22 (lower 8 bits of multiplier) is zero
	breq end	  ; if so, end the program
	jmp lower	  ; otherwise, continue in this loop
	
end:
	jmp end		  ; loop here to end the program
