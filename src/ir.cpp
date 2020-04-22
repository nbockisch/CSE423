/**
 * @file ir.cpp
 * @brief Defines the ir class used to produce a three variable linear IR
 **/

//#include "node.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <regex>
#include <stack>
#include <algorithm>
#include "ir.h"
#include "printvisitor.h"

ir::ir(Symtable *table) {
    this->table = table;
}

void tmpPrint(std::vector<item_t> lol, int level)
{
    for (item_t test : lol) {
        if (test.params.size() != 0) {
            std::reverse(test.params.begin(), test.params.end());
            tmpPrint(test.params, level + 1);
        }
        for (int i = 0; i < level; i++) {
            std::cout << " ";
        }
        std::cout << "Label: " << test.label << ", type: " << test.type << ", id: " << test.id << ", val: " << test.val << std::endl;
    }
}

/**
 * Recursive function that converts the IR representation from the tree 
 * traversal to something easier to handle
 * @return A vector of item_t objects with an easir to handle representation
 **/
std::vector<item_t> ir::cleanIr(std::vector<item_t> items)
{
    std::vector<item_t> ir_list;

    for (item_t item : items) {
        ir_list.push_back(item);
        if (item.params.size() != 0) {
            //std::reverse(item.params.begin(), item.params.end());
            for (item_t item2 : cleanIr(item.params)) {
                ir_list.push_back(item2);
            }
        }
    }

    return ir_list;
}

/**
 * Take the nodes gathered from the parse tree and construct the final IR
 * @return a vector of item_t objects holding the components of the final IR
 **/
std::vector<item_t> ir::buildIr()
{
    std::vector<item_t> fin_ir;
    std::vector<item_t> tmp_list;

    int first_param = 1;

    // Gather the nodes from the tree
    while (!this->blocks.empty()) {
        tmp_list.push_back(this->blocks.back());
        this->blocks.pop_back(); 
    }

    //tmpPrint(tmp_list, 0);
    /*for (item_t test : cleanIr(tmp_list)) {
        std::cout << "Label: " << test.label << ", type: " << test.type << ", id: " << test.id << ", val: " << test.val << std::endl;
    }*/

    for (item_t item : cleanIr(tmp_list)) {
        if (item.label == "FUNC DECL") {
            first_param = 1;
            std::cout << item.type << " " << item.id << "(";
            for (item_t item2 : item.params) {
                if (item2.label == "FUNC PARAM") {
                    if (first_param == 1) {
                        std::cout << item2.type << " " << item2.id;
                        first_param = 0;
                    } else {
                        std::cout << ", " << item2.type << " " << item2.id;
                    }
                }
            }
            std::cout << ")" << std::endl;
        }
    }

    return tmp_list;
}
