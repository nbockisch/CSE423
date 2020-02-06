/**
 * @file Scanner.h
 * @brief Defines the class used for Scanning tokens
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <set>
#include <vector>

// Types of tokens
enum types {
	keyword,
	identifier,
	constant,
	string,
	special,
	op
};

// Data structure for manipulating tokens
struct token_t {
	std::string contents;
	enum types type;
};


class Scanner {
public:
        Scanner(const char *fname);
        ~Scanner();

	std::string readFile(int &len);
	std::vector<token_t> tokenize(std::string code);

private:
        FILE *fp;
                             
        // Will probably have an std::vector<Token*> to keep an array of all Tokens?
                
};
