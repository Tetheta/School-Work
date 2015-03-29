## Programmed by Travis Crumley for ENGR 350 at Walla Walla University, 1/19/2015
## This program implements Booth's algorithm. Since registers are 32 bits in MIPS
## the program can compute multiplication of two 16 bit binary numbers
## The program can handle negative and positive numbers
## However negative numbers only up to -32767 because of the way I read in
## The numbers

# ============= DATA DECLARATIONS =============
        .data
        .align 2
        .space 12
String: .space 16
Input1: .asciiz "\nEnter the multiplier (from -32,767 to 32,767)"
Input2: .asciiz "\nEnter the multiplicand (from -32,767 to 32,767)"
IsNeg:  .asciiz "\nIs the number negative? (1 = yes, 0 = no)"
Output: .asciiz "\n\nThe answer is "

# ============= MAIN FUNCTION =============

        .text
        .globl main

main:
		#Ask for multiplier
        li $2, 4                        # System call code for print string
        la $4, Input1                   # Argument string as Input
        syscall                         # Print the string
		
        li $2, 5                        # System call code to read int input
        syscall                         # Read it
        move $16, $2                    # move the num entered into $16
		
		#Ask if it's negative
		li $2, 4                        # System call code for print string
        la $4, IsNeg                    # Argument string as IsNeg
        syscall                         # Print the string
		
		li $2, 5                        # System call code to read int input
        syscall                         # Read it
        move $24, $2                    # move the num entered into $24
		
		bne $24, $zero, isNeg1			#If it's 1, go make it negative

num2:		
		#Ask for multiplicand
		li $2, 4                        # System call code for print string
        la $4, Input2                   # Argument string as Input
        syscall                         # Print the string
		
		li $2,5                         # System call code to read int input
        syscall                         # Read it
        move $17, $2                    # move the num entered into $17
		
		#Ask if it's negative
		li $2, 4                        # System call code for print string
        la $4, IsNeg                    # Argument string as IsNeg
        syscall                         # Print the string
		
		li $2, 5                        # System call code to read int input
        syscall                         # Read it
        move $24, $2                    # move the num entered into $24
		
		bne $24, $zero, isNeg2			#If it's 1, go make it negative
		j setup							#Number 2 isn't negative, jump to setup
isNeg1:
		sub $16, $zero, $16				#subtract from zero to make it negative
		j num2							#go back to loading the multiplicand
isNeg2:
		sub $17, $zero, $17				#subtract from zero to make it negative
		
		#At this point, 16 is the multiplier, 17 (called B) is the multiplicand
setup:		
		sll $17, $17, 16				#Shift multiplicand by 16 for add/sub later
		andi $16, $16, 0x0000ffff 		#Clear all but the lowest two bytes
		
		li $19,0					    #setup our pad bit
		li $20,16						#setup our counter (going to shift 16 times)
		
		#We've added 19 as the pad bit, and 20 is the counter. 
		#18 is going to be the LSB of our running result
		#16 is our running result, all operations are on it.
loop:
		andi $18, $16, 1				#Get the LSB of our running result
		beq $18, $19, shiftRight		#We're 00 or 11, just shift
		beq $18, $zero, addB			#It's 01, time to add B
		sub $16, $16, $17				#It's 10, subtract B
		j shiftRight					#Done here, jump to shifting
addB:
		add $16, $16, $17				#Add B to our result
shiftRight:
		#I'm assuming sra takes care of sign extension
		sra $16, $16, 1					#immediate right shift one bit
		addi $20, -1					#decrement our counter
		move $19, $18					#move the old LSB to our pad bit now
		bne $20, $zero, loop			#Keep looping if we're not done 
		
		#We're done! Now to display the result
		li $2, 1                        # system call code for print int
        move $4, $16                    # return_value (our result in 16) as argument
        syscall

        #b Exit                          # branch to Exit, we're done! (Commented this for easier use, but no exit)
	b main #Branch back to main to ask for another number now

        .text
        .align 2
Exit:
        li $2, 10                       # System call code for exit
        syscall                         # exit