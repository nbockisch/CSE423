/**
 * @file ir.h
 * @brief Declares the ir class used for producing a three variable linear IR
 **/

#ifndef IR_H
#define IR_H

#include "node.h"
#include <stdio.h>
#include <string>

struct token_t {
    std::string contents;
    int level;
};

class ir
{
public:
    ir(NBlock *root);
    ~ir();
    std::vector<token_t> parse_tree();
    std::vector<std::string> getIR();
private:
    NBlock *tree;
};

#endif
