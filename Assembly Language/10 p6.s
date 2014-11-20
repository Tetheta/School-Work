;INSTRUCTIONS
;This program divides Y by X, placing the quotient in r0 and the remainder in r1
;Mathematically: Y/X = r0 (with remainder of r1)
;If this is an illegal divide (IE divide by zero) r10 will be set to 1
;For some reason is only works for numbers <= 0xffff for dividend. 
;I think this is because the only example in the book was very limited
;and thus I'm not sure what I need to do to make a true 32 bit version

			GLOBAL
			AREA Divider, CODE, READONLY
ENTRY

			LDR		r7, =0x0000ffff	;Dividend, Y
			LDR		r2, =0x000000ff	;Divisor, X
			BL		divSub			;Jump to our subroutine

stop		B		stop

divSub		
			PUSH	{r5-r10,lr}
			MOV		r0, #0			;clear the quotient count
			CMP		r2, #0 			;See if we are trying to divide by zero
			MOVEQ	r10, #1			;Set our illegal divide flag to true 
			BEQ		div0			;We are dividing by Zero, emergency measures!
			MOV		r5, #31			;Set a counter for number of shifts
			
loop		CMP		r5, #0			;See if our counter reached 1 or less
			BLT		done			;We're done if the counter is less than 0
			MOV		r9, r2			;set r9 = r2
			LSL		r9, r5			;shift the divisor left
			SUB		r5, #1			;decrement counter
			CMP		r9, #0			;make sure it's not zero
			BEQ		nosub			;skip to the next loop
			CMP		r7, r9			;Compare to see if we can subtract
			BHI		subtract		;subtract
			BEQ		subtract		;subtract
nosub		LSL		r0, #1			;No subtract, but still keep shifting
			BAL		loop			;Loop

subtract	SUBS	r7, r7, r9		;Subtract shifted X from Y, store in Y
			LSL		r0, #1			;Shift it left for this type of division
			ADD		r0, #1			;Count the number of times we subtract (aka divide)
			BPL		loop

done		
			MOV		r1, r7			;Store the remainder in r8
div0		;Continue
			POP		{r5-r10,pc}

			END