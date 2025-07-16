.data
space: .asciiz " "    # Space character for printing between numbers
newline: .asciiz "\n" # Newline character
extra_newline: .asciiz "\n\n" # Extra newline at end

#For debugging
#board: .byte 1,2,3,4,5,6
#board_width: .word 3
#board_height: .word 2

#board_height: .word 10          # Height of the board
#board_width:  .word 10          # Width of the board
#board:       .byte  0:100       # A 10x10 board initialized to all 0s
#piece: .word 2, 1, 3, 3  # Type = line, Orientation = vertical, Row = 3, Col = 3


.text
.globl zeroOut 
.globl place_tile 
.globl printBoard 
.globl placePieceOnBoard 
.globl test_fit 
#.globl main

#main:

    #debugging
    #li $a0, 65
    #li $v0, 11 #Print A
    #syscall

    #jal printBoard #Call printBoard function
    #jal zeroOut #Call zeroOut function 
    #jal printBoard #Call printBoard function
    #li $v0, 10 #Exit
   # syscall
   
   
   


#--------------------------------------------------------------------------------------

# Function: zeroOut
# Arguments: None
# Returns: void
zeroOut:
    # Function prologue

    addi $sp, $sp, -8 #Create stack space
    sw $ra, 4($sp) #Save return addresss
    sw $s0, 0($sp) #int row_start_index = 0

    lw $t0, board_height #t0 = board_height
    lw $t1, board_width #t1 = board_width
    li $t2, 0 #int row_index=0
    la $t3, board #t3 = &board
 
    outer_loop:
        bge $t2, $t0, zero_done #Exit loop if row_index>=board_height
        mul $s0, $t1, $t2 #start_row_index = row_index * board_width
        li $t4, 0 #col_index=0

    inner_loop: #Loops through columns
        bge $t4, $t1, next_row #Exit loop if col_index>=board_width
        add $t5, $s0, $t4 #start_col_index = start_row_index + col_index
        add $t6, $t3, $t5 #&board + start_col_index

        #Set value to 0
        li $t7, 0 #t7 = 0
        sb $t7, 0($t6) #Store value 0 into current address

        addi $t4, $t4, 1 #col_index++;
        j inner_loop #Jump back to inner loop

    next_row:
        addi $t2, $t2, 1 #row_index++
        j outer_loop #Jump back to the outer loop

    zero_done:
        # Function epilogue
        lw $ra, 4($sp) #Get return address from the stack
        lw $s0, 0 ($sp) #Restore $s0
        addi $sp, $sp, 8 #Moving stack pointer back to deallocate stack space
        jr $ra #Return

#--------------------------------------------------------------------------------------

# Function: placePieceOnBoard
# Arguments: 
#   $a0 - address of piece struct
#   $a1 - ship_num
placePieceOnBoard:
    # Function prologue
    addi $sp $sp, -4 #Space for return addres
    sw $ra, 0($sp) 
   
    #Get data from struct
    lw $s3, 0($a0) #type
    lw $s4, 4($a0) #orientation
    lw $s5, 8($a0) #row_loc
    lw $s6, 12($a0) #col_loc
    move $s1, $a1 #Ship ID
    li $s2, 0 #counter for errors
    #lw $s1, $a1 #Ship num
   
    li $t0, 1
    li $t1, 7
    li $t2, 4
    li $t7, 0
    lw $t4, board_width
    #li $t4, 0($t4)
    
    lw $t5, board_height
    #li $t5, 0($t5)
    
   
   	
    blt $s3, $t0, out_of_bounds1 #piece_type<1, go to out_of_bounds1
    bgt $s3, $t1, out_of_bounds1 #piece_type>7, go to out_of_bounds1
      
    blt $s4, $t0, out_of_bounds1 #piece_rotation<1, go to out_of_bounds1
    bgt $s4, $t2, out_of_bounds1 #piece_rotation>4, go to out_of_bounds1
 

    blt $s5, $t7, out_of_bounds1 #row<0, go to out_of_bounds1
    bge $s5, $t5, out_of_bounds1 #row>height, go to out_of_bounds1
    
    blt $s6, $t7, out_of_bounds1 #col<0, go to out_of_bounds1
    bge $s6, $t4, out_of_bounds1 #col>width, go to out_of_bounds1

    # Load piece fields
    # First switch on type
    li $t0, 1
    beq $s3, $t0, piece_square
    li $t0, 2
    beq $s3, $t0, piece_line
    li $t0, 3
    beq $s3, $t0, piece_reverse_z
    li $t0, 4
    beq $s3, $t0, piece_L
    li $t0, 5
    beq $s3, $t0, piece_z
    li $t0, 6
    beq $s3, $t0, piece_reverse_L
    li $t0, 7
    beq $s3, $t0, piece_T
    #j out_of_bounds1
     
    
