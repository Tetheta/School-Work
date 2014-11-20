			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;This program divides Y by X, placing the quotient in r0 and the remainder in r1
;Mathematically: Y/X = r0 (with remainder of r1)
;If this is an illegal divide (IE divide by zero) r10 will be set to 1

HW6			LDR		r3, =0x0f0f0f0f	;Dividend, Y
			LDR		r2, =0x0000000e	;Divisor, X

			MOV		r0, #0			;clear the quotient count

			CMP		r2, #0 			;See if we are trying to divide by zero
			MOVEQ	r10, #1			;Set our illegal divide flag to true 
			BEQ		div0			;We are dividing by Zero, emergency measures!
loop		
			SUBS	r3, r3, r2		;Subtract X from Y, store in Y
			ADD		r0, #1			;Count the number of times we subtract (aka divide)
			BPL		loop			;Keep looping until it's negative

			ADD		r3, r3, r2		;Go back a step, we're in the negatives now
			SUB		r0, #1			;Subtract one, to get the correct count
			MOV		r1, r3			;Store the remainder in r1

div0								;Continue
stop		B		stop
			END