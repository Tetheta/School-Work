			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;This program takes in a list of numbers (defined at datastart, with number in the list defined in the first MOV)
;Then finds the largest value of the list and stores it in r0
;It then finds the smallest value of the list and stores it in r1


HW9			LDR		r4, =datastart 		;list_start is the address of the first list element
			MOV		r5, #5				;the number of items in the list
			;r4 is used as ptr and r5 as count

			MOV		r0, #0				;r0 holds largest number, initialized to smallest possible
			MOV		r1, #0xffffffff		;r1 holds smallest number, initialized to largest possible

loop_st
			LDR		r7, [r4], #4		;load memory value at ptr, advance ptr
			CMP		r0, r7				;test for value > than largest so far
			BCS		small				;if value was smaller then skip load
			MOV		r0, r7				;make value new largest result
small		
			CMP		r1, r7				;test for value < than smallest so far
			BCC		loop_cont			;if value was larger than skip load
			MOV		r1, r7				;make value new smallest result
loop_cont
			SUBS	r5, r5, #1			;decrement our counter
			BNE		loop_st				;continue looping if SUBS is not equal to 1

stop		B		stop

			ALIGN
datastart	DCD		0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555	 ;This is the list
			ALIGN
			END