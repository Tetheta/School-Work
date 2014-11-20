		GLOBAL
		AREA Reset, CODE, READONLY
ENTRY
		LDR R1, =0x2b2b
stop	B stop
		END	