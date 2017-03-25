//PART4

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


FILE* file;
FILE* fileST;
char end[17];
char command[4][13];
long programCounter;
char startValue[5];

//Main method

int main (int argc, char* argv[]) {
	
	//adding the operands into an array
	strcpy(command[0], "and");
	strcpy(command[1], "add");
	strcpy(command[2], "jmp");
	strcpy(command[3], "ld" );
	
	// set the program counter, DEC, of course
	programCounter = strtol(argv[3], NULL, 16);
	
	
	// open files
	file = fopen(argv[1], "r");
	
	if(argc == 4){
		fileST = fopen(argv[2], "r");
	}
	
	//This checks if the files have been created 
	if(file == NULL) {
		printf("Error couldn't find file");
		return 1;
	}
	if(!fileST){
		printf("Error couldn't find file");
		return 1;
	}

	
	char line[14], otherLine[8], addrs[9], label[3];
	char op[2], desR[2], secondR[3], lastR[2];
	int value;
	long offsetForLDs, result;
	
//Convert
	while(fgets(line, 14, file) && line[14] != EOF){
			
		if(line[0] == 'j'){ //scans the jmp command and splits operands
			programCounter++;
			strcpy(end, "1100");
			line[3] = ','; 
			sscanf(line, "%[^','], %[^',']", op, secondR);
			desR[0] = '0';
			secondR[0] = '0';
			goto CC; 
		}
		
		if(line[0] == 'l' && line[1] == 'd'){ 
			programCounter++;
			strcpy(end, "0010");
			line[2] = ',';
			sscanf(line, "%[^','], %[^','], %[^',']", op, desR, secondR);
			desR[0] = '0';
						
			
			if(fgets(otherLine, 9, fileST) && otherLine[9] != EOF){
				sscanf(otherLine, "%s %s", label, addrs);
				offsetForLDs = strtol(addrs, NULL, 16);
				result = offsetForLDs - programCounter;
				
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
		}
	
		
		if(line[0] == 'a'){ //scans and/add command, splits operands
			programCounter++;
			line[3] = ','; 
			sscanf(line, "%[^','], %[^','], %[^','], %[^',']", op, desR, secondR, lastR);
			desR[0] = '0'; 
			secondR[0] ='0';
		}
	
		
CC:		
		//ADD,AND statements
		if(strcmp(op, command[0]) == 0) { //AND
			strcpy(end, "0101");
		}

		if(strcmp(op, command[1]) == 0) { //ADD
			strcpy(end, "0001");
		}


		switch(atoi(desR)){
			case 1 : strcat(end, "001");break; case 2 : strcat(end, "010");break;
			case 3 : strcat(end, "011");break; case 4 : strcat(end, "100");break; 
			case 5 : strcat(end, "101");break; case 6 : strcat(end, "110");break;
			case 7 : strcat(end, "111");break; case 0 : strcat(end, "000");break;
		}
		if(strcmp(op, command[3]) == 0){
			strcat(end, addrs);
			goto SKIP;
		}
		
		switch(atoi(secondR)){
			case 1 : strcat(end, "001");break; case 2 : strcat(end, "010");break;
			case 3 : strcat(end, "011");break; case 4 : strcat(end, "100");break;
			case 5 : strcat(end, "101");break; case 6 : strcat(end, "110");break;  
			case 7 : strcat(end, "111");break; case 0 : strcat(end, "000");break;
		}
		
		if(line[0] == 'j'){ 
			goto LASTR;
		}
		
		if(lastR[0] != 'r'){ 
			value = atoi(lastR); 
			goto FINISH; //jumps to FINISH only if the immediate value is correct
		
		}else if(lastR[0] == 'r'){
			lastR[0] ='0';
			goto LASTR; //else go to LAST
		}
		
LASTR:	switch(atoi(lastR)){ 
			case 1 : strcat(end, "000001");goto SKIP; case 2 : strcat(end, "000010");goto SKIP;
			case 3 : strcat(end, "000011");goto SKIP; case 4 : strcat(end, "000100");goto SKIP;
			case 5 : strcat(end, "000101");goto SKIP; case 6 : strcat(end, "000110");goto SKIP;
			case 7 : strcat(end, "000111");goto SKIP; case 0 : strcat(end, "000000");goto SKIP;
			
		}
		
FINISH: switch(value){ 
			
			case  0 : strcat(end, "100000");break; case -1 : strcat(end, "111111");break;
			case -2 : strcat(end, "111110");break; case -3 : strcat(end, "111101");break; 
			case -4 : strcat(end, "111100");break; case -5 : strcat(end, "111011");break;
			case -6 : strcat(end, "111010");break; case -7 : strcat(end, "111001");break;
			case -8 : strcat(end, "111000");break; case -9 : strcat(end, "110111");break;
			case -10: strcat(end, "110110");break; case -11: strcat(end, "110101");break;
			case -12: strcat(end, "110100");break; case -13: strcat(end, "110011");break;
			case -14: strcat(end, "110010");break; case -15: strcat(end, "110001");break;
			case -16: strcat(end, "110000");break; case 1  : strcat(end, "100001");break;
			case 2  : strcat(end, "100010");break; case 3  : strcat(end, "100011");break;
			case 4  : strcat(end, "100100");break; case 5  : strcat(end, "100101");break;
			case 6  : strcat(end, "100110");break; case 7  : strcat(end, "100111");break;
			case 8  : strcat(end, "101000");break; case 9  : strcat(end, "101001");break;
			case 10 : strcat(end, "101010");break; case 11 : strcat(end, "101011");break;
			case 12 : strcat(end, "101100");break; case 13 : strcat(end, "101101");break;
			case 14 : strcat(end, "101110");break; case 15 : strcat(end, "101111");break;
			
		}

		
		
SKIP:		
		if(strlen(end) == 16){ //prevent 0's from printing in file
			printf("%x\n", strtol(end, NULL, 2));
		}
		memset(end, 0, sizeof(end));
		memset(op, 0, sizeof(op));
		memset(desR, 0, sizeof(desR));
		memset(secondR, 0, sizeof(secondR));
		memset(lastR, 0, sizeof(lastR));
		memset(addrs, 0, sizeof(addrs));
	}


	//close files
	fclose(file);
	fclose(fileST);
	
	return 0;
	}
