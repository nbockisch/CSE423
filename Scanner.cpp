#include <ctype.h>

#include "Scanner.h"

/**
 * Constructor for the Scanner
 */
Scanner::Scanner(const char *fname) {

        this->fp = fopen(fname, "r");
        if (fp == NULL) {
                printf("Error opening file '%s'\n", fname);
                exit(-1);
        }

        
}


/**
 * Deconstructor for Scanner.. free memory here
 */
Scanner::~Scanner() {
        if (fp) {
                fclose(fp);
        }
}


/**
 * Scans the file removing any whitespace characters not within any quotes.
 * Does not handle parsing of comments, which should be done before this as 
 *  this function will strip out newlines, making it hard to parse single line
 *  code comments.
 * @param len The size of stream in bytes.
 * @returns File contents with no whitespace as a character stream
 */
char* Scanner::removeWhitespace(int &len) {

        len = 0;

        int size = 128;
        char * stream = (char*)malloc(sizeof(char)*size);
        assert(stream);
        
        int cur = -1;
        int isString = 0;
        while( (cur = fgetc(fp)) != -1) {
                // NOTE: this wont work if something has an apostrophe in the string..
                //  I will fix this in the future..
                if(cur == '"' || cur == 39) {
                        isString = !isString;
                }

                // Skip any whitespace only if we are not looking at a user defined string.
                if(!isString) {
                        if(isspace(cur)) {
                                continue;
                        }
                }

                // Debugging
                //printf("%c", cur);
                
                if(len > size-1) {
                        size *= 2;
                        stream = (char*)realloc(stream, size);
                        assert(stream);
                }
                
                stream[len] = cur;
                len++;
        }

        stream[len] = '\0';
                
        return stream;
}
