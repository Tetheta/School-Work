		GLOBAL
		AREA Reset, CODE, READONLY
ENTRY
		MOV R1, #0x2c
		ADD R2, R1, #0x2c
stop	B stop
		END	