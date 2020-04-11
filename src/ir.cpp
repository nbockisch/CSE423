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
#include "printvisitor.h"

ir::ir(NBlock *root) {
    this->tree = root;
}

/**
 * Parse the parse tree string into a series of token_t structs for IR production
 * @return a token_t vector with the token_t elements of the parse tree
 **/
std::vector<token_t> ir::parse_tree()
{
    //std::string p_tree = this->tree->print(0);
    PrintVisitor visitor;
    this->tree->accept(visitor);
    std::string p_tree = visitor.getResult();
    std::istringstream in_stream(p_tree);
    std::vector<token_t> nodes;
    std::regex tok_regex("([A-z\\d*+-/]+[ ]?[A-z\\d]*)");
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
    int i, j, k, first_param;


    // Cycle through nodes of parse tree and build the IR
    for (i = 1; i < nodes.size(); i++) {
        first_param = 0;
        //std::cout << nodes[i].contents << std::endl;
        if (nodes[i].contents.compare("FUNCTION DECL") == 0) {
            // Build function declaration IR
            std::string tmp;

            for (j = i + 1; nodes[j].level > nodes[i].level && j < nodes.size() && nodes[j].contents.compare("BLOCK") != 0; j++) {
                if (nodes[j].contents.compare("IDENTIFIER") == 0) {
                    tmp.append("function " + nodes[++j].contents + "(");
                } else if (nodes[j].contents.compare("VAR DECL") == 0) {
                    if (first_param == 0) {
                        first_param = 1;
                        tmp.append(nodes[j + 4].contents);
                    } else {
                        tmp.append(", " + nodes[j + 4].contents);
                    }
                    j += 4;
                }                 
            }

            tmp.append(")");
            ir.push_back(tmp);
            tmp.clear();

        } else if (nodes[i].contents.compare("BLOCK") == 0) {
            // Build block statement IR
            std::string tmp;

            for (j = i + 1; nodes[j].level > nodes[i].level && j < nodes.size(); j++) {
                if (nodes[j].contents.compare("ASSIGNMENT") == 0) {
                    first_param = 0;

                    for (k = j + 1; nodes[k].level > nodes[j].level && k < nodes.size(); k++) {
                        if (nodes[k].contents.compare("IDENTIFIER") == 0 || nodes[k].contents.compare("OPERATOR") == 0 || nodes[k].contents.compare("INTEGER") == 0) {
                            if (first_param == 0) {
                                tmp.append(nodes[++k].contents + " =");
                                first_param = 1;
                            } else {
                                tmp.append(" " + nodes[++k].contents);
                            }
                        }
                    }

                    ir.push_back(tmp);
                    tmp.clear();
                } else if (nodes[j].contents.compare("VAR DECL") == 0) {
                    first_param = 0;

                    for (k = j + 1; nodes[k].level > nodes[j].level && k < nodes.size(); k++) {
                        if (nodes[k].contents.compare("IDENTIFIER") == 0 || nodes[k].contents.compare("OPERATOR") == 0 || nodes[k].contents.compare("INTEGER") == 0) {
                            if (first_param == 0) {
                                tmp.append(nodes[++k].contents);
                                first_param = 1;
                            } else if (first_param == 1) {
                                tmp.append(" = " + nodes[++k].contents);
                                first_param = 2;
                            } else {
                                tmp.append(" " + nodes[++k].contents);

                            }
                        }
                    }

                    ir.push_back(tmp);
                    tmp.clear();
                } else if (nodes[j].contents.compare("RETURN") == 0) {
                    tmp.append("return " + nodes[j + 2].contents);
                    j += 2;

                    ir.push_back(tmp);
                    tmp.clear();
                } /*else if (nodes[j].contents.compare("WHILE STATEMENT") == 0) {
                    for (k = j + 1; nodes[k].level > nodes[j].level && k < nodes.size(); k++) {
                        if (nodes[k].contents.compare("IDENTIFIER") == 0 || nodes[k].contents.compare("OPERATOR") == 0 || nodes[k].contents.compare("INTEGER") == 0) {
                            if (first_param == 0) {
                                tmp.append(nodes[++k].contents + " =");
                                first_param = 1;
                            } else {
                                tmp.append(" " + nodes[++k].contents);
                            }
                        }
                    }

                    ir.push_back(tmp);
                    tmp.clear();
                
                } */
            }
        }
    }
   
    return ir;
}
