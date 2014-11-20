			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;This program takes in a list of numbers (defined at datastart, with number in the list defined in the first MOV)
;Then finds the largest value by counting in a loop up from zero to the desired number.

;Comments for homework: 
;The only difference is in lines 27 and 28 where I use ADD and CMP instead of a SUBS, and then I also add a zero
;counter in line 20 which I use to compare to my desired number. It's less efficient than the book's method
;but still gets the job done.


HW9			LDR		r4, =datastart 		;datastart is the address of the first list element
			MOV		r5, #5				;the number of items in the list
			;r4 is used as ptr and r5 as count

			MOV		r0, #0				;r0 holds result, initial value zero is the smallest
										;possible unsigned int
			MOV 	r10, #0				;set our counter

;FOR STANDARD LOOP COUNT UP:
loop_st
			LDR		r7, [r4], #4		;load memory value at ptr, advance ptr
			CMP		r0, r7				;test for value > than largest so far
			BCS		small				;if value was smaller then skip load
			MOV		r0, r7				;make value new largest result
small		
			ADD		r10, r10, #1		;count up number done
			CMP		r10, r5				;Compare to number you need to do
			BNE		loop_st				;continue looping if more to do

;FOR WHILE LOOP COUNT UP
;while_st	;while loop entry point to check if r5 == r10
;			CMP		r10, r5				;Compare our counter to how many we need to do
;			BEQ		stop				;all done!
;			LDR		r7, [r4], #4		;load memory value at ptr, advance ptr
;			CMP		r0, r7				;test for value > than largest so far
;			BCS		small				;if value was smaller then skip load
;			MOV		r0, r7				;make value new largest result
;small		
;			ADD		r10, r10, #1		;add to our counter
;			BAL		while_st			;loop!

;FOR WHILE LOOP COUNT DOWN
;while_st	;while loop entry point to check if r5 == 0
;			BEQ		stop				;Check if the SUBS set a flag, if it did, we're done!
;			LDR		r7, [r4], #4		;load memory value at ptr, advance ptr
;			CMP		r0, r7				;test for value > than largest so far
;			BCS		small				;if value was smaller then skip load
;			MOV		r0, r7				;make value new largest result
;small		
;			SUBS	r5, r5, #1			;decrement our counter
;			BAL		while_st			;loop!

stop		B		stop

			ALIGN
datastart	DCD		0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555	 ;the list
			ALIGN
			END