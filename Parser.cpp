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
                int prod_num = 0;
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
                                std::vector<std::vector<Production>> exprs;
                                prod_num++;
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
                                        
                                        /* Split the line by spaces */
                                        std::string rule;
                                        std::istringstream ss(expr);
                                        std::vector<Production> rules;
                                        while(std::getline(ss, rule, ' ')) {
                                                /* Create a production struct for each part of the rule so we can 
                                                   identify the type of each thing. */
                                                Production prod;
                                                prod.name = rule;

                                                /* Should do some error checking before this.. */
                                                std::string start = rule.substr(0,2);
                                                std::string end = rule.substr(rule.length()-2);
                                                
                                                if(!start.compare("[[") && !end.compare("]]")) {
                                                        prod.type = prod_type::literal;
                                                } else if(!start.compare("((") && !end.compare("))")) {
                                                        prod.type = prod_type::keyw;
                                                } else if(!start.compare("{{") && !end.compare("}}")) {
                                                        prod.type = prod_type::charclass;
                                                } else {
                                                        prod.type = prod_type::nonterminal;
                                                }

                                                if(prod.type == prod_type::literal ||
                                                   prod.type == prod_type::keyw ||
                                                   prod.type == prod_type::charclass) {
                                                        prod.name.erase(0,2);
                                                        prod.name.erase(prod.name.length()-2);
                                                }

                                                prod.level = ++prod_num;
                                                
                                                rules.push_back(prod);
                                        }
                                        exprs.push_back(rules);
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
 * Makes sure all the rules in the grammar are actually correct and resolve correctly.
 */
int Parser::verifyGrammar() {
        // TODO
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
                        std::vector<Production> list = rule.second[j];
                        for(unsigned k = 0; k < list.size(); k++) {
                                printf("%s (%d) ", list[k].name.c_str(), list[k].level);
                        }

                        if( j == rule.second.size()-1) {
                                printf("\n");
                        } else {
                                printf(" | ");
                        }
                }
        }
}

/*
int Parser::search(std::string token) {
        //finds correct grammer matching, returns its level if found, 0 if it's a terminal, or -1 if it was not found
}

std::string Parser::term_match(tmp.name) {
        //Uncertain if needs to be used
}

//Activity, takes token vector, for each token, finds it in the grammer, pushes it to PV and to a normal vector of tokens
int Parser::verify(std::vector<std::string> tokens) {
        PV = new ParseVector;
        std::vector<std::string> stk;
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
