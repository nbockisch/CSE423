**
 * @file Parser.cpp
 * @brief Implementation of the Parser class
 */

#include <string>
#include <fstream>
#include <ctype.h>
#include <sstream>

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
						if (line.size() == 0) {
							continue;
						}
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

//Determine the minimum
int Parser::recalculate_priority(std::string rule) {
	//To do
	return -1;
}

//creates a lr0 array using the rules
void Parser::build_lr0() {
	std::vector<std::vector<std::string>> tmp;
	for (int i = 0; i < rules.size(); i++) {
		for (int j = 0; j < rules[i].second.size(); j++) {
			std::vector<std::string> tmp2;
			for (int k = 0; k < rules[i].second[j].size(); k++) {
				tmp2.push_back(rules[i].second[j][k].name);
			}
			tmp.push_back(tmp2);
			tmp2.clear();
		}
	}

	for (int i = 0; i < tmp.size(); i++) {
		std::vector<std::string> tmp2 = tmp[i];
		for (int j = 0; j <= tmp2.size(); j++) {
			tmp2.insert(tmp2.begin() + j, "\0");
			lr0.push_back(tmp2);
			tmp2.erase(tmp2.begin() + j);
		}
	}
}

//Finds the rule using the right side matching
std::string Parser::find_rule(std::vector<std::string> text) {
	text.erase(std::remove(text.begin(), text.end(), "\0"), text.end());
	for (int i = 0; i < rules.size(); i++) {
		for (int j = 0; j < rules[i].second.size(); j++) {
			bool found = false;
			for (int k = 0; k < rules[i].second[j].size() && k < text.size(); k++) {
				if (rules[i].second[j][k].name == text[k]) {
					found = true;
				}
				else {
					found = false;
					break;
				}
			}
			if (found == true) {
				return rules[i].first;
			}
		}
	}
}

//finds the closure set of any particular lr0 element
std::vector<std::pair<std::string, std::vector<std::string>>> Parser::closure(std::vector<std::string> reduction) {
	std::vector<std::pair<std::string, std::vector<std::string>>> closure_table;
	std::pair<std::string, std::vector<std::string>> x;
	x.second = reduction;
	x.first = find_rule(reduction);

	closure_table.push_back(x);

	bool finish = false;
	while (!finish) {
		finish = true;
		std::vector<std::string>::iterator it = std::find(reduction.begin(), reduction.end(), "\0");
		int dot = std::distance(reduction.begin(), it);

		for (int i = 0; i < rules.size(); i++) {
			if (rules[i].first == reduction[dot + 1]) {
				for (int j = 0; j < lr0.size(); j++) {
					if (find_rule(lr0[j]) == rules[i].first && lr0[j][0] == "\0") {
						finish == false;
						reduction = lr0[j];
						x.second = reduction;
						x.first = rules[i].first;
						closure_table.push_back(x);
						break;
					}
				}
			}
		}
	}
	return closure_table;
}

//Inputs, a set of i0 derived from closure, and a symbol being looked for
std::vector<std::pair<std::string, std::vector<std::string>>> Parser::go_to(std::vector<std::pair<std::string, std::vector<std::string>>> dfa_state, std::string symbol) {
	for (int i = 0; i < dfa_state.size(); i++) {
		for (int j = 0; j < dfa_state[i].second.size(); j++) {
			if (dfa_state[i].second[j] == symbol && j > 0 && dfa_state[i].second[j-1] == "\0") {
				std::vector<std::string> search = dfa_state[i].second;
				std::swap(search[j - 1], search[j]);
				return closure(search); 
			}
		}
	}
	std::vector<std::pair<std::string, std::vector<std::string>>> empty;
	return empty;
}

//Build Action Table
void Parser::build_Actions() {
	
}

//Build Go To Table
void Parser::build_Goto() {
}

//verify the grammer
int Parser::verify(std::vector<std::string> tokens) {
	while (tokens.size() > 0)
	{

	}
	return 0;
}

//For a Given Character, find it's equivalent in the array, == for most, some exceptions
std::string Parser::identify_term(std::string target) {
	return "";
}

