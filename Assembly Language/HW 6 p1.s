			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;This program subtracts 64bit number CD from 64 bit number AB
;Then stores the result in registers r7 and r6. 
;If r5 is 1, then the number is negative	

;Assumed A is in r0, B is in r1, C is in r2, D is in r3
;borrow is put in r4, isNeg into r5, low into r6, and high into r7
load_vals	LDR		r0, =0x00000001 ;A
			LDR 	r1, =0x00000001 ;B
			LDR 	r2, =0xffffffff ;C
			LDR 	r3, =0xffffffff ;D

HW6			MOV 	r4, #0			;initialize increment = 0
			SUBS	r6, r1, r3		;low = B - D
			BCS 	need_borrow		;skip if no need to borrow
			MOV		r4, #1			;set borrow true

need_borrow	SUBS	r7, r0, r2		;high = A - C
			BCS		AlessC			;skip if A is greater than C
			MOV		r5, #1			;set isNegative (r5) to true

AlessC		SUBS	r7, r7, r4		;high = high - borrow
			BCS		AnslessBrw		;skip if Answer is greater than Borrow
			MOV		r5, #1			;set isNegative (r5) to true

AnslessBrw	CMP		r5, #1
			BNE 	isNeg			;skip if not negative
			MVN		r7, r7			;Switch all bits of first part of answer
			MVN		r6, r6			;Switch all bits of second part of answer
			ADD		r6, #1			;Now it is a negative number

isNeg								;continue
stop		B		stop
			END