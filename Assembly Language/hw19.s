 ; Hillary Smith & Travis Crumley  CPTR215   Homework 19
 ; Design and implement an assembly language program that will “drive” the class vehicle
 ; autonomously to follow a black line on a white piece of paper.
 ; Pressing the center joystick switch will cause the vehicle to stop. 
 ; Pressing joystick up will start vehicle motion forward. 


	

 ; shell and subroutines copied from Larry Aamodt's webpage
;---------------------------------------------------------------------------
;
;   Programmer  : Larry Aamodt
;
;   File name  	: shell_2148.s 
;   Class       : CPTR-215
;   Language    : ARM assembly
;   Assembler   : Keil
;   Target MCU	: NXP LPC-2148 on Embedded Artists board
;   Date Written: 11/30/09  
;    change history:  11/30/09  LDA  Updated with hardware start-up
;    		      12/03/09  LDA  PWM register definitions added 
;   Description	: 
;
;   Inputs      :
;   
;   Outputs     :
;
;   Special     :  
;  requirements
;   
;
; 	NOTES: 
;
; 
;
;---------------------------------------------------------------------------

; Put application program definitions (i.e. equates) here:


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled

;  Memory addresses for standard GPIO definitions
IO0PIN		    EQU     0xE0028000
IO0SET		    EQU     0xE0028004
IO0DIR		    EQU     0xE0028008
IO0CLR		    EQU     0xE002800C
;  Memory addresses for Pulse Width Modulation (PWM)
PWM_TCR         EQU     0xE0014004      ; PWM_TCR Timer Control Register
PWM_PR          EQU     0xE001400C      ; PWM_PR Prescaler Register
PWM_MCR         EQU     0xE0014014      ; PWM_MCR Match Control Register
PWM_MR0         EQU     0xE0014018      ; PWM_MR0 Match Register 0 (sets pulse period)
PWM_MR4         EQU     0xE0014040      ; PWM_MR4 Match Register 4 (sets pulse length)
PWM_MR6         EQU     0xE0014048      ; PWM_MR6 Match Register 6 (sets pulse length)
PWM_PCR         EQU     0xE001404C      ; PWM_CR Control Register
PWM_LER         EQU     0xE0014050      ; PWM_LER Latch Enable Register

PINSEL0         EQU     0xE002C000      ; Pin connect block - port 0
PINSEL1         EQU     0xE002C004      ; Pin connect block - port 1

; Memory addresses for A/D Reader
AD1CR 			EQU		0xE0060000	
AD1DR6 			EQU		0xE0060028
AD1DR7			EQU		0xE006002C	
;  Stack size definitions
UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000008
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000080
USR_Stack_Size  EQU     0x00000400

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM


; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         LDR     PC, Reset_Addr         
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
                NOP                            ; Reserved Vector 
