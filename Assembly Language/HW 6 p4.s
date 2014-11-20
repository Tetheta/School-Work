			GLOBAL
			AREA Reset, CODE, READONLY
ENTRY

;INSTRUCTIONS
;X and Y are stored in r0 and r1 respectively
;The X value must be reset, to do this we
;set r5 to the value of r0 every outer loop
;The loops will run X*Y number of times

;Results: 	Less than a second for X = 100, Y = 50000
;			3.0 Seconds for X = 200, Y = 100000
;			11.2 Seconds for X = 400, Y = 200000
;A)			43.5 Seconds for X = 800, Y = 400000
;B)			43.7 Seconds for X = 8000, Y = 40000
;			Given user error, it seems my program is accurate
			
HW6			LDR		r0, =8000 		;X
			LDR		r1, =40000		;Y
			
outLoop		
			MOV		r5, r0		;Reset X	
inLoop		SUBS	r5, #1		;decrement X
			BNE 	inLoop		;Loop X number of times

			SUBS 	r1, #1		;decrement Y
			BNE		outLoop	  	;Loop back to outLoop Y number of times

stop		B		stop
			END