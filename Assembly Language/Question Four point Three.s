		GLOBAL
		AREA Reset, CODE, READONLY

ENTRY
		;MOV r1, #127				; Storing Decimal 127 at r1
		;LDR r2, =0xe45ad			; Storing large hex e45ad at r2
		;LDR r3, =2_10101110010		; Storing large binary at r3
		;ADD r4, r1, r2			 	; add 127 and the hex number
		;ADD r4, r3, r4			  	; add the sum of above and the binary number
		ADD r6, r6, #1

stop	B stop
		END	