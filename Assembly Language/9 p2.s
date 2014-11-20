;INSTRUCTIONS
;This program uses a subroutine to convert all the characters of a string to uppercase
;and then stores it in RAM. It only works with strings made strictly of characters with
;a null terminator

			GLOBAL
			AREA ASCIIViewer, CODE, READONLY
ENTRY
			LDR		sp, =0x40001000		;set up the stack
			LDR		r0, =charString 	;the address of the string
			LDR		r1, =datastart		;the address of the data
			BL		sub1				;jump to our subroutine

stop		B		stop

charString	DCB		"Hello World",0		;Set our null terminated character string

sub1		PUSH	{r0,lr}
			LDRB	r5,[r0],#1			;Load byte and update address
			CMP		r5, #0				;Check if it's a null terminator
			BEQ		store				;Skip to end if nullterm
			CMP		r5,#0x60			;See if it is already uppercase
			BLT		store		 		;Letter is already uppercase, skip changing it
			SUB		r5, #0x20			;Subtract 0x20 to make it uppercase ASCII
store	 
			STRB	r5,[r1],#1			;Store byte and update address
			CMP		r5,#0				;Check for our null term
			BNE		sub1				;Loop if no null term, get the next byte
			POP		{r0,pc}

			AREA 	theData, DATA, READWRITE
datastart	SPACE	20					;reserve 20 bytes of memory for data
			ALIGN

			END