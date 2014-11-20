;INSTRUCTIONS
;This program uses a subroutine to output a null terminated character string.
;The string is stored in ROM then loaded and stored in to RAM at 0x40000000

			GLOBAL
			AREA ASCIIViewer, CODE, READONLY
ENTRY
			LDR		sp, =0x40001000		;set up the stack
			LDR		r0, =charString 	;the address of the string
			LDR		r1, =datastart		;the address of the data
			BL		sub1				;jump to our subroutine

stop		B		stop

charString	DCB		"Hello World",0			;Set our null terminated character string

sub1		PUSH	{r0,lr}
			LDRB	r5,[r0],#1			;Load byte and update address
			STRB	r5,[r1],#1			;Store byte and update address
			CMP		r5,#0				;Check for our null term
			BNE		sub1				;Loop if no null term, get the next byte
			POP		{r0,pc}

			AREA 	theData, DATA, READWRITE
datastart	SPACE	20					;reserve 20 bytes of memory for data
			ALIGN

			END