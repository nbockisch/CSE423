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
        if (match[0] == "") {
            continue;
        }

        token_t new_tok;
        i = 0;

        while (tmp[i] == ' ') {
            i++;
        }

        new_tok.level = i;
        new_tok.contents = match[0];
        nodes.push_back(new_tok);
    }

    //token_t a;
    //nodes.push_back(a);
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
    std::vector<token_t> nodes = ir::parse_tree();
    std::vector<std::string> ir;
    int i, j, end, first_param, block, found_name;

    // Cycle through nodes of parse tree and build the IR
    for (i = 0; i < nodes.size(); i++) {
        if (nodes[i].contents.compare("FUNCTION DECL") == 0) {
            block = 0;
            found_name = 0;
            first_param = 1;
            std::string tmp;
            end = nodes[i].level;
            for (j = i + 1; nodes[j].level > end && j < nodes.size(); j++) {
                if (nodes[j].contents.compare("IDENTIFIER") == 0) {
                    if (!found_name) {
                        tmp.append(nodes[j + 1].contents + "(");
                        found_name = 1;
                    }
                } else if (nodes[j].contents.compare("BLOCK") == 0) {
                    block = 1;
                    tmp.append(")");
                    ir.push_back(tmp);
                    tmp.clear();
                } else if (nodes[j].contents.compare("VAR DECL") == 0) {
                    if (!block) {
                        if (first_param) {
                            tmp.append(nodes[j + 4].contents);
                            first_param = 0;
                        } else {
                            tmp.append(", " + nodes[j + 4].contents);
                        }
                    }
                }  else if (nodes[j].contents.compare("RETURN") == 0 && block) {
                    std::string tmp;
                    tmp.append(" return " + nodes[i + 2].contents);
                    ir.push_back(tmp);
                    tmp.clear();
                }
            }
        }  /*else if (nodes[i].contents.compare("RETURN") == 0) {
            std::string tmp;
            tmp.append("return " + nodes[i + 2].contents);
            ir.push_back(tmp);
        }*/
    }

    /* for (std::string q : ir) {
        std::cout << q << std::endl;
    } */
    return ir;
}
