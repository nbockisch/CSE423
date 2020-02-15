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


int main(int argc, char **argv) {
	int opt;
	char *file;

	/*break apart command line arguments*/
	while((opt = getopt(argc, argv, ":if:lrx")) != -1) {  
		switch(opt)  { 
			/*boiler plate: change letters to whatever you want as needed*/ 
			case 'i':  
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
 
        delete scanner;
}
