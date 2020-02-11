/**
 * @file Parser.cpp
 * @brief Implementation of the Parser class
 */

#include <string>
#include <fstream>
#include <ctype.h>

#include "Parser.h"

Parser::Parser(const std::string grammar_file) {
        this->fname = grammar_file;
        printf("Grammar file: '%s'\n", this->fname.c_str());
}

Parser::~Parser() {
        
}

/**
 * Loads the grammar file specified when the Parser was created.
 * Populates the rules vector in the Parser itself
 * @returns 0 on success, -1 on error
 */
int Parser::loadGrammar() {

        std::ifstream file;

        file.open(this->fname);
        if(file.is_open()) {
                std::string line;
                int lc = 0;
                while(std::getline(file, line)) {
                        lc++;
                        // Skip since comment or blank line.. NOTE: Probably need more robust checking here..
                        if (line.front() == '#' || line.front() == '\0') {
                                continue;
                        }
                        std::smatch match;
                        
                        // Regex to search for "word = rule | rule" etc. Technically matches "word = | " but minor issue.
                        std::regex left("([[:alpha:]]+)(?:\\s*=\\s*)(?:([^\\\\|]+)|(?:([^\\\\|]+)(?:[\\\\|])([^\\\\|]+)))+");
                        
                        if(std::regex_match(line, match, left)) {
                                std::vector<std::string> exprs;
                                for(unsigned i = 2; i < match.size(); i++) {
                                        std::string expr = match[i].str();
                                        // Strip a leading space if any.
                                        if(!expr.empty() && expr.front() == ' ') {
                                                expr.erase(0, 1);
                                        }
                                        // Remove any empty strings
                                        if(expr.empty()) {
                                                continue;
                                        }
                                        exprs.push_back(expr);
                                }
                                rules.push_back(Rule(match[1].str(), exprs));
                        } else {
                                printf("Error: Parsing grammar '%s' at line %d: Invalid statement '%s'\n", fname.c_str(), lc, line.c_str());
                                return -1;
                        }
                }

                file.close();
        } else {
                printf("Error opening grammar file '%s'\n", this->fname.c_str());
                return -1;
        }

        return 0;
}

/**
 * Displays all rules loaded by the loadGrammar() function.
 */
void Parser::printRules() {
        for(unsigned i = 0; i < rules.size(); i++) {
                Rule rule = rules[i];
                printf("%d: %s = ", i+1, rule.first.c_str());
                for(unsigned j = 0; j < rule.second.size(); j++) {
                        if ( j == rule.second.size()-1) {
                                printf("%s\n", rule.second[j].c_str());
                        } else {
                                printf("%s | ", rule.second[j].c_str());
                        }
                }
        }
}

/*
int Parser::search(std::string token) {
        //Waiting for Grammer Format
}

std::string Parser::term_match(tmp.name) {
        //Waiting for Grammer Format
}

int Parser::verify(std::vector<std::string> tokens) {
        PV = new ParseVector;
        int depth = 0;
        std::vector<int> hold;
        hold.push_back(0);
        for(int i = 0; i < tokens.size(); i++) {
                depth = search(tokens[i]);
                if(depth < 0) {
                        hold.push_back(i);
                } else if(depth == 0) {
                        PV->TermVec.push_back(tokens[i])
                } else {
                        struct Operator tmp;
                        tmp.name = tokens[i];
                        tmp.term = term_match(tmp.name);
                        PV->OpVec.push_back(tmp);
                }
        }
        while(hold.size() != 0) {
                depth = search(hold.peek());
                if(depth < 0) {
                        //Error Situation
                } else if(depth == 0) {
                        PV->TermVec.push_back(hold.pop())
                } else {
                        struct Operator tmp;
                        tmp.name = hold.pop();
                        tmp.term = term_match(tmp.name);
                        PV->OpVec.push_back(tmp);
                }
        }
}
*/
