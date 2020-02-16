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

enum prod_type { nonterminal, charclass, literal, keyw };

struct ParsedToken {
	std::string name;
	prod_type tp;
	bool trep; //for if we want to store whether or not this op needs to be in the parse tree
	int priority;
	int children;
};


struct Production {
	prod_type type;
	std::string name;
	int level; // Level is currently the number of the production found as read in from file..

	bool operator==(const Production& x) {
		return x.name == name && x.type == type;
	}
};

typedef std::pair<std::string, std::vector<std::vector<Production>>> Rule;

class Parser {
public:
        Parser(const std::string grammar_file);
        ~Parser();

        int loadGrammar();
        int verifyGrammar();
        void printRules();
        
        std::vector<ParsedToken> releasePV() {return PV;}
		int search(std::vector<std::string> tokens);

private:
        std::string fname;

        std::vector<Rule> rules;
        
        
        std::vector<ParsedToken> PV;
		std::vector<std::string> search_stack;

		int bytype(std::vector<Rule> bfs, std::vector<int> ruleindex, int depth);
		int recalculate_priority(std::string rule);
		Production match(std::string left);
		int verify();
        //std::string term_match(std::string);

};
