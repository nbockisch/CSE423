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

//Perfomrs a breadth first search of the grammer list to determine the minimum path to reach the rule from root
int Parser::recalculate_priority(std::string rule) {
	//To do
	return -1;
}

//Takes vector at instance, determines the operation in the grammer the token string belongs in, pushes it in post order format to PV, and reduces it for search_stack for all base tokens
int Parser::search(std::vector<std::string> tokens) {
	int index = 0;
	int depth = 0;
	std::vector<Rule> bfs;
	std::vector<int> ruleindex;
	std::vector<bool> findex;
	while (index < tokens.size()) { //Termination condition
		search_stack.push_back(tokens[index]);
		bool found = false;
		if (bfs.size() > 0) {
			for (int i = 0; i < bfs.size(); i++) { //breadth first search of remaining grammer rules
				if (search_stack[search_stack.size() - 1] == bfs[i].second[ruleindex[i]][depth].name) {
					findex.push_back(true);
					found = true;
				}
				else {
					findex.push_back(false);
				}
			}
		}
		else { //Initial full search for begining of breadth first search
			for (int i = 0; i < rules.size(); i++) { //Searches for token in right hand side
				for (int j = 0; j < rules[i].second.size(); j++) {
					if (search_stack[search_stack.size() - 1] == rules[i].second[j][depth].name) { //Construct breadth first search setup when next token is found
						bfs.push_back(rules[i]);
						ruleindex.push_back(j);
						findex.push_back(true);
						found = true;
					}
				}
			}
		}
		if (found == false && bytype(bfs, ruleindex, depth) == false) { //invalid token couldn't find a match in the grammer
			return -1;
		}
		//gets rid of all failed branches in the breadth first search
		int i = 0;
		bool noreduc = true;
		while (i < findex.size()) {
			if (findex[i] == false) {
				findex.erase(findex.begin() + i);
				bfs.erase(bfs.begin() + i);
				ruleindex.erase(ruleindex.begin() + i);
				continue;
			}
			else {
				if ((depth + 1) == bfs[i].second[ruleindex[i]].size()) { //Branch is completed and can be reduced
					
					//Todo: Instead of finishing at first completable branch, preserve branch and move forward until all other branches have been invalidated or reached reducibility, then choose the highest one
					//Possible Issue, the rule closer to the root level is looking for a lower level rule that is equally valid with one that is not chosen, branching situation occurs there

					ParsedToken p;
					noreduc = false;
					for (int j = 0; j <= depth; j++) { //setup Parse Tree Vector pushes
						p.name = tokens[index - (depth + 1 + j)];
						p.tp = bfs[i].second[ruleindex[i]][j].type;
						p.trep = true;
						if (p.name == "(" || p.name == ")" || p.name == "{" || p.name == "}" || p.name == ";" || p.name == "," || p.name == ":") { //things not desired in tree representation
							p.trep = false;
						}
						if (bfs[i].second[ruleindex[i]][j].type == nonterminal) {
							p.children = depth + 1;
							p.priority = recalculate_priority(bfs[i].first); //not finished
						}
						else {
							p.children = 0;
							p.priority = -1;
						}
						PV.push_back(p);
					}
					while (depth >= 0) { //constructs remove elements currently in search_stack;
						search_stack.pop_back();
						depth--;
					}
					search_stack.push_back(bfs[i].first); //reduction
					bfs.clear();
					ruleindex.clear();
					findex.clear();
					break;
				}
				i++;
			}
			if (noreduc == true && bfs.size() == 0) { //May need to be altered to ensure
				return -1;
			}
		}
		depth++;
		index++;
		findex.clear(); //used repeatedly
	}
	
	//once base is completed, use a function to reduce to correctness
	verify();
}

