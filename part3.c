//PART3




#include <stdio.h>
#include <string.h>
#include <stdlib.h>



FILE* file; //creating files
char end[17];
char command[3][13];

//Main method 

int main (int argc, char* argv[]) {
	//adding the operands into an array
	strcpy(command[0], "and");
	strcpy(command[1], "add");
	strcpy(command[2], "jmp");
	
	// open files created
	file = fopen(argv[1], "r");

	
	if(file == NULL) {
		printf("Error couldn't find file");
		return 1;
	}

	char op[2], desR[2], secondR[2], lastR[2], line[14];
	int value;
	
//Convert	
	while(fgets(line, 14, file) && line[14] != EOF) {
	
		line[3] = ','; 
		
		if(line[0] == 'j'){
			sscanf(line, "%[^','], %[^',']", op, secondR);
			desR[0] = '0';
			secondR[0] = '0';
			goto CC;
			
		}
		
		sscanf(line, "%[^','], %[^','], %[^','], %[^',']", op, desR, secondR, lastR);
		
		desR[0] = '0'; 
		secondR[0] ='0';
CC:					
		if(strcmp(op, command[0]) == 0) { //AND
			strcpy(end, "0101");
			
		}

		if(strcmp(op, command[1]) == 0) { //ADD
			strcpy(end, "0001");
			
		}
		
		if(strcmp(op, command[2]) == 0){ //JMP
			strcpy(end, "1100");
			
		}

		switch(atoi(desR)){
			case 1 : strcat(end, "001");break; case 2 : strcat(end, "010");break;
			case 3 : strcat(end, "011");break; case 4 : strcat(end, "100");break; 
			case 5 : strcat(end, "101");break; case 6 : strcat(end, "110");break;
			case 7 : strcat(end, "111");break; case 0 : strcat(end, "000");break;
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
	}
	//close files
	fclose(file);
	return 0;
}

