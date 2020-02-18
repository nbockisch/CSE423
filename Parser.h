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
		int verify(std::vector<std::string> tokens);
		void build_Actions();
		void build_Goto();
private:
        std::string fname;

        std::vector<Rule> rules;
		int index = 0;
        
		std::string terms[37] = { "NUMCONST", "ID", "int", "void", ";", "e", "break", "return", "[", "]", "{", "}", "(", ")", "=", "+=", "-=", "*=", "/=", "++", "--", "or", "and", "not", "<=", "<", ">", ">=", "==", "!=", "+", "-", "*", "div", "%", "?", "," };

		std::vector<std::pair<std::string, int>> ActionsTable;
		std::vector<std::vector<std::pair<Rule, int>>> GoTo;

        std::vector<ParsedToken> PV;
		std::vector<std::string> search_stack;
		std::string identify_term(std::string target);

		int recalculate_priority(std::string rule);
};

