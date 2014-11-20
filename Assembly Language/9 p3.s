;INSTRUCTIONS
;This program uses a subroutine to convert all the characters of a string to normal
;sentence case structure, then stores the result in RAM at datastart. It works with
;A single sentence, but does not change special characters

			GLOBAL
			AREA ASCIIViewer, CODE, READONLY
ENTRY
			LDR		sp, =0x40001000		;set up the stack
			LDR		r0, =charString 	;the address of the string
			LDR		r1, =datastart		;the address of the data
			BL		sub1				;jump to our subroutine

stop		B		stop

sub1		PUSH	{r5-r6,lr}
			MOV		r6, #0				;r6 = isFirstChar
loop		
			LDRB	r5,[r0],#1			;Load byte and update address
			CMP		r5, #0				;Check if it's a null terminator
			BEQ		store				;Skip to end if nullterm

			CMP		r5, #0x61			;See if it is an uppercase/special character
			BLT		chkSpecial			;Letter is uppercase or special
			CMP		r5, #0x7A			;See if letter is a special character
			BGT		store				;Letter is special character, store it
			;Letter is lowercase
			CMP		r6, #1				;Check if first letter
			BEQ		store				;Not the first letter, store it
			SUB		r5, #0x20			;Subtract 0x20 to make it uppercase ASCII
			MOV		r6, #1				;Tells us that we have dealt with first letter
			BAL		store				;Store the uppercase number

chkSpecial	CMP		r5, #0x41			;See if it is special char below alphabet
			BLT		store				;Store directly if it's below alphabet
			CMP		r5, #0x5A			;See if it's special char above alphabet
			BGT		store				;Store directly if it's between alphabets
			;Letter is uppercase
			CMP		r6, #0				;See if we have dealt with 1st letter
			BEQ		firstLtr			;skip next section if we haven't
			ADD		r5, #0x20			;Make the letter lowercase
			BAL		store				;store the lowercase letter
firstLtr	MOV		r6, #1				;Tells us that we have dealt with first letter
			BAL		store				;Store the uppercase letter

store	 	;Store the character here, check for null terms and loop
			STRB	r5,[r1],#1			;Store byte and update address
			CMP		r5,#0				;Check for our null term
			BNE		loop				;Loop if no null term, get the next byte
			POP		{r5-r6,pc}

			ALIGN
charString	DCB		"%heLLOo, WoRLd!%",0		;Set our null terminated character string
			ALIGN

			AREA 	theData, DATA, READWRITE
datastart	SPACE	20					;reserve 20 bytes of memory for data
			ALIGN

			END