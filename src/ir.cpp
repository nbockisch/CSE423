/**
 * @file ir.cpp
 * @brief Defines the ir class used to produce a three variable linear IR
 **/

//#include "node.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <regex>
#include "ir.h"

ir::ir(NBlock *root) {
    this->tree = root;
}

/**
 * Parse the parse tree string into a series of token_t structs for IR production
 * @return a token_t vector with the token_t elements of the parse tree
 **/
std::vector<token_t> ir::parse_tree()
{
    std::string p_tree = this->tree->print(0);
    std::istringstream in_stream(p_tree);
    std::vector<token_t> nodes;
    std::regex tok_regex("([A-z\\d]+[ ]?[A-z\\d]*)");
    int i, level;

    // Cycle through parse tree line by line
    for (std::string tmp; std::getline(in_stream, tmp);) {
        std::smatch match;
        std::regex_search(tmp, match, tok_regex);
        if (match[0] != "") {
            std::cout << match[0] << std::endl;
        }

        token_t new_tok;
        i = 0;

        while (tmp[i] == ' ') {
            i++;
        }

        new_tok.level = i;
    }

    token_t a;
    nodes.push_back(a);
    return nodes;
}

/**
 * Produce a string array containing lines of the linear IR from the parse tree
 * @return a string vector with the lines of the linear IR from the parse tree
 **/
std::vector<std::string> ir::getIR()
{
    /*StatementList::const_iterator it;
    for (it = this->tree->statements.begin(); it != this->tree->statements.end(); it++) {
        std::cout << "Generating code for " << (**it).print(-2) << std::endl;
    }*/
    ir::parse_tree();
    std::vector<std::string> ir;
    ir.push_back("test");


    return ir;
}