//Search by type
int Parser::bytype(std::vector<Rule> bfs, std::vector<int> ruleindex, int depth) {
	std::string token = search_stack.back();
	search_stack.pop_back();
	ParsedToken p;
	p.name = token;
	p.priority = -1;
	p.tp = charclass;
	p.trep = true;
	if (isalpha(token[0])) {
		PV.push_back(p);
		token = "ID";
	}
	else if (isdigit(token[0])) {
		PV.push_back(p);
		token = "NUMCONST";
	}
	else if (token == "") { //Empty Argument List, check this for debugging, should happen during basic lr parse
		PV.push_back(p);
		token == "epsilon";
	}
	else {
		return -1;
	}
	
	//New Search
	search_stack.push_back(token);
	bool found = false;
	if (bfs.size() > 0) {
		std::vector<bool> findex;
		for (int i = 0; i < bfs.size(); i++) { //breadth first search of remaining grammer rules
			if (search_stack[search_stack.size() - 1] == bfs[i].second[ruleindex[i]][depth].name) {
				findex.push_back(true);
				found = true;
			}
			else {
				findex.push_back(false);
			}
		}
		if (found == false) {
			return -1;
		}
	}
	else {
		for (int i = 0; i < rules.size(); i++) { //Searches for token in right hand side
			for (int j = 0; j < rules[i].second.size(); j++) {
				if (token == rules[i].second[j][depth].name) { //Construct breadth first search setup when next token is found
					bfs.push_back(rules[i]);
					ruleindex.push_back(j);
					found = true;
				}
			}
		}
	}
	if (found == false) {
		return -1;
	}
	return 0;
}

//Resolves oversight in Grammer Structure
Production Parser::match(std::string left) {
	for (int i = 0; i < rules.size(); i++) {
		for (int j = 0; j < rules[i].second.size(); j++) {
			for (int k = 0; k < rules[i].second[j].size(); k++) {
				if (left == rules[i].second[j][k].name) {
					return rules[i].second[j][k];
				}
			}
		}
	}
}

//Goes through the search_stack until it completes to root or fails
int Parser::verify() {
	std::vector<Rule> bfs;
	std::vector<int> ruleindex;
	std::vector<bool> findex;
	int depth = 0;
	int index = 0;
	while (true) { //Termination condition
		bool found = false;
		if (bfs.size() > 0) {
			for (int i = 0; i < bfs.size(); i++) { //breadth first search of remaining grammer rules
				if (search_stack[index] == bfs[i].second[ruleindex[i]][depth].name) {
					findex.push_back(true);
					found = true;
				}
				else {
					findex.push_back(false);
				}
			}
			if (found == false && bytype(bfs, ruleindex, depth) == false) {
				return -1;
			}
			else { //gets rid of all failed branches in the breadth first search
				int i = 0;
				bool noreduc = true;
				while (i < bfs.size()) {
					if (findex[i] == false) {
						findex.erase(findex.begin() + i);
						bfs.erase(bfs.begin() + i);
						ruleindex.erase(ruleindex.begin() + i);
						continue;
					}
					else {
						if (depth == bfs[i].second[ruleindex[i]].size()) { //Branch is completed and can be reduced
							noreduc = false;
							while (depth > 0) { //constructs remove elements currently in search_stack;
								search_stack.pop_back();
								depth--;
							}
							search_stack.push_back(bfs[i].first); //reduction
							bfs.clear();
							ruleindex.clear();
							findex.clear();
							break;
						}
					}
					i++;
				}
				if (noreduc == true && bfs.size() == 0) { //May need to be altered to ensure
					return -1;
				}
				else if (search_stack.size() == 1 && search_stack.back() == "program") { //correct exit condition
					return 0;
				}
			}
		}
		else { //Initial full search for begining of breadth first search
			for (int i = 0; i < rules.size(); i++) { //Searches for token in right hand side
				for (int j = 0; j < rules[i].second.size(); j++) {
					if (search_stack[search_stack.size() - 1] == rules[i].second[j][depth].name) { //Construct breadth first search setup when next token is found
						bfs.push_back(rules[i]);
						ruleindex.push_back(j);
						found = true;
					}
				}
			}
		}
		if (found == false && bytype(bfs, ruleindex, depth) == false) { //invalid token couldn't find a match in the grammer
			return -1;
		}
		depth++;
		index++;
		if (index >= search_stack.size()) {
			index = 0;
		}
	}
}

