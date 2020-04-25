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
#include <iterator>
#include "ir.h"
#include "printvisitor.h"

ir::ir(Symtable *table) {
    this->table = table;
    this->v_num = 1;
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
                    
                    while (!this->tv_decl.empty()) {
                        tvar_st.push_back(this->tv_decl.top());
                        this->tv_decl.pop();
                    }
                    std::reverse(tvar_st.begin(), tvar_st.end());
                    for (item_t i : tvar_st) {
                        convert_ir.push_back(i);
                    }
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
void ir::convertSSA(std::vector<item_t> &in)
{
    std::vector<ssa_rec> vars;
    std::vector<item_t> items;
    std::vector<item_t>::iterator it;

    for (int i = 0; i < in.size(); i++) {
        if (((&in[i])->label == "IF STATEMENT") || ((&in[i])->label == "IF STATEMENT")) {
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "BIN OP") {
                    for (int k = 0; k < (&in[i])->params[j].params.size(); k++) {
                        if ((&in[i])->params[j].params[k].label == "IDENTIFIER") {
                            std::string tmp2 = (&in[i])->params[j].params[k].id;
                            
                            for (int l = 0; l < vars.size(); l++) {
                                if (vars[l].orig == (&in[i])->params[j].params[k].id) {
                                    (&in[i])->params[j].params[k].id = vars[l].cur; 
                                }
                            }

                            if ((&in[i])->params[j].params[k].id == tmp2) {
                                ssa_rec rec;
                                rec.orig = (&in[i])->params[j].params[k].id;   
                                rec.prev = (&in[i])->params[j].params[k].id;   
                                rec.cur = (&in[i])->params[j].params[k].id;   
                                vars.push_back(rec);
                            }
                        }
                    }
                }
            }
        } else if ((&in[i])->label == "FUNC DECL") {
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "FUNC PARAM") {
                    std::string tmp2 = (&in[i])->params[j].id;
                    
                    for (int k = 0; k < vars.size(); k++) {
                        if (vars[k].orig == (&in[i])->params[j].id) {
                            vars[k].prev = vars[k].cur;
                            vars[k].v_num++;
                            vars[k].cur = vars[k].orig + std::to_string(vars[k].v_num);
                           (&in[i])->params[j].id = vars[k].cur; 
                        }
                    }
                    for (ssa_rec v : vars) {
                    }

                    if ((&in[i])->params[j].id == tmp2) {
                        ssa_rec rec;
                        rec.orig = (&in[i])->params[j].id;   
                        rec.prev = (&in[i])->params[j].id;   
                        rec.cur = (&in[i])->params[j].id;   
                        vars.push_back(rec);
                    }
                }
            }
        } else if ((&in[i])->label == "VAR DECL") {
            std::string tmp = (&in[i])->id;
            for (int j = 0; j < vars.size(); j++) {
                if (vars[j].orig == (&in[i])->id) {
                    // Change current variable name
                    vars[j].prev = vars[j].cur;
                    vars[j].v_num++;
                    vars[j].cur = vars[j].orig + std::to_string(vars[j].v_num);
                    (&in[i])->id = vars[j].cur;
                }
            }
            
            // Check if var  not in record
            if ((&in[i])->id == tmp) {
                ssa_rec rec;
                rec.orig = (&in[i])->id;
                rec.prev = (&in[i])->id;
                rec.cur = (&in[i])->id;
                vars.push_back(rec);
            }

            // Update identifiers (if any)
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "IDENTIFIER") {
                    std::string tmp2 = (&in[i])->params[j].id;
                    
                    for (int k = 0; k < vars.size(); k++) {
                        if (vars[k].orig == (&in[i])->params[j].id) {
                            if ((&in[i])->params[j].id == (&in[i])->id) {
                               (&in[i])->params[j].id = vars[k].prev; 
                            } else {
                                (&in[i])->params[j].id = vars[k].cur; 
                            }
                        }
                    }

                    if ((&in[i])->params[j].id == tmp2) {
                        ssa_rec rec;
                        rec.orig = (&in[i])->params[j].id;   
                        rec.prev = (&in[i])->params[j].id;   
                        rec.cur = (&in[i])->params[j].id;   
                        vars.push_back(rec);
                    }
                }
            }
        } else if ((&in[i])->label == "ASSIGNMENT") {
            // Update identifiers (if any)
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "IDENTIFIER") {
                    std::string tmp2 = (&in[i])->params[j].id;
                    
                    for (int k = 0; k < vars.size(); k++) {
                        if (vars[k].orig == (&in[i])->params[j].id) {
                            vars[k].prev = vars[k].cur;
                            vars[k].v_num++;
                            vars[k].cur = vars[k].orig + std::to_string(vars[k].v_num);
                           (&in[i])->params[j].id = vars[k].cur; 
                        }
                    }

                    if ((&in[i])->params[j].id == tmp2) {
                        ssa_rec rec;
                        rec.orig = (&in[i])->params[j].id;   
                        rec.prev = (&in[i])->params[j].id;   
                        rec.cur = (&in[i])->params[j].id;   
                        vars.push_back(rec);
                    }
                }
            }
            
        } else if ((&in[i])->label == "UNARY OP") {
            // Update identifiers (if any)
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "IDENTIFIER") {
                    std::string tmp2 = (&in[i])->params[j].id;
                    
                    for (int k = 0; k < vars.size(); k++) {
                        if (vars[k].orig == (&in[i])->params[j].id) {
                            vars[k].prev = vars[k].cur;
                            vars[k].v_num++;
                            vars[k].cur = vars[k].orig + std::to_string(vars[k].v_num);
                           (&in[i])->params[j].id = vars[k].cur; 
                        }
                    }

                    if ((&in[i])->params[j].id == tmp2) {
                        ssa_rec rec;
                        rec.orig = (&in[i])->params[j].id;   
                        rec.prev = (&in[i])->params[j].id;   
                        rec.cur = (&in[i])->params[j].id;   
                        vars.push_back(rec);
                    }
                }
            }

        }
    } 
}

/**
 * Take the nodes gathered from the parse tree and construct the final IR
 * @return a vector of item_t objects holding the components of the final IR
 **/
std::vector<item_t> ir::buildIr()
{
    std::vector<item_t> tmp_list;


    // Gather the nodes from the tree
    while (!this->blocks.empty()) {
        tmp_list.push_back(this->blocks.back());
        this->blocks.pop_back(); 
    }

    tmp_list = convert3Var(cleanIr(tmp_list));

    convertSSA(tmp_list);
    
    return tmp_list;
}
