/**
 * @symtable.h
 * @brief Simple implementation of a symbol table that supports multiple scopes.
 */

#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_map>

#include "node.h"

// Defines the type of record in the symbol table
enum record_type {
        variable, function, funcarg, label
};

// Holds any necessary information for a record in the symbol table
struct record_t {
        std::string name;
  
        record_type rtype; // What kind of record this is
        std::string type; // Type (int, void, etc)

        const Node *node; // Pointer to the object in the AST
};

class Symtable {

public:
        Symtable();
        ~Symtable();

        record_t *lookup(std::string name);
        int insert(std::string name, record_t record);
  
        void initializeScope();
        void finalizeScope();

        void print();

private:
        std::string rtype_str(record_type type);
        
        std::vector<std::unordered_map<std::string, record_t>*> tables;
        
        int prev_table = -1; //Holds index of prev table, probably not needed..
        int cur_table = -1;
};

#endif
