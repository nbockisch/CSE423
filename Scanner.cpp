#include <iostream>
#include <ctype.h>
#include <regex>
#include <string>
#include <set>
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
 * Reads in a C source file and returns its contents as a string
 * @param len The size of stream in bytes.
 * @returns File contents in a string
 */
std::string Scanner::readFile(int &len) 
{

        len = 0;
        int size = 128;
        char * stream = (char*)malloc(sizeof(char)*size);
        assert(stream);
        
        int cur = -1;
        int isString = 0;
        while( (cur = fgetc(fp)) != -1) {
                
                if(len > size-1) {
                        size *= 2;
                        stream = (char*)realloc(stream, size);
                        assert(stream);
                }
                
                stream[len] = cur;
                len++;
        }

        stream[len] = '\0';
	        
        return std::string(stream);
}

/**
 * Splits a string of C code into valid tokens
 * @param code a string with C code
 * @return A vector of token structs with valid tokens
 **/
std::vector<token_t> Scanner::tokenize(std::string code) 
{
	std::set<std::string> c_keywords = {"auto", "break", "case", "char", "const",
		                            "continue", "default", "do", "double",
			                    "else", "enum", "extern", "float", "for",
					    "goto", "if", "int", "long", "register",
			                    "return", "short", "signed", "sizeof",
                                            "static", "struct", "switch", "typedef",
					    "union", "unsigned", "void", "volatile",
					    "while"};

	std::string tmp(code);
	int num_tok, j;

	// Comment matching regex from https://stackoverflow.com/questions/16160190/regular-expression-to-find-c-style-block-comments
	std::string splitter = "(?:\\/\\*[^*]*\\*+(?:[^\\/*][^*]*\\*+)*\\/)"; // multi-line comments
	splitter.append("|(?:\\/\\/(\\s*\\w*)*)"); // single-line comments
	splitter.append("|(\\w+)"); // keywords, identifiers, and other words
	splitter.append("|((\")[^\"]*(\"))"); // double quotes
	splitter.append("|((\')[^\']*(\'))"); // single quotes
	splitter.append("|(==|<=|>=|!=|&&|\\+=|\\-=|\\+\\+|\\-\\-)"); // two character operators
	splitter.append("|[%+\\-/*=^]"); // single character operators
	splitter.append("|[#,<.>{}()[\\]\\|;:]"); // special characters

	std::regex token_splitter(splitter.c_str());

	// Collect tokens from regex
	auto token_start = std::sregex_iterator(tmp.begin(), tmp.end(), token_splitter);
	auto token_stop = std::sregex_iterator();
	num_tok = std::distance(token_start, token_stop);

	std::vector<token_t> tokens;

	for (std::sregex_iterator i = token_start; i != token_stop; ++i) {
		std::smatch match = *i;
		token_t tok;
		tok.contents.assign(match.str());
		tokens.push_back(tok);
	}

	// Assign type to tokens
	std::vector<token_t>::iterator cur = tokens.begin();
	while (cur != tokens.end()) {
		if (std::regex_match((*cur).contents, std::regex("(?:\\/\\*[^*]*\\*+(?:[^\\/*][^*]*\\*+)*\\/)|(?:\\/\\/(\\s*\\w*)*)"))) {
			// Remove comments
			cur = tokens.erase(cur);
		} else if (std::regex_match((*cur).contents, std::regex("(((\")[^\"]*(\")))|((\')[^\']*(\'))"))) {
			(*cur).type = string;
			++cur;
		} else if (std::regex_match((*cur).contents, std::regex("(==|<=|>=|!=|&&|\\+=|\\-=|\\+\\+|\\-\\-)|[%+\\-/*=^]"))) {
			(*cur).type = op;
			++cur;
		} else if (std::regex_match((*cur).contents, std::regex("[#,<.>{}()[\\]\\|;:]"))) {
			(*cur).type = special;
			++cur;
		} else if (std::regex_match((*cur).contents, std::regex("(\\w+)"))) {
			// Check if keyword
			std::set<std::string>::iterator key_it = c_keywords.find((*cur).contents);
			if (key_it != c_keywords.end()) {
				(*cur).type = keyword;
			} else {
				(*cur).type = identifier;
			}
			++cur;
		} else {
			++cur;
		}
	}
	
	return tokens;	
}