out_of_bounds1:
    ori $s2, $s2, 2 #counter for errors = 2
    j errors
    
    #debugging A stands for out of bounds
    #li $a0, 65
    #li $v0, 11 #Print A
    #syscall
errors:
	
    #debugging B stands for errors
    #li $a0, 66
    #li $v0, 11 #Print B
    #syscall
    bnez $s2, goto_zeroOut #if counter for errors is not zero, go to goto_zeroOut
    #li $s2, 0
    li $v0, 0 #Load 0 to return variable
    j piece_done
    
goto_zeroOut:
     # Debugging: Before zeroOut
    #li $a0, 90          # ASCII 'Z'
    #li $v0, 11          # Print 'Z'
    #syscall
    
    jal zeroOut

    # Debugging: After zeroOut
    #li $a0, 79          # ASCII 'O'
    #li $v0, 11          # Print 'O'
    #syscall

    move $v0, $s2
    #li $s2, 0 #Reset error counter
    #andi $t1, $s2, 1 #Check cell occupied error
    #andi $t2, $s2, 2 #Check out of bounds error
    #or $v0, $t1, $t2 #Combine errors
    
 
    lw $ra, 0($sp) #restore ra from stack
    addi $sp, $sp, 4 #deallocate stack space
    jr $ra #return
    

piece_done:
	#debugging
    #li $a0, 65
    #li $v0, 11 #Print A
    #syscall
   
    li $v0, 0
    move $v0, $s2
    bnez $v0, goto_zeroOut
    lw $ra, 0($sp) #restore ra from stack
    addi $sp, $sp, 4 #deallocate stack space
    jr $ra #return
    

#-------------------------------------------------------------------------------

# Function: printBoard
# Arguments: None (uses global variables)
# Returns: void
# Uses global variables: board (char[]), board_width (int), board_height (int)



printBoard:
    
    #debugging
    #li $a0, 66
    #li $v0, 11 #Print B
    #syscall

    # Function prologue
    addi $sp, $sp, -8 #Create stack space
    sw $ra, 4($sp) #saves return address
    sw $s0, 0($sp) #int start_row_index = 0

    lw $t0, board_height #t0 = board_height
    lw $t1, board_width #t1 = board_width
    li $t2, 0 #int row_index=0
    la $t3, board #t3 = &board

    outer_loop1: #Loops through rows

        #debugging
        #li $a0, 67
        #li $v0, 11 #Print C
        #syscall

        bge $t2, $t0, exit_loop1 #Exit loop if row_index>=board_height
        mul $s0, $t1, $t2 #start_row_index = row_index * board_width

        li $t4, 0 #int col_index = 0

    inner_loop1: #Loops through columns

        #debugging
        #li $a0, 68
        #li $v0, 11 #Print D
        #syscall

        bge $t4, $t1, next_row1 #Exit loop if col_index>=board_width
        add $t5, $s0, $t4 #start_col_index = start_row_index + col_index
        add $t6, $t3, $t5 #&board + start_col_index
        lb $a0, 0($t6) #Load element at the index of the board into argument register
        addi $a0, $a0, 48
        li $v0, 11 #Print char at the index 
        syscall

        la $t7, space #Load space into a variable
        lb  $a0, 0($t7) #Load it into argument
        li $v0, 11 #Print the space
        syscall

        addi $t4, $t4, 1 #col_index++
        j inner_loop1 #Jump back to inner loop

    next_row1: #Move to next row

        la $t7, newline #Load a new line into argument
        lb $a0, 0($t7) #Load it into argument
        li $v0, 11 #Print the new line
        syscall 

        addi $t2, $t2, 1 #row_index++
        j outer_loop1 #Jump back to the outer loop

    
    # Function epilogue

    exit_loop1:
        lw $ra, 4($sp) #Get return address from the stack
        lw $s0, 0 ($sp) #Restore $s0
        addi $sp, $sp, 8 #Moving stack pointer back to deallocate stack space
        jr $ra                # Return


