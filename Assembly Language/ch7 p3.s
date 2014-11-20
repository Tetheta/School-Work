;INSTRUCTIONS
;This program takes a list of 5 numbers (defined at datastart, with number in the list defined at Numvals)
;Then computes the sum of the five numbers, holding the result in successive memory locations

Numvals		EQU		5					;number of items in the list

			GLOBAL
			AREA Summation, CODE, READONLY
			EXPORT Reset_Handler

Reset_Handler
ENTRY

; r3 holds count and r4 holds total, r5 is the pointer to the data, ptr
			MOV		r3, #Numvals		;initialize count
			MOV		r4, #0				;initialize total
			LDR		r5, =datastart		;set ptr to the start of the data
		;start of addition loop
wloop
			BEQ		stop				;If SUBS said it was equal, break the loop
			LDR		r6, [r5], #4		;get value at ptr, advance ptr
			ADD		r4, r4, r6			;add value to total
			SUBS	r3, r3, #1			;decrement count
			BAL		wloop				;loop
			
stop		BAL		stop

datastart	DCD		0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555	 ;This is the list

			END