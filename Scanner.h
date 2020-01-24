/**
 * @file Scanner.h
 * @brief Defines the class used for Scanning tokens
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

class Scanner {
public:
        Scanner(const char *fname);
        ~Scanner();

        char* removeWhitespace(int &len);

private:
        FILE *fp;
                             
        // Will probably have an std::vector<Token*> to keep an array of all Tokens?
                
};