#--------------------------------------------------------------------------------------

# Function: place_tile
# Arguments: 
#   $a0 - row
#   $a1 - col
#   $a2 - value
# Returns:
#   $v0 - 0 if successful, 1 if occupied, 2 if out of bounds
# Uses global variables: board (char[]), board_width (int), board_height (int)

place_tile:
#debugging
    #li $a0, 65
    #li $v0, 11 #Print A
    #syscall
addi $sp, $sp, -4
sw $ra, 0($sp)

la $t0, board_width #Load board width address
lw $t1, 0($t0) #t1 = board_width
la $t2, board_height #Load board height address
lw $t3, 0($t2) #t3 = board_height
la $t5, board #load board address


bltz $a0, out_of_bounds #if row<0, then go to out_of_bounds
bge $a0, $t3, out_of_bounds #if row>board_height, then go to out_of_bounds

bltz $a1, out_of_bounds #if col<0, then go to out_of_bounds
bge $a1, $t1, out_of_bounds #if col>board_width, then go to out_of_bounds

mul $t4,$a0, $t1 #board_index = row * board_width
add $t4, $t4, $a1 #board_index  = (row*board_width) + col

add $t5, $t4, $t5 #value_index = board_address + board_index
lb $t6, 0($t5) #value = element at value_index

#debugging
    #move $a0, $t6
    #li $v0, 1 
    #syscall
li $t7, 0 #t7 = 0
bne $t6, $t7, invalid_location #if value!=0, jump to invalid_location

sb $a2, 0($t5) #board[board_index] = value
li $v0, 0 #return 0
lw $ra, 0($sp)
addi $sp, $sp, 4
jr $ra #return to caller

out_of_bounds:

	#debug
	#li $a0, 66
	
	#li $v0, 11 #Print B
	#syscall
	
	li $v0, 2 #return 2 
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra #return to caller
	
invalid_location:
	
	#Why is it calling invald location???
	#debugging
        #li $a0, 68
        #li $v0, 11 #Print D
        #syscall
	li $v0, 1 #return 1
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra #return to caller
	

   

#--------------------------------------------------------------------------------------


