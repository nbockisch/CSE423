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
	int tree = 0;
	/*break apart command line arguments*/
	while((opt = getopt(argc, argv, ":af:lrx")) != -1) {  
		switch(opt)  { 
			/*boiler plate: change letters to whatever you want as needed*/ 
			case 'a':  
				tree = 1;
				break;
			case 'l':  
			case 'r':  
				printf("option: %c\n", opt);  
				break; 
			/*file input*/ 
			case 'f':  
				file = (char *)malloc((strlen(optarg)+1) * sizeof(char));
				strncpy(file, optarg, strlen(optarg));
				printf("filename: %s\n", file);  
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
	
	AST *ast = new AST();
	char const *order[3] = {"main", "return", "1"};
       	ast->insert(order);
	if (tree == 1) {
		printf("Post order traversal of AST:\n");
		ast->postorder();
	}
        delete ast;
 
        delete scanner;

}
