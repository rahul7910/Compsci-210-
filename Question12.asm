;Rahul Issar
;riss899
;588382864

		.ORIG x3000 ; Starting address of the program

CLEAR_R0 	AND R0, R0, #0 ; Initialize R0 to 0
 		NOT R3, R2 ; R3 contains the 1's complement value of R2
 		ADD R3, R3, #1 ; R3 contains the 2's complement value of R2
		ADD R4, R1, R3 ; R4 is the result of R1 - R2
		BRz STOP ; Jump to STOP so R0 is still 0, meaning R1 = R2
		BRp GREATER ; Jump to GREATER so R0 is updated to 1
		BRn LESS ; Jump to LESS so R0 is updated to -1

GREATER ADD R0, R0, #1 ; R0 = 1 if R1 > R2
		BRp STOP ; After update, the program should proceed to store result

LESS ADD R0, R0, #-1 ; R0 = -1 if R1 < R2

STOP LD R6, OFFSET ; Load R6 with address x4000
		STR R0, R6, #0 ; Store the result into memory location x4000
		HALT
OFFSET .FILL x3000
 	.END