# Function: test_fit
# Arguments: 
#   $a0 - address of piece array (5 pieces)
test_fit:
    # Function prologue
    addi $sp, $sp, -8 #Move stack pointer 
    sw $ra, 4($sp) #Save return address
    sw $s0, 0($sp) #Loop counter
   move $t8, $a0 #Saves the base address
    
    
    li $s0, 0 #Loop counter 
    #li $s6, 5 #Max # of ships
    li $v0, 0 #Initialize return value
    li $t1, 1 
    li $t2, 4 
    li $t3, 7
    li $t9, 4 #Max # of ships (0-4)
    
    #lw $t5, 0($a0)
    
    loop_ships:
     
     	#DEBUGGING
    	#move $t7, $a0
    	
    	
    	 #move $a0, $s0
    	 #li $v0, 1
    	 #syscall
    	 
    	 #move $a0, $t7
    	 
    
   	 bgt $s0, $t9, place_ships #If i>4, exit for loop
   	 
   	 #Each ship piece is 16 bytes
   	 sll $t4, $s0, 4 #Offset
   	 add $t5, $t8, $t4 #Get address of current ship
   	 
   	 
   	 
   	 #move $a0, $t5
   	 #li $v0, 1
   	 #syscall
   	 
   	 lw $t6, 0($t5) #t6 = piece_type
   	 lw $t7, 4($t5) #t6 = piece_rotation
   	 #lw $t8, 8($t5) #t6 = row
   	 #lw $t9, 12($t5) #t6 = col
   	
         #debugging
        #move $t8, $a0
    	
    	 #move $a0, $t6
    	 #li $v0, 1
    	 #syscall
    	 
    	#move $a0, $t8
  
   	 
   	 #Check piece_type and piece_rotation
   	 blt $t6, $t1, out_of_bounds2 #If the piece_type<1, go to out_of_bounds2
   	 bgt $t6, $t3, out_of_bounds2 #If the piece_type>7, go to out_of_bounds2
   	 blt $t7, $t1, out_of_bounds2 #If the piece_rotation<1, go to out_of_bounds2
   	 bgt $t7, $t2, out_of_bounds2 #If the piece_rotation>4, go to out_of_bounds2
   	 
   	 #Debugging
    	#li $a0, 68
        #li $v0, 11 #Print D
        #syscall
        
         #move $a0, $t8
   	 addi $s0, $s0, 1 #Increment loop counter
   	 j loop_ships #Go back to the beginning of the loop
   	 
   	 
    out_of_bounds2:
    	#Debugging
    	#li $a0, 68
        #li $v0, 11 #Print D
        #syscall
    	li $v0, 4 #Return 4 if invalid piece rotation or type
    	j test_fit_done
    	
    place_ships:
    	li $s0, 0 #Set counter back to 1 for next loop
    	
    	#li $v0, 0 
    	
    place_ships_loop:
    
    	
  	#DEBUGGING
    	#move $t8, $a0
    	
    	
    	 #move $a0, $s0
    	 #li $v0, 1
    	 #syscall
    	 
    	 #move $a0, $t8
    	
    	
    	 
    	bgt $s0, $t9, test_fit_done #exit when s0>4
    	
    	
    	
    	#Each ship piece is 16 bytes
   	sll $t4, $s0, 4 #Offset
   	add $t5, $t8, $t4 #Get address of current ship
   	
   	move $a0,$t5 #Store address of the array in argument 
   	addi $a1, $s0, 1 #Store ship number as ship ID in argument
   	
   	
   	
   	jal placePieceOnBoard
   	#move $a0, $t8
   	 #debugging
   	 #jal printBoard
   	
   	#or $v0, $v0, $v0 #Combine occupy errors and out of bounds errors
   	
   	addi $s0, $s0, 1 #Incremement loop counter
   	j place_ships_loop #Go back to beginning of place_ships_loop
    	
 
   test_fit_done: 
    lw $ra, 4($sp)  #Restore return address
    lw $s0, 0($sp)  #Set loop counter back to 1
    
    addi $sp, $sp, 8 #Deallocate stack space
    jr $ra #Return

#--------------------------------------------------------------------------------------

T_orientation4:
    # Study the other T orientations in skeleton.asm to understand how to write this label/subroutine
    move $a0, $s5  # row
    move $a1, $s6  # col	
    move $a2, $s1  # ship_id
    jal place_tile #Store ship_id at row and col
    or $s2, $s2, $v0  #accumulate error
    
    move $a0, $s5 #row
    addi $a0, $a0, 1 #row+1
    move $a1, $s6 #col
    move $a2, $s1 
    jal place_tile 
    or $s2, $s2, $v0
    
    move $a0, $s5 #row
    addi $a0, $a0, 2 #row+2
    move $a1, $s6 #col
    move $a2, $s1 
    jal place_tile
    or $s2, $s2, $v0
    
    
    move $a0, $s5 #row
    addi $a0, $a0, 1 #row+1
    move $a1, $s6 #col
    addi $a1, $a1, 1 #col+1
    move $a2, $s1 
    jal place_tile 
    or $s2, $s2, $v0
    
  
    j piece_done





.include "skeleton.asm"