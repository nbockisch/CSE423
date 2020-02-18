/**
 * @file main.cpp
 * @brief Main driver for compiler
 */

/**
 * @file main.cpp
 * @brief Main driver for compiler
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Scanner.h"
#include <unistd.h>
#include "AST.h"


int main(int argc, char **argv) {
	int opt;
	char *file;
	int size;
	int p_tokens = 0;
	int tree = 0;

	/*break apart command line arguments*/
	while((opt = getopt(argc, argv, ":if:ax")) != -1) {  
		switch(opt)  { 
			/*boiler plate: change letters to whatever you want as needed*/ 
			case 'i':  
				/* print out tokens */
				p_tokens = 1;	
				break;
			case 'a':  
				/*prints out AST*/
				tree = 1;
				break;
			/*file input*/ 
			case 'f':  
				file = (char *)malloc((strlen(optarg)+1) * sizeof(char));
				strncpy(file, optarg, strlen(optarg)); 
				break; 
			/*-f option missing file argument*/ 
			case ':':  
				printf("Include filename after -f\n");  
				break;
			/*unknown commands given*/  
			case '?':  
				printf("unknown option: %c\n", optopt); 
				break;  
		}  
	}  


	Scanner *scanner = new Scanner(file);
	std::vector<token_t> tokens = scanner->tokenize(scanner->readFile(size));

	// Print tokens
	if (p_tokens) {
		scanner->printTokens(tokens);
	}
	/*the parsing is not finished but this piece inserts a basic program into the tree in the way it will after parsing piece finished*/
	AST *ast = new AST();
	char const *order[3] = {"main", "return", "1"};
       	ast->insert(order);
	/*prints tree*/
	if (tree == 1) {
		printf("Tree structure:\n");
		ast->printTree();
	}
        delete ast;
        delete scanner;
}
