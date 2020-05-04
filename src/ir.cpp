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
        if (item.label == "BLOCK") {
            item_t tmp;
            tmp.label = "BLOCK END";
            ir_list.push_back(tmp);
        }
    }

    return ir_list;
}

void ir::convertBinOp(item_t in_item)
{
    item_t assignment;
    assignment.label = "VAR DECL";
    assignment.id = "X" + std::to_string(this->v_num);
    this->v_num++;

    for (item_t item : in_item.params) {
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
                    //std::cout << tvar_st.front().id << std::endl;

                    item_t tmp;
                    tmp.label = item.label;
                    tmp.id = item.id;
                    tmp.type = item.type;
                    tmp.val = item.val;
                    tmp.params.push_back(tvar_st.front());
                    tvar_st.push_back(tmp);
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
        } else if ((&in[i])->label == "FUNCTION CALL" || (&in[i])->label == "FUNC DECL") {
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "IDENTIFIER" || (&in[i])->params[j].label == "FUNC PARAM") {
                    std::string tmp2 = (&in[i])->params[j].id;
                    
                    for (int k = 0; k < vars.size(); k++) {
                        if (vars[k].orig == (&in[i])->params[j].id) {
                            /*vars[k].prev = vars[k].cur;
                            vars[k].v_num++;
                            vars[k].cur = vars[k].orig + std::to_string(vars[k].v_num);*/
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
        } else if (((&in[i])->label == "ASSIGNMENT")) {
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
            
        } else if (((&in[i])->label == "RETURN") || ((&in[i])->label == "UNARY OP") || ((&in[i])->label == "WHILE STATEMENT")) {
            // Update identifiers (if any)
            for (int j = 0; j < (&in[i])->params.size(); j++) {
                if ((&in[i])->params[j].label == "IDENTIFIER" && ((&in[i])->label != "RETURN")) {
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

        }
    } 
}

bool const_fold(item_t* block)
{
    bool val = false;
    for (item_t i: block->params) {
        if (i.label == "ASSIGNMENT") {
            if (i.params.size() == 3 && std::isdigit(i.params[1].val[0]) && std::isdigit(i.params[2].val[0])) {
                val = true;
                i.params[1].val = std::to_string(atoi(i.params[1].val) + atoi(i.params[2].val));
                i.params.pop_back();
            }
        }
    }
    return val;
}

bool const_prop(item_t* block)
{
    std::string tmp = "";
    std::string tmp1 = "";
    bool val = false;
    for (item_t i: block->params) {
        if (i.label == "ASSIGNMENT") {
            if (i.params.size() == 2 && std::isdigit(i.params[1].val[0])) {
                tmp = i.params[0].val;
                tmp1 = i.params[1].val;
            }
        }
        for (int j = 1; j < i.params.size(); j++) {
            if (i.params[j].val == tmp) {
                val = true;
                i.params[j].val = tmp1;
            }
        }
    }
    return val;
}

void optimization_1(std::vector<item_t> list)
{
    for (item_t i: list) {
        if (i.label == "BLOCK") {
            bool f,p = false;
            while (f || p) {
                f = const_fold(&i);
                p = const_prop(&i);
            }
        } else if (!i.params.empty()) {
            optimization_1(i.params);
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

    /*for (item_t a : tmp_list) {
        std::cout << "label = " << a.label << ", type = " << a.type << ", id = " << a.id << ", val = " << a.val << std::endl;
        for (item_t b : a.params) {
            std::cout << "- label = " << b.label << ", type = " << b.type << ", id = " << b.id << ", val = " << b.val << std::endl;
            for (item_t c : b.params) {
                std::cout << "-- label = " << c.label << ", type = " << c.type << ", id = " << c.id << ", val = " << c.val << std::endl;
            }
        }
    }*/
    
    return tmp_list;
}

std::string ir::itemPrint(item_t *item) {
        std::string out;

        out.append("Label: "+item->label+"\n");
        out.append("Type: "+item->type+"\n");
        out.append("ID: "+item->id+"\n");
        out.append("Val: "+item->val+"\n");
        out.append("Tag: "+std::to_string(item->tag)+"\n");

        //Print the number of parameters to keep track
        out.append("Params: "+std::to_string(item->params.size())+"\n");

        if(item->params.size() > 0) {
                for(uint i = 0; i < item->params.size(); i++) {
                        out.append(itemPrint(&(item->params[i])));
                }
        }
        
        return out;
}

std::string ir::printIR(std::vector<item_t> items) {
        std::string out;
        
        for(uint i = 0; i < items.size(); i++) {
                item_t item = items[i];
                
                out.append(itemPrint(&item));
        }

        return out;
        
}

void ir::writeIR(const char *fname, std::vector<item_t> items) {
        FILE *fp = fopen(fname, "w");
        if(fp == NULL) {
                printf("Error: Cannot open file '%s' to write IR.\n", fname);
                exit(-1);
        }
        
        for(uint i = 0; i < items.size(); i++) {
                item_t item = items[i];
                fprintf(fp, "%s", itemPrint(&item).c_str());
        }

        fprintf(fp, "\n");
        fclose(fp);
}
