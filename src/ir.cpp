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
#include <fstream>
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
/*
int const_fold(item_t* block)
{
    val = 0;
    for (item_t i: block->params) {
    }
    return val;
}

int const_prop(item_t* block)
{
    val = 0;
    for (item_t i: block->params) {
    }
    return val;
}

void optimization_1(std::vector<item_t> list)
{
    for (item_t i: list) {
        if (i.label == "BLOCK") {
            int f,p = 0;
            while (f || p) {
                f = const_fold(&i);
                p = const_prop(&i);
            }
        }
    }
}
*/
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

/**
 * Helper function to print IR contents in the correct format
 * @param item the item_t item to be printed
 * @param level the level of the tree the item is to be printed at
 * @return a string with the contents to be printed
 **/
std::string ir::itemPrint(item_t *item, int level) {
        std::string out;

        out.append(std::to_string(level));
        out.append(",");
        out.append(item->label);
        out.append(",");
        out.append(item->type);
        out.append(",");
        out.append(item->id);
        out.append(",");
        out.append(item->val);
        out.append(",");
        out.append("\n");
        for (item_t i : item->params) {
            out.append(itemPrint(&i, level + 1));
        }
        return out;
}

/**
 * Print the IR
 * @param items the list of ir items to print
 * @return A string with the printable IR
 **/
std::string ir::printIR(std::vector<item_t> items) {
        std::string out;
        
        for(uint i = 0; i < items.size(); i++) {
                item_t item = items[i];
                
                out.append(itemPrint(&item, 0));
        }

        return out;
        
}

/**
 * Write the IR to a file
 * @param fname the name of the file to write the IR to
 * @param items the list of item_t objects to be written to a file
 **/
void ir::writeIR(std::string fname, std::vector<item_t> items) {
        FILE *fp = fopen(fname.c_str(), "w");
        if(fp == NULL) {
                printf("Error: Cannot open file '%s' to write IR.\n", fname);
                exit(-1);
        }
        
        for(uint i = 0; i < items.size(); i++) {
                item_t item = items[i];
                fprintf(fp, "%s", itemPrint(&item, 0).c_str());
        }

        fprintf(fp, "\n");
        fclose(fp);
}

/**
 * Recursive helper function to put IR file contents in a tree
 * @param i the index of where in the IR file list processing is at
 * @param ir the list of IR file contents
 * @return an item_t vector with the IR elements on that level of the tree
 **/
std::vector<item_t> traverseIrFile(int i, std::vector<std::vector<std::string>> ir) {
    int level = atoi(ir[i][0].c_str());
    std::vector<item_t> write_out;
    std::vector<item_t> tmp;


    for (; i < ir.size() - 2; i++) {
        if (atoi(ir[i][0].c_str()) < level) {
            return write_out;
        }

        item_t tmp_i;
        for (int j = 1; j < ir[i].size(); j++) {
            switch (j)
            {
                case 1:
                    tmp_i.label = ir[i][j];
                    break;
                case 2:
                    tmp_i.type = ir[i][j];
                    break;
                case 3:
                    tmp_i.id = ir[i][j];
                    break;
                case 4:
                    tmp_i.val = ir[i][j];
                    break;
            };
        }
        if (atoi(ir[i + 1][0].c_str()) > level) {
            tmp = traverseIrFile(i + 1, ir);   
            i += tmp.size() + 1;
        }
        for (item_t i : tmp) {
            tmp_i.params.push_back(i);
        }
        //std::cout << "Got i: " << i << std::endl;

        write_out.push_back(tmp_i);
        std::cout << "i: " << i << ", label: " << tmp_i.label << ", level: " << level << std::endl;
    }

    return write_out;
}

/**
 * Reads in an IR file
 * @param fname a string with the IR file name
 * @return a vector of item_t structs with the IR
 **/
std::vector<item_t> ir::readIR(std::string fname) {
        std::string line;
        std::ifstream in(fname);
        std::vector<std::vector<std::string>> ir;
        std::vector<item_t> rep;

        while (std::getline(in, line)) {
            /* Split each line of IR file with comma */
            std::vector<std::string> parts;
            std::stringstream ss(line);
            std::string part;
            while(std::getline(ss, part, ',')) {
                parts.push_back(part);
            }
            ir.push_back(parts);
        }

        return traverseIrFile(0, ir);
}
