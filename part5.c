//PART5




#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h> 

//Declare variables
FILE* file; 
FILE* fileST; 
char end[17]; 
char command[5][13]; 
char symbolslabel[50][10];
char memrylocs[50][10];
long programCounter; 
char startValue[5]; 

//Main method

int main (int argc, char* argv[]) { 
     
    //adding the operands into an array 
    strcpy(command[0], "and"); 
    strcpy(command[1], "add"); 
    strcpy(command[2], "jmp"); 
    strcpy(command[3], "ld" ); 
    strcpy(command[4], "br" ); 
     
    //set the program counter, DEC
    programCounter = strtol(argv[3], NULL, 16); 
    
    //open out files 
    file = fopen(argv[1], "r"); 
    
	
    if(argc == 4){ 
        fileST = fopen(argv[2], "r");
	}
     
    //This checks if the files have been created 
    if(file == NULL) { 
        printf("Error couldn't find file"); 
        return 1; 
    } 
     
    if(fileST == NULL){ 
        printf("Error couldn't open/find the symbol table file");
		return 1;
    } 
    char words[15], labels[5], values[5];
	int symbolsToLoop;
	short j;
	for(j = 0; j < 50; j++){
		if(!feof(fileST)){
			fgets(words, 15, fileST);
			sscanf(words, "%s %s", labels, values);
			strcpy(symbolslabel[j], labels);
			strcpy(memrylocs[j], values);
			symbolsToLoop++;
		}
	}
	 

    char line[14], addrs[9], label[5];
    char op[2], desR[2], secondR[3], lastR[2], brOperand[5], brLabel[7]; 
    char ldLabel[5];
	int value; 
    long offsetForLDs, result; 
	   
//Convert  
    while(fgets(line, 14, file) && line[14] != EOF){ 
         
        if(line[0] == 'l' && line[1] == 'd'){ 
			programCounter++; 
            strcpy(end, "0010"); 
            line[2] = ','; 
            sscanf(line, "%[^','], %[^','], %[^',']", op, desR, ldLabel); 
            desR[0] = '0'; 
			
		
			short m;
			for(m = 0; m < symbolsToLoop; m++){
				if((strcmp(ldLabel, symbolslabel[m]) - 13) == 0){
					strcpy(label, symbolslabel[m]);
					strcpy(addrs, memrylocs[m]);
				}
			}

			offsetForLDs = strtol(addrs, NULL, 16); 
            result = offsetForLDs - programCounter; 
		/* Grab the last 9 bits of the variable result */
            short i; 
            addrs[9] = 0; 
            for( i = 8; i >= 0; i--){ 
				if( (1 << i ) & result){ 
					addrs[8-i] = '1'; 
                }else{ 
                    addrs[8-i] = '0'; 
                } 
            }
		}
        
		
        if(line[0] == 'b' && line[1] == 'r'){
			programCounter++;
            strcpy(end, "0000"); 
			sscanf(line, "%s %s", brOperand, brLabel); 
			
		
			if((line[2] == 'n') && (line[3] == 'z') && (line[4] == 'p')){strcat(end, "111");}
			else if((line[2] == 'n') && (line[3] == 'z')){strcat(end, "110");}
			else if((line[2] == 'n') && (line[3] == 'p')){strcat(end, "101");}
			else if((line[2] == 'z') && (line[3] == 'p')){strcat(end, "011");}
			else if(line[2] == 'n'){strcat(end, "100");}
			else if(line[2] == 'z'){strcat(end, "010");} 
			else if(line[2] == 'p'){strcat(end, "001");} 
			else if(line[2] == ' '){strcat(end, "000");line[2] = ',';}
	
		
			short k;
			for(k = 0; k < symbolsToLoop; k++){
				if(strcmp(brLabel, symbolslabel[k]) == 0){
					strcpy(label, symbolslabel[k]);
					strcpy(addrs, memrylocs[k]);
				}
			}
			offsetForLDs = strtol(addrs, NULL, 16); 
            result = offsetForLDs - programCounter;

		/* Grab the last 9 bits of the variable result */
            short i; 
            addrs[9] = 0; 
            for( i = 8; i >= 0; i--){ 
				if( (1 << i ) & result){ 
					addrs[8-i] = '1'; 
                }else{ 
					addrs[8-i] = '0'; 
                } 
            }
			strcat(end, addrs);
			printf("0"); 
			goto SKIP;
		}
	
		
		if(line[0] == 'j'){ 
			programCounter++; 
            strcpy(end, "1100"); 
            line[3] = ','; 
            sscanf(line, "%[^','], %[^',']", op, secondR); 
            desR[0] = '0'; 
            secondR[0] = '0'; 
        }
		/* End of JMP */ 
     
        if(line[0] == 'a'){ 
			programCounter++; 
            line[3] = ','; 
            sscanf(line, "%[^','], %[^','], %[^','], %[^',']", op, desR, secondR, lastR); 
            desR[0] = '0'; 
            secondR[0] ='0';
			
			if(strcmp(op, command[0]) == 0) { //AND 
				strcpy(end, "0101"); 
			} 
			if(strcmp(op, command[1]) == 0) { //ADD 
				strcpy(end, "0001"); 
			} 
        } 
        /* End of ADD/AND */
             
		
        switch(atoi(desR)){ 
            case 1 : strcat(end, "001");break; /* */ case 2 : strcat(end, "010");break; 
            case 3 : strcat(end, "011");break; /* */ case 4 : strcat(end, "100");break;  
            case 5 : strcat(end, "101");break; /* */ case 6 : strcat(end, "110");break; 
            case 7 : strcat(end, "111");break; /* */ case 0 : strcat(end, "000");break; 
        } 
        if(strcmp(op, command[3]) == 0){ 
			strcat(end, addrs);             
            goto SKIP; 
        } 
       
        switch(atoi(secondR)){ 
            case 1 : strcat(end, "001");break; /* */ case 2 : strcat(end, "010");break; 
            case 3 : strcat(end, "011");break; /* */ case 4 : strcat(end, "100");break; 
            case 5 : strcat(end, "101");break; /* */ case 6 : strcat(end, "110");break;   
            case 7 : strcat(end, "111");break; /* */ case 0 : strcat(end, "000");break; 
        } 
         
        if(line[0] == 'j'){ 
            goto LASTR; 
        } 
		
		if(lastR[0] != 'r'){  
            value = atoi(lastR); 
            goto IMMD; 
         
        }else if(lastR[0] == 'r'){ 
            lastR[0] ='0'; 
            goto LASTR; 
        } 
         
LASTR:    switch(atoi(lastR)){ 
            case 1 : strcat(end, "000001");goto SKIP; /* */ case 2 : strcat(end, "000010");goto SKIP; 
            case 3 : strcat(end, "000011");goto SKIP; /* */ case 4 : strcat(end, "000100");goto SKIP; 
            case 5 : strcat(end, "000101");goto SKIP; /* */ case 6 : strcat(end, "000110");goto SKIP; 
            case 7 : strcat(end, "000111");goto SKIP; /* */ case 0 : strcat(end, "000000");goto SKIP; 
							
			 
        } 
        
IMMD: 		switch(value){ 
				
            case  0 : strcat(end, "100000");break; /* */ case -1 : strcat(end, "111111");break; 
            case -2 : strcat(end, "111110");break; /* */ case -3 : strcat(end, "111101");break;  
            case -4 : strcat(end, "111100");break; /* */ case -5 : strcat(end, "111011");break; 
            case -6 : strcat(end, "111010");break; /* */ case -7 : strcat(end, "111001");break; 
            case -8 : strcat(end, "111000");break; /* */ case -9 : strcat(end, "110111");break; 
            case -10: strcat(end, "110110");break; /* */ case -11: strcat(end, "110101");break; 
            case -12: strcat(end, "110100");break; /* */ case -13: strcat(end, "110011");break; 
            case -14: strcat(end, "110010");break; /* */ case -15: strcat(end, "110001");break; 
            case -16: strcat(end, "110000");break; /* */ case 1  : strcat(end, "100001");break; 
            case 2  : strcat(end, "100010");break; /* */ case 3  : strcat(end, "100011");break; 
            case 4  : strcat(end, "100100");break; /* */ case 5  : strcat(end, "100101");break; 
            case 6  : strcat(end, "100110");break; /* */ case 7  : strcat(end, "100111");break; 
            case 8  : strcat(end, "101000");break; /* */ case 9  : strcat(end, "101001");break; 
            case 10 : strcat(end, "101010");break; /* */ case 11 : strcat(end, "101011");break; 
            case 12 : strcat(end, "101100");break; /* */ case 13 : strcat(end, "101101");break; 
            case 14 : strcat(end, "101110");break; /* */ case 15 : strcat(end, "101111");break; 
        } 
SKIP:       
        if(strlen(end) == 16){ 
			printf("%x\n", strtol(end, NULL, 2)); 
        } 

        memset(end, 0, sizeof(end)); /* */ memset(op, 0, sizeof(op));
		memset(lastR, 0, sizeof(lastR)); /* */ memset(desR, 0, sizeof(desR));
        memset(addrs, 0, sizeof(addrs)); /* */ memset(brOperand, 0, sizeof(brOperand));
        memset(label, 0, sizeof(label)); /* */ memset(brLabel, 0, sizeof(brLabel)); 
    } 
	
	//close files
     
    fclose(file);
	fclose(fileST);
    return 0; 
}
