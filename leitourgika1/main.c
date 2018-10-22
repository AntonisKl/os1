#include <stdio.h>
#include <stdlib.h>
#include "graph.c"
#include <string.h>
#include <stdbool.h>

void errCatch(char* errmsg){
	printf("Error: %s\n", errmsg);
}

void menuOpts(){
	printf("\nWrite the letter not in parentheses:\n"
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

int checkUserInput(char **tokens, graphP mygraph){
	int count = 0;
	while( tokens[count] != NULL )
		count++;
	if(  !strcmp(tokens[0], "i") ){
		if(!strcmp(tokens[1], "\0"))
			errCatch("Wrong Number of Arguments.");
		else
			createNode(mygraph, tokens[1]);
		return 0;
		// printf("%s\n",mygraph->)
	}
	else if( !strcmp(tokens[0], "n") ){
		if(count == 4)
			addEdge(mygraph, tokens[1], tokens[2], atoi(tokens[3]));
		else
			err_exit("Wrong number of Arguments.");
		return 0;
	}
	else if( !strcmp(tokens[0], "d") ){
		if(count == 2)
			deleteNode(mygraph, tokens[1]);
		else
			err_exit("Wrong number of Arguments.");
		return 0;
	}
	else if( !strcmp(tokens[0], "l") ){
		if(count == 4)
			deleteEdge(mygraph, tokens[1], tokens[2], atoi(tokens[3]));
		else
			err_exit("Wrong number of Arguments.");
		return 0;
	}
	else if( !strcmp(tokens[0], "m") ){
		if(count == 5)
			modifyWeight(mygraph, tokens[1], tokens[2], atoi(tokens[3]), atoi(tokens[4]));
		else
			err_exit("Wrong number of Arguments.");
		return 0;
	}
	else if( !strcmp(tokens[0], "r") ){
		if(count == 2)
			showTransactions(mygraph, tokens[1]);
		else
			err_exit("Wrong number of Arguments.");
		return 0;
	}
	else if( !strcmp(tokens[0], "c") ){
		if(count == 2)
			circleFind(mygraph, tokens[1]);
		else
			err_exit("Wrong number of Arguments.");
		return 0;
	}
	else if( !strcmp(tokens[0], "f") ){
		printf("Input is f\n");
	}
	else if( !strcmp(tokens[0], "t") ){
		printf("Input is t\n");
	}
	else if( !strcmp(tokens[0], "e") )
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
	//displayGraph(myGraph);
	/* Checking for Command Line Arguments */
    if(argc == 1)
        fptr = NULL;
    else if( argc == 3 && !!strcmp(argv[1], "-i"))
    	fptr = fopen(argv[2], "r");
    else if( argc == 3 && !!strcmp(argv[1], "-o"))
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
    	token[i] = strtok(userOpt, " \n");
		//Check this assignment tomorrow
    	while( token[i] != NULL){
    		i++;
			token[i] = strtok(NULL, " \n");
		}
    	if(checkUserInput(token, myGraph) == 1)
    		exit = false;
		displayGraph(myGraph);
    }

}