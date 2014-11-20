			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
			
HW6			MOV		r4, #8 		;load counter
			MOV		r5, #0		;load incrementer
loop		
			SUBS 	r4, #1		;decrement
			ADD		r5, #1		;increment!
			BPL		loop
stop		B		stop
			END