;               LDR     PC, IRQ_Addr
                LDR     PC, [PC, #-0x0FF0]     ; Vector from VicVectAddr
                LDR     PC, FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                      ; Reserved Address 
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
IRQ_Handler     B       IRQ_Handler
FIQ_Handler     B       FIQ_Handler

; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler   

; Setup Stack for each mode

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR

                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size


; User program code goes here
;Instructions:
;First off, I am using the car with the white wheels for this program, as there
;were errors/availability issues with the orange-wheeled vehicle.
;There are many car-specific values, so make sure you test on the white-wheeled
;vehicle

;This program uses light sensors and two motors to drive a small device around
;following a black line (against a white background). I am using Larry Aamodt's
;subroutines, with my own defined stack pointer
;I have two flags, r9 and r10 that basically act as state machines for the 
;center button actions and runtime actions respectively.
;Some things to note: 
;Joystick inputs are active when low
;I use a process of reading in the IO0PIN and masking it to read the joystick
;The car should go forward when on white until it hits a black line and then 
;it should follow said black line until it is (it ran fine on the test track)

main
	LDR	sp, = 0x40001000	 		; Load stack pointer
	LDR r4,=IO0PIN					; Load the address of I/O port 0 pin register
	MOV	r9, #0						; Flag, Moving = 1, Stopped = 0
	MOV r10, #0						; Flag, Forward = 0, Left = 1, Right = 2
	BL pwm_init						; Initialize the pwm
	BL ad_init						; Initialize the a/d sensor
stop
	MOV	r0,#3						; Tell the subroutine to talk to both motors
	LDR r1,=1435					; Prepare to stop the left motor
	LDR r2,=1530					; Prepare to stop the right motor
	BL pwm_update					; Stop the motors
check_js
	LDRB r5,[r4,#2]					; Check to see if the joystick is pressed
	AND r5,r5,#0x1f					; Mask the input to get the values we want
	LDR r6,=0x1f					; Load a mask of sorts to check if joystick is pressed
	CMP r5,r6						; Check if joystick is being pressed
	BEQ noChange					; If joystick isn't pressed, do what we were doing
up
	LDR r6,=0x1d	    			; Check to see if the joystick is pressed up
	CMP r5,r6						
	BNE center						; Jump to center if not
	MOV	r9, #1						; Set the moving flag
readAD
	BL ad_read
	; The following checks to see if both are on the white
	CMP r0,#0x40					; See if left sensor is on the black line
	BLT	checkValues					; If it is, skip to checkValues
	CMP	r1,#0x40					; See if right sensor is on the black line
	BLT	checkValues					; If it is, jump to checkvalues
	BAL turn						; Both sensors are on the white, just go forward
	; Now we check to see which direction to turn
checkValues
	CMP r0,#0x40					; See if the left sensor is on the black line
	BLT	turnLeft					; Left sensor is on the line, turn left!
	CMP	r1,#0x30					; See if the right sensor is on the black line
	BLT	turnRight					; Right sensor is on the line, turn right!
	BAL	turn
turnRight
	CMP r0, #0x40					; See if both sensors are on the line
	MOVLT r10, #0					; If they're both on black, go forward
	BLT	turn						; Run forwards
	MOV r10, #2						; Set our turn right flag
	MOV r0, #3						; Tell the subroutine to talk to both motors
	BL turn							; Turn left
turnLeft
	CMP r1, #0x40					; See if both sensors are on the line
	MOVLT r10, #0					; If they're both on black, go forwards
	BLT turn						; Run forwards
	MOV r10, #1						; Set our turn left flag
	BL turn							; Turn left
turn
	MOV r0,#3						; Tell the subroutine to talk to both motors
	CMP	r10, #1						; Check our turn flag
	BEQ left						; Turn left if equal
	BGT	right						; Turn right if greater than

	;If neither is set, then assume it's forward and go forward
	LDR r1,=1410					; Prepare to move the left wheel forward
	LDR r2,=1655					; Prepare to move the right wheel forward
	BAL update
left
	LDR r1, =1435					; Stop the left wheel to turn left
	LDR r2, =1565					; Make right wheel go forward slowly
	BAL update
right
	LDR r2, =1425					; Make the left wheel go forward slowly
	LDR r2, =1535					; Stop the right wheel to turn right	
	BAL update
update
	BL pwm_update					; Move the car forward
	B check_js						; Check the joystick again
center
	LDR r6,=0x1e					; Check to see if the joystick is pressed center
	CMP r5,r6						; Check with our earlier mask to see if pressed
	BNE check_js					; Check the joystick again if not
	MOV	r9, #0						; Set our flag to stopped
	B stop							; Branch to stop if it is stopped

noChange
	CMP	r9, #1						; See if our flag is set or not
	BEQ	readAD						; If it's 1, read the AD again
	BL	check_js					; If not, keep checking (we're already stopped)

; To follow the line, slow the motor opposite the sensor that loses the line until the sensor finds the line once again.

;*****************************************************************************
;    Pulse width modulator initialization routine.
;          pulse period = 20ms;  initial pulse length = 1.5ms
;          (values shown are for controlling model plane servos)
;    Inputs: none
;    Returned values: none
;    Uses registers r0, r1
;
;    Calling method:   BL   pwm_init
;                                                   LDA   rev 1.0  12/01/10
;*****************************************************************************
pwm_init		STMFD	sp!,{r14}		; save link register on the stack

		        LDR     r0,=PWM_PR
				LDR     r1,=2			; prescaler = 2 divides PCLK by 3
                STR     r1,[r0]         ; load prescaler
                                        ; PCLK rate is 1 MHZ (1 uSEC period)
                LDR     r0,=PWM_MCR
				LDR     r1,=0x02        ; bit 1 is set, others are zero
				STR     r1,[r0]         ; load PWM_MCR: PWM_TC resets when PWM_TC=PWM_MR0

                LDR     r0,=PWM_MR0
				LDR     r1,=20000       ; count 20,000 1uSEC intervals = 20 milli secs
				STR     r1,[r0]         ; load match register 0. sets pulse period

				LDR     r0,=PWM_MR4
                LDR     r1,=1500		; initial pulse width = 1.5 milli secs
				STR     r1,[r0]         ; load match register 4
				LDR     r0,=PWM_MR6
				LDR     r1,=1500		; initial pulse width
				STR     r1,[r0]			; load match register 6

	            LDR     r0,=PWM_LER
				LDR     r1,=0x51
				STR     r1,[r0]         ; Enable latch registers 0, 4, & 6

                LDR     r0,=PWM_PCR
				LDR     r1,=0x5000      ; bits 12 & 14 set
				STR     r1,[r0]         ; load PWM_CR: enables PWM4 and PWM6 outputs

                LDR     r0,=PWM_TCR
				LDR     r1,=0x09        ; bits 3,1,0 set
				STR     r1,[r0]         ; load PWM_TCR enable PWM counter & prescaler

                LDR     r0,=PINSEL0
                LDR     r1,=0xA0000     ; bits 19 & 17 set.  selects output PWM 6 & 4
				STR     r1,[r0]		    ; Enable PWM6 & PWM4 outputs

end_pwm_init	LDMFD	sp!,{pc}		; Return from subroutine  pwm_init


;*****************************************************************************
;   Pulse width modulator update routine
;	Inputs:  r0 = command
;                   1 = update PWM channel 4
;                   2 = update PWM channel 6
;                   3 = update both channel 4 and 6
;            r1 = new pulse width (# of microseconds) for PWM channel 4
;            r2 = new pulse width (# of microseconds) for PWM channel 6
;   Returned values: none
;   Uses registers r0, r1, r2, r3
;
;   Calling method:  first put values in r0, r1, r2 as appropriate
;                    BL pwm_update
;                                                   LDA    rev 2.0  12/01/11
;*****************************************************************************

pwm_update		STMFD	sp!,{r14}		; r0 specifies channels to update 

load_pwm4		CMP		r0,#1			; 1 = load PWM chan 4
				BNE		load_pwm6
				LDR     r3,=PWM_MR4
				STR     r1,[r3]         ; load match register 4

load_pwm6		CMP		r0,#2			; 2 = load PWM chan 6
				BNE		load_both
				LDR     r3,=PWM_MR6
				STR     r2,[r3]			; load match register 6

load_both		CMP		r0,#3
				BNE		pwm_reg_update
				LDR		r3,=PWM_MR4
				STR		r1,[r3]
				LDR		r3,=PWM_MR6
				STR		r2,[r3]

pwm_reg_update	CMP		r0,#1			; check for just pwm 4 update
				MOVEQ	r1,#0x10
				CMP		r0,#2			; check for just pwm 6 update
				MOVEQ	r1,#0x40
				CMP		r0,#3			; check for pwm 4 & 6 update
				MOVEQ	r1,#0x50

				LDR		r3,=PWM_LER
				STR		r1,[r3]			; enable latch registers

end_pwm_update	LDMFD	sp!,{pc}		; Return from subroutine  pwm_update


;*****************************************************************************
;  A/D converter initialization subroutine.  Sets up for reading A/D
;      channels AD1.6 and AD1.7 to which vehicle sensors left and right are
;      connected.
;
;  Inputs:  none
;  Returned Values: none
;  Registers used: ro, r1
;
;  NOTES:
;     This routine written for the simple vehicle. Call it once.
;     analog sensor inputs come in on AD1.6 and AD1.7  (P0.21 & P0.22)
;        (A/D converter #1 on channels 6 and 7)
;     Use AD1CR register at 0xE0060000
;     sets the following bits to one in AD1CR: (0xE0060000)			 (pg 267)
;         bit 21 (A/D on)
;         bit 16 (burst mode, i.e. A/D continously does conversions)
;         bit 6  (turns on channel 6)
;         bit 7  (turns on channel 7)
;     Reads data from AD1DR6 at 0xE0060028 and AD1DR7 at 0xE006002C	 (pg 266)
;     Sets I/O pins P0.21 & P0.22 for analog input (AD1 ch 6 & 7 respectively)  
;        by setting bits 11 and 12 in PINSEL1 (0xE002C004)			 (pg 78)
;            	(page numbers above refer to the NXP LPC2148 users manual)
;*****************************************************************************

ad_init			STMFD	sp!,{lr}
				LDR		r1,=PINSEL1      ; load address of Pin Function selection reg #1
				LDR     r0,=0x1800       ; set bits 11 & 12 for pins P0.21 & P0.22 as input
				STR     r0,[r1]
				LDR		r1,=AD1CR		 ; get address of AD 1 control register
                LDR     r0,=0x2100C0     ; A/D on, burst mode, chs 6 & 7 to be converted
				STR		r0,[r1]
end_ad_init		LDMFD	sp!,{pc}




;*****************************************************************************
;  Read vehicle photo sensors.
;      Reads channels AD1.6 and AD1.7 to which vehicle sensors left 
;      and right are connected.
;
;  Inputs:  none
;  Returned Values: ro = left sensor voltage.  0 to 3FF  (3FF =2 volts)
;                   r1 = right sensor voltage. 0 to 3FF
;
;  Registers used: ro, r1, r2
;
;  Note: ad_init must be called once prior to calling ad_read
;*****************************************************************************

ad_read			STMFD	sp!,{lr}
				LDR		r2,=AD1DR6		; channel 6 data register address
				LDR		r0,[r2]			; read left sensor voltage
				LDR		r2,=AD1DR7		; channel 7 data register address
				LDR		r1,[r2]			; read right sensor voltage
				MOV		r0,r0,ASR #6	; shift right to justify the value
				MOV		r1,r1,ASR #6
				LDR		r2,=0x3FF		; 10 bit mask
				AND		r0,r0,r2		; set upper bits to zero if set
				AND		r1,r1,r2
end_ad_read		LDMFD	sp!,{pc}

; User data area definition follows

                AREA  appdata, DATA, NOINIT, READWRITE

                END
