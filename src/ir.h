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

struct item_t {
    std::string label;
    std::string type;
    std::string id;
    std::vector<item_t> params;
};

class ir
{
public:
    ir(Symtable *table);
    ~ir() { };
    std::vector<item_t> items;
private:
    Symtable *table;
};

#endif
