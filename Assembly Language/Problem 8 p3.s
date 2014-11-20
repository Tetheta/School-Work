;INSTRUCTIONS
;This program takes in a list of numbers (defined at datastart, with number in the list defined in the first MOV as N)
;Then finds the largest value of the list and stores it in r9

			GLOBAL
			AREA LargestNumber, CODE, READONLY
ENTRY
			LDR		sp, =0x40001000		;set up the stack
			LDR		r4, =datastart 		;the address of the first list element
			MOV		r5, #5				;r5 = N
			;r0 is used as ptr
			BL		sub1				;jump to our subroutine

stop		B		stop

sub1		PUSH	{r4,r5,lr}
			MOV		r9, #0				;r0 holds largest number, initialized to smallest possible
loop_st
			LDR		r7, [r4], #4		;load memory value at ptr, advance ptr
			CMP		r9, r7				;test for value > than largest so far
			BCS		small				;if value was smaller then skip load
			MOV		r9, r7				;make value new largest result
small		
			SUBS	r5, r5, #1			;decrement our counter
			BNE		loop_st				;continue looping if SUBS is not equal to 1
			POP		{r4,r5,pc}

			ALIGN
datastart	DCD		0x11111111, 0x22222222, 0x33333333, 0x94444444, 0x55555555	 ;This is the list
			ALIGN
			END