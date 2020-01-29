/**
 * @file Scanner.h
 * @brief Defines the class used for Scanning tokens
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Types of tokens
#define KEYWORD 0
#define IDENTIFIER 1
#define CONSTANT 2
#define STRING 3
#define SPECIAL 4
#define OPERATOR 5

// Data structure for manipulating tokens
struct token_t {
	char* contents;
	int type;
};

class Scanner {
public:
        Scanner(const char *fname);
        ~Scanner();

        char* removeWhitespace(int &len);
	token_t* tokenize(char* code, int len);

private:
        FILE *fp;
                             
        // Will probably have an std::vector<Token*> to keep an array of all Tokens?
                
};
