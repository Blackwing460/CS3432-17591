#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int words = 0;//Stores the number of words in input
char *tokens[1000];//Stores tokens


// Return true (non-zero) if c is a whitespace characer ('\t' or ' ').
bool delim_character(char c){
    switch (c){ //Switch checks for whitespace and empty values
    case ' ':
        return true;
        break;
    case '\t':
        return true;
        break;
    
    case '\0':
        return true;
        break;
    
    default:
        return false;
        break;
    }

}

//Method responsible for copying and storing word as a token
char *copy_str(char *inStr, short len){ 
    char *str; //Stores word
    char *temp = malloc(len*sizeof(short)); // Stores temporary array that makes up the word
    len++;
    for(int i = 0; i<len;i++){ //Populates temp with the chars that make up the word
        temp[i] = inStr[i];  
    }
    str = temp;//Assigns array holding the correct word to str
    tokens[words] = str; //Stores token
 
}


//Method checks input for begining and ending letter of each word
char *word(char* str, int length){
    char *wordstart;
    char *wordend;
    for(int i =0; i<length-1; i++){ //Loops through the entire input
        if(delim_character(str[i]) == false){//Checks if char is not a empty space
            if(i == 0 || delim_character(str[i-1]) == true ){ //Checks for start of word
                wordstart = &str[i];
            }
            if (delim_character(str[i+1]) == true || i == length-2){ //Checks for end of word
                wordend = &str[i];
                copy_str(wordstart, wordend - wordstart); //Finds end of word and send it to be stored
                words++;//Adds 1 to the number of words
            }
        }

    }
   
}


//Prints all tokens
void print_all_tokens(char** token){

    for(int i = 0;i<words;i++){ //Loops for as many words stored
        printf("%s","Token #");
        printf("%d",i);
        printf("%s",": ");
        printf("%s",token[i]);
        printf("%s","\n");

    }
    printf("%s","Total words: ");
    printf("%d",words);
    printf("%s","\n");
    
}

//Directs the code to tokenize
char** tokenize(char* str, int length){ 
   *word(str,length);
    print_all_tokens(tokens);
}

//Collects user input and returns total number of chars
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
    char string[1000];//Max number for chars allowed
    int size = 0; 
    printf("Try it out \n");
    size = userInput(string);//Collects user input as well as size of input
    tokenize(string,size);//Begins the tokenize code
    return 0;
}


