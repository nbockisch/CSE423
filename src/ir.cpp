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
    this->v_num = 1;
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
        if (item.label != "FUNC PARAM" && item.label != "BIN OP" && item.label != "IDENTIFIER" && item.label != "INTEGER" && item.label != "OP") {
            ir_list.push_back(item);
            if (item.params.size() != 0) {
                //std::reverse(item.params.begin(), item.params.end());
                for (item_t item2 : cleanIr(item.params)) {
                    ir_list.push_back(item2);
                }
            }
        }
    }

    return ir_list;
}

void ir::convertBinOp(item_t item)
{
    item_t assignment;
    assignment.label = "VAR DECL";
    assignment.id = "X" + std::to_string(this->v_num);
    this->v_num++;

    for (item_t item : item.params) {
        if (item.label == "BIN OP") {
            //std::cout << "HERE" <<
            convertBinOp(item);
            item_t tmp;
            tmp.label = "IDENTIFIER";
            tmp.id = this->tv_decl.top().id;
            assignment.params.push_back(tmp);
        } else {
            assignment.params.push_back(item);
        }
    }

    this->tv_decl.push(assignment);
}

/**
 * Convert an item_t vector with IR information to 3 variable form
 * @param items an item_t vector with IR information
 * @return an item_t vector with IR information converted to 3 variable form
 **/
std::vector<item_t> ir::convert3Var(std::vector<item_t> items)
{
    std::vector<item_t> convert_ir;

    for (item_t item : items) {
        if ((item.label == "ASSIGNMENT") || (item.label == "VAR DECL")) {
            for (item_t item2 : item.params) {
                if (item2.label == "BIN OP") {
                    std::vector<item_t> tvar_st;
                    convertBinOp(item2);
                    //std::cout << "=== START TESTING BIN OP ===" << std::endl;
                    
                    while (!this->tv_decl.empty()) {
                        /*std::cout << "Label: " << this->tv_decl.top().label << ", type: " << this->tv_decl.top().type << ", id: " << this->tv_decl.top().id << ", val: " << this->tv_decl.top().val << std::endl;*/
                        tvar_st.push_back(this->tv_decl.top());
                        this->tv_decl.pop();
                    }
                    std::reverse(tvar_st.begin(), tvar_st.end());
                    for (item_t i : tvar_st) {
                        convert_ir.push_back(i);
                    }
                    //std::cout << "=== END TESTING BIN OP ===" << std::endl;
                } else {
                    convert_ir.push_back(item);
                }
            }
        } else {
            convert_ir.push_back(item);
        }
    }

    return convert_ir;
}

/**
 * Converts a three variable form IR to SSA form
 * @param items a vector of item_t structs with a three variable IR
 * @return a vector of item_t structs in SSA form
 **/
/*std::vector<item_t> ir::convertSSA(std::vector<item_t> items)
{
    std::vector<ssa_rec> vars;

    for (item_t item : items) {
        if (item.label == "FUNC DECL") {
            for (item_t item2 : item.params) {
                if (item2.label = "FUNC PARAM") {
                    // Check if var already recorded
                    for (ssa_rec i : vars) {
                        if (i.orig == item2.id) {
                            if 
                        }
                    }

                }
            }
        }
    }
}*/

/**
 * Take the nodes gathered from the parse tree and construct the final IR
 * @return a vector of item_t objects holding the components of the final IR
 **/
std::vector<item_t> ir::buildIr()
{
    std::vector<item_t> fin_ir;
    std::vector<item_t> tmp_list;


    // Gather the nodes from the tree
    while (!this->blocks.empty()) {
        tmp_list.push_back(this->blocks.back());
        this->blocks.pop_back(); 
    }

    tmp_list = convert3Var(cleanIr(tmp_list));

    //tmpPrint(tmp_list, 0);
    /*for (item_t test : cleanIr(tmp_list)) {
        //std::cout << "Label: " << test.label << ", type: " << test.type << ", id: " << test.id << ", val: " << test.val << std::endl;
    }*/

    /*std::cout << "LOL THIS WILL FAIL!!!" << std::endl;
    for (item_t test2 : convert3Var(cleanIr(tmp_list))) {
        std::cout << "Label: " << test2.label << ", type: " << test2.type << ", id: " << test2.id << ", val: " << test2.val << std::endl;
            for (item_t test : test2.params) {
               std::cout << "- Label: " << test.label << ", type: " << test.type << ", id: " << test.id << ", val: " << test.val << std::endl;
            }
        if (test2.label == "VAR DECL") {
            for (item_t test : test2.params) {
               std::cout << "- Label: " << test.label << ", type: " << test.type << ", id: " << test.id << ", val: " << test.val << std::endl;
            }

        }
    }*/

    /* for (item_t item : cleanIr(tmp_list)) {
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
    } */

    return tmp_list;
}
