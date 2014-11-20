		GLOBAL
		AREA Reset, CODE, READONLY
ENTRY
		MOV R1, #0x2b
stop	B stop
		END	