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
#include <stack>

struct item_t {
    std::string label;
    std::string type;
    std::string id;
    std::string val;
    int tag;
    std::vector<item_t> params;
};

struct ssa_rec {
    std::string orig;
    std::string cur;
    std::string prev;
    int v_num = 0;
};

class ir
{
public:
    ir(Symtable *table);
    ~ir() { };
    std::deque<item_t> blocks;
    std::vector<item_t> cleanIr(std::vector<item_t> items);
    void convertBinOp(item_t item);
    std::vector<item_t> convert3Var(std::vector<item_t> items);
    void convertSSA(std::vector<item_t> &in);
    std::vector<item_t> buildIr();
    std::vector<item_t> items;

    std::string printIR(std::vector<item_t> items);
    void writeIR(std::string fname, std::vector<item_t> items);
    std::vector<item_t> readIR(std::string fname);
private:
    
    std::stack<item_t> tv_decl;
    int v_num;
    Symtable *table;

    std::string itemPrint(item_t *item, int level);
};

#endif
