//PART1


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


FILE* file;     //Creating file 
char end[17];
char command[2][13];

//Main method 

int main (int argc, char* argv[]) {
	//adding the operands into array
	strcpy(command[0], "and");
	strcpy(command[1], "add");
	
	// open files created 
	file = fopen(argv[1], "r");

	
	if(file == NULL) {
		printf("Error couldn't find file");
		return 1;
	}

	// create an array that will hold the line
	char line[13];
	char op[2], desR[2], secondR[2], lastR[2];

	while(fgets(line, 13, file) && line[13] != EOF) {
		
		line[3] = ','; 
		
		
		sscanf(line, "%[^','], %[^','], %[^','], %[^',']", op, desR, secondR, lastR);
		
		desR[0] = '0'; 
		secondR[0] ='0';
		lastR[0] ='0';
		
		
		//AND , ADD statements
		if(strcmp(op, command[0]) == 0) { //AND
			strcpy(end, "0101");
		}

		if(strcmp(op, command[1]) == 0) { //ADD
			strcpy(end, "0001");
		}

		switch(atoi(desR)){
			case 1 : strcat(end, "001"); break;
			case 2 : strcat(end, "010"); break;
			case 3 : strcat(end, "011"); break;
			case 4 : strcat(end, "100"); break;
			case 5 : strcat(end, "101"); break;
			case 6 : strcat(end, "110"); break;
			case 7 : strcat(end, "111"); break;
			case 0 : strcat(end, "000"); break;
		}

		switch(atoi(secondR)){
			case 1 : strcat(end, "001"); break;
			case 2 : strcat(end, "010"); break;
			case 3 : strcat(end, "011"); break;
			case 4 : strcat(end, "100"); break;
			case 5 : strcat(end, "101"); break;
			case 6 : strcat(end, "110"); break;
			case 7 : strcat(end, "111"); break;
			case 0 : strcat(end, "000"); break;
		}

		switch(atoi(lastR)){ 
			case 1 : strcat(end, "000001"); break;
			case 2 : strcat(end, "000010"); break;
			case 3 : strcat(end, "000011"); break;
			case 4 : strcat(end, "000100"); break;
			case 5 : strcat(end, "000101"); break;
			case 6 : strcat(end, "000110"); break;
			case 7 : strcat(end, "000111"); break;
			case 0 : strcat(end, "000000"); break;
		}
			
			
		//prevent 0's from printing in file
		
		if(strlen(end) == 16){ 
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

