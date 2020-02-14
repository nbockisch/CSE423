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

/* Data Structures for Grammer Verifier and Outputs
struct Terminal {
        //std::vector<"TREE">* subtrees; //Internal Tree Construction Method
        //std::string vals; //Simple Output Method
};

struct Operator {
        std::string name;
        std::string term;
        //bool trep; //for if we want to store whether or not this op needs to be in the parse tree
        int priority;
};

struct ParseVector {
        std::vector<Terminal> TermVec;
        std::vector<Operator> OpVec
};
*/

enum prod_type { nonterminal, charclass, literal, keyw };

struct Production {
        prod_type type;
        std::string name;
        int level; // Level is currently the number of the production found as read in from file..
};

typedef std::pair<std::string, std::vector<std::vector<Production>>> Rule;

class Parser {
public:
        Parser(const std::string grammar_file);
        ~Parser();

        int loadGrammar();
        int verifyGrammar();
        void printRules();
        
        //struct ParseVector* releasePV();
        //int verify(std::vector<std::string> tokens);

private:
        std::string fname;

        std::vector<Rule> rules;
        
        /*
        struct ParseVector* PV;
        //int search(std::string token);
        //std::string term_match(std::string)        
        */

};
