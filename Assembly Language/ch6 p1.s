			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;This program divides Y by X, placing the quotient in r0 and the remainder in r1
;Mathematically: Y/X = r0 (with remainder of r1)
;If this is an illegal divide (IE divide by zero) r10 will be set to 1

HW9			LDR		r4, =list_start 	;list_start is the address of the first list element
			LDR		r5, =list_len		;the number of items in the list (defined elsewhere)
			;r4 is used as ptr and r5 as count

			MOV		r0, #0				;r0 holds result, initial value zero is the smallest
										;possible unsigned int

loop_st
			LDR		r7, [r4], #4		;load memory value at ptr, advance ptr
			CMP		r0, r7				;test for value > than largest so far
			BCS		small				;if value was smaller then skip load
			MOV		r0, r7				;make value new largest result
small		
			SUBS	r5, r5, #1			;count down number to do
			BNE		loop_st				;continue looping if more to do

stop		B		stop
			END