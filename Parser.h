/**
 * @file Parser.h
 * @brief Defines the Parser class
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <map>
#include <vector>
#include <regex>

typedef std::pair<std::string, std::vector<std::string>> Rule;

class Parser {
public:
        Parser(const std::string grammar_file);
        ~Parser();

        int loadGrammar();
        void printRules();

private:
        std::string fname;

        std::vector<Rule> rules;
};
