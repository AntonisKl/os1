#include <stdio.h>
#include <stdlib.h>
#include "graph.c"
#include <string.h>
#include <stdbool.h>

void errCatch(char* errmsg){
	printf("Error: %s\n", errmsg);
}

void menuOpts(){
	printf("\nWrite the letter not in parentheses or the full word:\n"
		   "1. i(nsert) new Node ni\n"
		   "2. (i)n(sert) new Node Weight ni nj\n"
		   "3. d(elete) Node ni\n"
		   "4. (de)l(ete) Node Weight ni nj\n"
		   "5. m(odify) ni nj oldWeight newWeight\n"
		   "6. r(eceiving) Transactions of Node ni\n"
		   "7. c(irclefind) Node ni - for simple circles\n"
		   "8. f(indcircles) ni k - find circles of Node ni with minimum weight k\n"
		   "9. t(raceflow) ni nj l - find flows from Node ni to Node nj with maximum path distance l\n"
		   "10. e(xit) - Free allocated memory and exit program\n");
}

int checkUserInput(char **tokens){
	if( strcmp(tokens[0], "i") || strcmp(tokens[0], "insert")){

	}
	else if( strcmp(tokens[0], "n") || strcmp(tokens[0], "insert")){
		
	}
	else if( strcmp(tokens[0], "d") || strcmp(tokens[0], "delete")){
		
	}
	else if( strcmp(tokens[0], "l") || strcmp(tokens[0], "delete")){
		
	}
	else if( strcmp(tokens[0], "m") || strcmp(tokens[0], "modify")){
		
	}
	else if( strcmp(tokens[0], "r") || strcmp(tokens[0], "receiving")){
		
	}
	else if( strcmp(tokens[0], "c") || strcmp(tokens[0], "circlefind")){
		
	}
	else if( strcmp(tokens[0], "f") || strcmp(tokens[0], "findcircles")){
		
	}
	else if( strcmp(tokens[0], "t") || strcmp(tokens[0], "traceflow")){
		
	}
	else if( strcmp(tokens[0], "e") || strcmp(tokens[0], "exit"))
		return 1;
	else{
		errCatch("Invalid command");
		return 0;
	}

}

int main(int argc, char *argv[]){

	FILE *fptr;
	int i;

	graphP myGraph = createGraph();

	/* Checking for Command Line Arguments */
    if(argc == 1)
        fptr = NULL;
    else if( argc == 3 && !strcmp(argv[1], "-i"))
    	fptr = fopen(argv[2], "r");
    else if( argc == 3 && !strcmp(argv[1], "-o"))
    	fptr = fopen(argv[2], "w+");
    else if( argc == 5 ){
    	fptr = fopen(argv[2], "r");
    	fptr = fopen(argv[4], "w+");
    }
    else
    	errCatch("Wrong number/format of arguments.");

    bool exit = true;
    //userOpt stores the user's option in each loop iteration
    char* userOpt = malloc(100 * sizeof(char));
    //token is an array of strings that contains the user's input tokenized by whitespace
    char** token = malloc(5 * sizeof(char*));
    for (i = 0; i < 5; ++i){
    	token[i] = malloc(10 * sizeof(char));
    }

    while(exit){
    	menuOpts();
		fgets(userOpt, 50, stdin);
    	//scanf("opt", &userOpt);
    	i = 0;
		printf("\ncheck\n");
    	token[i] = strtok(userOpt, " ");
		printf("\n %s \n", token[0]);
		printf("\ncheck\n");
		//Check this assignment tomorrow
    	while( (token[i] = strtok(NULL, " ")) != NULL)
    		i++;
		printf("\n %s \n", token[0]);
    	if(checkUserInput(token) == 1)
    		exit = false;
    }

}