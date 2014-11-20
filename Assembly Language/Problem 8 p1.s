;INSTRUCTIONS
;This program delays for a number of seconds decided in sub1 (or alternately could declare them outside of the sub). It is specific to my computer

			GLOBAL
			AREA delayer, CODE, READONLY
			EXPORT Reset_Handler

Reset_Handler
ENTRY
			LDR		sp, =0x40001000		;set up the stack
			BL		sub1				;wait N, where N = r7 seconds		
			
stop		BAL		stop

delay		PUSH	{r4, lr}			;save return address, we're using r4 here
			LDR		r4, =0x005bbbbb		;set delay count/timer
wait		SUBS	r4, r4, #1			;decrement delay count (S to set flags)
			BNE 	wait				;if not zero, loop
			POP		{r4, pc}			;return

sub1		PUSH	{r4, r7, lr}		;save return address and addresses r7 and r4
			MOV		r7, #15				;set seconds to delay
loop		BL		delay				;run delay subroutine
			SUBS	r7, r7, #1			;decrement seconds to delay
			BNE		loop				;loop if not 0
			POP		{r4, r7, pc}		;return

			END