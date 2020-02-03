#include <iostream>
#include <ctype.h>
#include <regex>
#include <string>
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
char* Scanner::removeWhitespace(int &len) 
{

        len = 0;

        int size = 128;
        char * stream = (char*)malloc(sizeof(char)*size);
        assert(stream);
        
        int cur = -1;
        int isString = 0;
        while( (cur = fgetc(fp)) != -1) {
                // NOTE: this wont work if something has an apostrophe in the string..
                //  I will fix this in the future..
                /*if(cur == '"' || cur == 39) {
                        isString = !isString;
                }*/

                // Skip any whitespace only if we are not looking at a user defined string.
                /*if(!isString) {
                        if(isspace(cur)) {
                                continue;
                        }
                }*/

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

std::vector<token_t> Scanner::tokenize(char* code, int len) 
{
	std::string tmp(code);
	int num_tok, j;

	// Comment matching regex from https://stackoverflow.com/questions/16160190/regular-expression-to-find-c-style-block-comments
	// TODO, rewrite to make regex more readible, set token types in struct
	std::regex token_regex("(\\/\\*(\\*(?!\\/)|[^*])*\\*\\/)+|(\\w+)|((\")[^\"]*(\"))|((\')[^\']*(\'))|(==|<=|>=|!=|&&|\\+=|\\-=|\\+\\+|\\-\\-)|[%+\\-/*=^]|[#,<.>{}()[\\]\\|;:]|(\\/\\/(\\s*\\w*)*)");

	// Collect tokens from regex
	auto token_start = std::sregex_iterator(tmp.begin(), tmp.end(), token_regex);
	auto token_stop = std::sregex_iterator();
	num_tok = std::distance(token_start, token_stop);

	std::vector<token_t> tokens;
	//struct token_t *tokens = (struct token_t *)  malloc(sizeof(struct token_t *) * (num_tok + 1));
	j = 0;

	//assert(tokens);

	for (std::sregex_iterator i = token_start; i != token_stop; ++i) {
		std::smatch match = *i;
		token_t tok;
		tok.contents.assign(match.str());
		tokens.push_back(tok);
		//std::string match_tok = match.str();
		//tokens[j].contents.assign(match.str());
		//j++;
		//std::cout << match_tok << '\n';
	}

	return tokens;	
}
