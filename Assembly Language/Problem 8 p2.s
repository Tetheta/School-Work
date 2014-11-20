;INSTRUCTIONS
;This program takes two 64 bit numbers A and B and adds them, then sets R10 to 1 if there is an additional carry.

			GLOBAL
			AREA Summation, CODE, READONLY
			EXPORT Reset_Handler

Reset_Handler
ENTRY
			LDR		sp, =0x40001000		;set up the stack

			LDR		r0, =0xffffffff		;A - Low
			LDR		r1, =0x00000001		;A - High
			LDR		r2, =0xffffffff		;B - Low
			LDR		r3, =0xffffffff		;B- High

			MOV		r10, #0				;set carry to 0

			BL		add64bit			;run add subroutine		
			
stop		BAL		stop

add64bit	PUSH	{r4, r5, lr}		;save return address, we're using r4 here
			ADDS	r4, r0, r1			;Add the lower numbers
			ADCS	r5, r2, r3			;Add the higher numbers with carry
			BCC		noCarry				;check if there was a carry
			MOV		r10, #1				;set carry to 1
noCarry
			POP		{r4, r5, pc}		;return

			END