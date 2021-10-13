#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();


/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}


//Is used to store values to the memory
void SaveWord(char* value, char* offset, char* location){
	int32_t num = atoi(&value[1]);//Gets the address of the first value
	int32_t address = atoi(&location[1]);//Gets the address of the address where the new value will be stored
	address = reg[address] + atoi(offset);// New address is stored
	reg[address] =  reg[num]; //register is changed
	char* mem = "mem.txt";
	address = atoi(&reg[address]);
	int32_t write = write_address(num,address,mem);//Is stored in the memory
}

//Is used to load values to the register
void LoadWord(char* location, char* offset, char* value){
	int32_t num = atoi(&value[1]);//Gets the address of the value
	int32_t address = atoi(&location[1]);//gets address of where the value will be loaded
	reg[address] = reg[num + atoi(offset)];//loads teh value into the register

}

//Is used to add values and store them immediately into the memory
void addi(char* location,char* value_1,char* value_2){
	int32_t num1 = atoi(&value_1[1]);//Gets address of the value
	int32_t address = atoi(&location[1]);//Gets address for where value will be stored
	char* mem = "mem.txt";
	reg[address] = reg[num1] + atoi(value_2); //Performs addition and loads it to the register
	int32_t read = read_address(num1,mem);
	read = read + atoi(value_2);// performs add using addresses
	int32_t write = write_address(read,address,mem);//stores in memory
}


//Is used to add values together and loads them in the register
void add(char* location,char* value_1,char* value_2){
	int32_t num1 = atoi(&value_1[1]);//gets address of value 1
	int32_t num2 = atoi(&value_2[1]);//gets address of value 2
	int32_t address = atoi(&location[1]);//gets address where value will be loaded
	reg[address] = reg[num1] + reg[num2];//loads new value to the register

}


//Is responsible for managing risc-v methods
bool interpret(char* instr){
	int i = 0;//used to iterate through tokens
	char *array[4];//stores char* of user input tokenized
	const char delimiters[] = " ()";// inputs to avoid when tokenizing
	while (instr != NULL) {//loop that stores tokens in array for easier access
		array[i] = instr;
        instr = strtok(NULL, delimiters);//tokenizes with delimiters
		i++;
  
    }

	//if statements in charge ofperforming the correct operation based on user input
	if(!strcmp(array[0], "ADD")){
		add(array[1],array[2],array[3]);
	}
	else if (!strcmp(array[0], "ADDI")){
		addi(array[1],array[2],array[3]);
	}
	else if (!strcmp(array[0], "LW")){
		LoadWord(array[1],array[2],array[3]);
	}
	else if (!strcmp(array[0], "SW")){
		SaveWord(array[1],array[2],array[3]);
	}



}

//used to collect user input
int userInput (char s[])
{
    int c, i;

    for (i = 0;(c=getchar())!=EOF && c!='\n'; ++i) //Collects all chars and checks for empty values
	s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int main(){
	char input[50];//used to collect user's string
	int size;//collects string size
	int i = 0;//used to iterate through register when printing
	int e = 0;//value for while loop
	char *token;

	// Do noLt write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	while(e != 1){//loop runs infinetly until EOF is inputted
		printf("Please input desired operation \n");
		size = userInput(input);//collects user input
		token = strtok(input," ");//tokenizes input
		
		interpret(token);
		// loop responisble for printing the register
		while(i<= 31){
			if(i % 2 == 0){//prints even numbers without starting a new line

				printf("X%02i:%.*lld   ",i,10,(long long int) reg[i]);
				//printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
			}
			else{//Odd numbers create new line after printing
				printf("X%02i:%.*lld \n",i,10,(long long int) reg[i]);
			}
			i++;
		}
		i=0;
		printf("\n");
	}	
	return 0;
}