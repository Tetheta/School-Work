 ; Hillary Smith & Travis Crumley  CPTR215   Homework 18
 ; Design and implement a program that will control both motors on the class vehicle and allow it to be "driven" using the joystick to steer it.
 ; The vehicle should be capable of driving straight ahead or reverse in a straight line. It should be able to go right by slowing the right wheel
 ; while the left continues to turn at normal speed. Likewise it should be able to turn left by slowing the left wheel. 

 ; Using the car with the orange wheels:
 ; When the joystick is not pressed, the vehicle will not move
 ; Up will make the vehicle move forward
 ; Down will make the vehicle move backward
 ; Right will make the vehicle turn to the right
 ; Left will make the vehicle turn to the left 
 ; Up-Left will make the vehicle move forward and to the left
 ; Up-Right	will make the vehicle move forward and to the right
 ; Down-Left will make the vehicle move backwards and to the left
 ; Down-Right will make the vehicle move backwards and to the right
 ; Center does nothing
	

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

main
	LDR r4,=IO0PIN					; load the address of I/O port 0 pin register

	BL pwm_init						; initialize the pwm

off
	MOV	r0,#3						; tell the subroutine to talk to both motors
	LDR r1,=1520					; prepare to stop the left motor
	LDR r2,=1550					; prepare to stop the right motor
	BL pwm_update					; stop the motors
check_js
	LDRB r5,[r4,#2]					; check to see if the joystick is pressed
	AND r5,r5,#0x1f
	LDR r6,=0x1f
	CMP r5,r6						
	BEQ off							; turn off the motor(s) and check the joystick again if not
up
	LDR r6,=0x1d	    			; check to see if the joystick is pressed up
	CMP r5,r6						
	BNE down						; jump to down if not
	MOV r0,#3						; tell the subroutine to talk to both motors
	LDR r1,=1380					; prepare to move the left wheel forward
	LDR r2,=1610					; prepare to move the right wheel forward
	BL pwm_update					; move the car forward
	B check_js						; check the joystick again
down
	LDR r6,=0x0f					; check to see if the joystick is pressed down
	CMP r5,r6						
	BNE right						; jump to right if not
	MOV r0,#3						; tell the subroutine to talk to both motors
	LDR r1,=1630 					; prepare to move the left wheel backwards
	LDR r2,=1450					; prepare to move the right wheel backwards
	BL pwm_update					; move the car backwards
	B check_js						; check the joystick again
right
	LDR r6,=0x1b					; check to see if the joystick is pressed right
	CMP r5,r6						
	BNE left						; jump to left if not
	LDR r1,=1380 					; prepare to move the left wheel forwards at full speed
	LDR r2,=1550					; prepare to stop the right wheel
	BL pwm_update					; turn the car right
	B check_js						; check the joystick again
left
	LDR r6,=0x17					; check to see if the joystick is pressed left
	CMP r5,r6						
	BNE f_left						; jump to f_left if not
   	LDR r1,=1520 					; prepare to stop the left wheel
	LDR r2,=1610					; prepare to move the right wheel forwards at full speed
	BL pwm_update					; turn the car left
	B check_js						; check the joystick again
f_left
	LDR r6,=0x15					; check to see if the joystick is pressed forward-left
	CMP r5,r6						
	BNE f_right						; jump to f_right if not
   	LDR r1,=1460 					; prepare to move the left wheel at a lesser speed
	LDR r2,=1610					; prepare to move the right wheel forwards at full speed
	BL pwm_update					; turn the car left
	B check_js						; check the joystick again
f_right
	LDR r6,=0x19					; check to see if the joystick is pressed forward-right
	CMP r5,r6						
	BNE b_left						; jump to b_left if not
   	LDR r1,=1380 					; prepare to move the right wheel forwards at full speed 
	LDR r2,=1570					; prepare to move the right wheel forwards at a lesser speed
	BL pwm_update					; turn the car left
	B check_js						; check the joystick again
b_left
	LDR r6,=0x07					; check to see if the joystick is pressed backwards-left
	CMP r5,r6						
	BNE b_right						; jump to b_right if not
   	LDR r1,=1560 					; prepare to move the left wheel backwards at a lesser speed
	LDR r2,=1450					; prepare to move the right wheel backwards at full speed
	BL pwm_update					; turn the car left
	B check_js						; check the joystick again
b_right
	LDR r6,=0x05					; check to see if the joystick is pressed backwards-right
	CMP r5,r6						
	BNE off							; jump to off if not
   	LDR r1,=1630 					; prepare to move the left wheel backwards at full speed
	LDR r2,=1480					; prepare to move the right wheel backwards at a lesser speed
	BL pwm_update					; turn the car left
	B check_js						; check the joystick again
	

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

; User data area definition follows

                AREA  appdata, DATA, NOINIT, READWRITE

                END
