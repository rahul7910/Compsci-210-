;Rahul Issar
;riss899
;588382864
    .ORIG x3000
    ;; Register usage:
; R0 = the input character
; R1 = the newline character
; R2 = base address of the array
; R3 = temporary working storage

PROMPT	.STRINGZ 	"Please enter your name(less than 100 characters long):\n "
; Main program code	
	LEA	R0, PROMPT	; Display the prompt
	PUTS

	LD 	R1, RT	          ; Initialize the return character
	LEA 	R2, ARRAY		; Get the base address of the array
	
	


WHILE	GETC			; Read and echo a character (stored in R0)
	OUT	
	ADD 	R3, R0, R1	; Quit if character = return
	BRz 	ENDWHILE
	STR 	R0, R2, #0	; Store that character in the array
	ADD 	R2, R2, #1	; Increment the address of the array cell
	BR 	WHILE	          ; Return to read another character
	
ENDWHILE	STR 	R3, R2, #0	; Store the null character after the last input

          
	LEA R0, FIRST
	FIRST   .STRINGZ        "Hi "
	PUTS

	LEA 	R0, ARRAY       	; Output the string
        PUTS  
	

	LEA R0, SECOND
	SECOND  .STRINGZ        ", have a good day."
	PUTS
	  HALT

; Main program data

ARRAY	.BLKW 100		          ; Array of 100 characters (including null)
RT	.FILL 	x-000A		; The return character (negated)

	.END
;not printing output 


 
