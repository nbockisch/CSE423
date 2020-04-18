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

ir::ir(Symtable *table) {
    this->table = table;
}
