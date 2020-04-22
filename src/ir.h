/**
 * @file ir.h
 * @brief Declares the ir class used for producing a three variable linear IR
 **/

#ifndef IR_H
#define IR_H

#include "node.h"
#include "symtable.h"
#include <stdio.h>
#include <string>
#include <deque>

struct item_t {
    std::string label;
    std::string type;
    std::string id;
    std::string val;
    std::vector<item_t> params;
};

class ir
{
public:
    ir(Symtable *table);
    ~ir() { };
    std::deque<item_t> blocks;
    std::vector<item_t> cleanIr(std::vector<item_t> items);
    std::vector<item_t> buildIr();
private:
    std::vector<item_t> items;
    Symtable *table;
};

#endif
