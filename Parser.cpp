/**
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

//Perfomrs a breadth first search of the grammer list to determine the minimum path to reach the rule from root
int Parser::recalculate_priority(std::string rule) {
	//To do
	return -1;
}

//Determines if an element in the breadth first search can be replaced with epsilon
std::string Parser::can_epsilon(std::string main_rule) {
	for (int i = 0; i < rules.size(); i++) { //Search Rules
		if (main_rule == rules[i].first) { //For Input
			for (int j = 0; j < rules[i].second.size(); j++) { //Check all reduction rules
				for (int k = 0; k < rules[i].second[j].size(); k++) { //Check all parts of the reduction rules
					for (int x = 0; x < rules.size(); x++) { //look up all reduction rule parts
						if (rules[i].second[j][k].name == rules[x].first) { //that were part of main input
							for (int y = 0; y < rules[x].second.size(); y++) { //search all subrules
								if (rules[x].second[y][0].name == "epsilon") { //for one that has epsilon
									return rules[x].first; //returns the name of that as it exists in main_rule
								}
							}
						}
					}
				}
			}
		}
	}
	return "";
}


//Takes vector at instance, determines the operation in the grammer the token string belongs in, pushes it in post order format to PV, and reduces it for search_stack for all base tokens
std::string Parser::search(std::vector<std::string> tokens) {
	std::vector<Rule> bfs;
	std::vector<int> ruleindex;
	std::vector<bool> findex;
	std::vector<int> depths;
	bool found = true;
	while (found) { //bfs exploration
		found = false;
		if (bfs.size() > 0) {
			for (int i = 0; i < bfs.size(); i++) { //breadth first search of remaining grammer rules
				if (search_stack.back() == bfs[i].second[ruleindex[i]][depths[i]].name) {
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
					if (search_stack.back() == rules[i].second[j][0].name) { //Construct breadth first search setup when next token is found
						bfs.push_back(rules[i]);
						ruleindex.push_back(j);
						findex.push_back(true);
						depths.push_back(0);
						found = true;
					}
				}
			}
		}
		if (found == false) {
			if (bytype() != "") {
				found = true;
				findex.clear();
				continue;
			}
		}
		//gets rid of all failed branches in the breadth first search
		//also launches new searchers in order to determine if a branch is truly failed
		int i = 0;
		bool noreduc = true;
		while (i < findex.size()) {
			if (findex[i] == false) {
				std::string tmp;
				if (can_epsilon(bfs[i].first) == bfs[i].second[ruleindex[i]][depths[i]].name) { //tests if a statement can be reduced to using nothing
					if (search_stack.back() != bfs[i].second[ruleindex[i]][depths[i]+1].name) { //checks if the name that caused the failure is now valid
						search_stack.pop_back();
						search_stack.push_back(bfs[i].second[ruleindex[i]][depths[i]].name);
						index--;
						std::string prev = search_stack.back();
						std::string tmp = search(tokens);
						if (tmp != bfs[i].second[ruleindex[i]][depths[i]+1].name) {
							search_stack.pop_back();
							search_stack.push_back(prev);
							findex.erase(findex.begin() + i);
							bfs.erase(bfs.begin() + i);
							ruleindex.erase(ruleindex.begin() + i);
							depths.erase(depths.begin() + i);
						}
					}
					else {
						search_stack.insert(search_stack.end() - 1, bfs[i].second[ruleindex[i]][depths[i]].name);
						found = true;
						depths[i]++;
					}
				}
				else { //checks if failed token can be reduced

					//To Do, ensure that failed returns properly clear everything from the search_stack

					std::string prev = search_stack.back();
					std::string tmp = search(tokens);
					if (tmp != bfs[i].second[ruleindex[i]][depths[i]].name) { //rule has failed
						findex.erase(findex.begin() + i);
						bfs.erase(bfs.begin() + i);
						ruleindex.erase(ruleindex.begin() + i);
						depths.erase(depths.begin() + i);
						PV.pop_back();
						search_stack.pop_back();
						search_stack.push_back(prev);
						continue;
					}
				}
			}
			if ((depths[i] + 1) == bfs[i].second[ruleindex[i]].size()) { //Branch is completed and can be reduced
				int max = 0;
				for (int y = 0; y < depths.size(); y++) {
					if (bfs[i].second[ruleindex[i]].size() > max) {
						max = bfs[i].second[ruleindex[i]].size();
					}
				}
				
				if (depths[i] == max-1) {
					//To Do, see if this limit on search can be removed and allow a failed return to clear it from search stack
					if (max != 1) {
						std::string prev = search_stack.back();
						std::string tmp = search(tokens);
						if (recalculate_priority(tmp) < recalculate_priority(bfs[i].first)) {
							search_stack.pop_back();
							search_stack.push_back(prev);
						}
					}
					ParsedToken p;
					noreduc = false;
					p.name = tokens[index];
					p.tp = bfs[i].second[ruleindex[i]][bfs[i].second[ruleindex[i]].size()-1].type;
					p.trep = true;
					if (p.name == "(" || p.name == ")" || p.name == "{" || p.name == "}" || p.name == ";" || p.name == "," || p.name == ":") { //things not desired in tree representation
						p.trep = false;
					}
					if (bfs[i].second[ruleindex[i]][bfs[i].second[ruleindex[i]].size() - 1].type == nonterminal) {
						p.children = depths[i] + 1;
						p.priority = recalculate_priority(bfs[i].first); //not finished
					}
					else {
						p.children = 0;
						p.priority = -1;
					}
					PV.push_back(p);
					
					int cnt = 0;
					while (depths[i] >= 0) { //constructs remove elements currently in search_stack;
						search_stack.pop_back();
						depths[i]--;
						cnt++;
					}
					search_stack.push_back(bfs[i].first); //reduction
					bfs.clear();
					ruleindex.clear();
					findex.clear();
					depths.clear();

					if (cnt > 1 || search_stack.back() == "program")
						return search_stack.back();
				}
			}
			i++;
		}
		if (noreduc && pushtok(tokens) == -1) { //second half only happens when no reduction occurs for an entire cycle
			return search_stack.back();
		}
		for (int y = 0; y < depths.size(); y++) {
			depths[y]++;
		}
		findex.clear(); //used repeatedly
	}
	//once base is completed, use a function to reduce to correctness
	return search_stack.back();
}

int Parser::pushtok(std::vector<std::string> tokens) {
	if (index < tokens.size()) {
		search_stack.push_back(tokens[index]);
		index++;
		return 0;
	}
	return -1;
}

//Search by type
std::string Parser::bytype() {
	std::string token = search_stack.back();

	for (int i = 0; i < rules.size(); i++) {
		if (token == rules[i].first) {
			return "";
		}
		for (int j = 0; j < rules[i].second.size(); j++) {
			for (int k = 0; k < rules[i].second[j].size(); k++) {
				if (token == rules[i].second[j][k].name) {
					return "";
				}
			}
		}
	}

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
		return "";
	}
	
	//New Search
	search_stack.pop_back();
	search_stack.push_back(token);
	return search_stack.back();
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
