			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;This program compares three 32bit numbers A, B, and C 
;It then stores the lowest number of the three in temporary storage at r0

;Assumed A is in r1, B is in r2, C is in r3
;temp is in r0
load_vals	LDR		r1, =0x00011111 ;A
			LDR 	r2, =0x00010001 ;B
			LDR 	r3, =0x00001000 ;C
			
HW6			SUBS 	r10, r1, r2		;Compute A - B so carry is set if A > B
			MOV		r0, r1			;Assume A is smaller to prevent excessive branching
			BCC		A_Smaller		;Branch if A is smaller
			MOV		r0, r2			;B is smaller, so put B in r0

A_Smaller	SUBS	r10, r3, r0		;Subtract the smaller number from C
			BCS		Ans_Smaller		;Branch if the number in r0 is smaller
			MOV		r0, r3			;C is smaller, so put C in r0

Ans_Smaller							;continue

stop		B		stop
			END