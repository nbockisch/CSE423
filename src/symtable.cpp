/**
 * @symtable.cpp
 * @brief Simple implementation of a symbol table that supports multiple scopes.
 */

#include "symtable.h"

Symtable::Symtable() {
        // Create the "root" (global) scope table
        // This probably isnt needed since the tree starts with BLOCK, and a new scope is created
        //  everytime a BLOCK starts..
        //initializeScope();
}

Symtable::~Symtable() {
        
}

/**
 * Returns a pointer to the record object in the symbol table using name as the key
 * @param name The key to search in the table
 * @returns Pointer to record object if found, NULL if record not in table
 */
record_t *Symtable::lookup(std::string name) {

        auto it = tables[cur_table]->find(name);
        if(it == tables[cur_table]->end()) {
                printf("Error: table (%d) lookup  of '%s' failed!\n", cur_table, name.c_str());
                return NULL;
        }

        return &(it->second);
}

/**
 * Stores the given record in the symbol table with name as its key.
 * @param name The key used to store record
 * @param record The symbol record to store in the table
 * @returns 0 on success, -1 on error
 */
int Symtable::insert(std::string name, record_t record) {

        // Check if name already exists in the table
        auto check = tables[cur_table]->find(name);
        if(check != tables[cur_table]->end()) {
                // Name already exists in table, so throw error
                printf("Error: name '%s' already exists in symbol table (%d).\n", name.c_str(), cur_table);
                return -1;
        }

        // Insert the record and check for success
        bool success = tables[cur_table]->insert(std::make_pair(name, record)).second;
        if(success) {
                //printf("-- Inserted name '%s' into table (%d)!\n", name.c_str(), cur_table);
                return 0;
        }
        
        printf("Error: error inserting name '%s' into table.\n", name.c_str());
        
        return -1;
}

/**
 * Creates a new table for a new scope. lookup and insert will work on this table now.
 */
void Symtable::initializeScope() {
        std::unordered_map<std::string, record_t> *root = new std::unordered_map<std::string, record_t>();
        tables.push_back(root);

        // Save a pointer to the previous scope
        this->prev_table = this->cur_table;
        this->cur_table = tables.size()-1;
}

/**
 * Sets the active table to the previous scope
 */
void Symtable::finalizeScope() {
        // Check if we are at the root level
        if(this->cur_table == 0) {
                //printf("Error: Symbol table can't finalize scope since it is already on root scope.\n");
                return;
        }
        this->cur_table = this->prev_table;
        this->prev_table = this->cur_table - 1;
}

/**
 * Prints every record for each scope/table
 */
void Symtable::print() {
        for (uint i = 0; i < tables.size(); i++) {
                printf("=== Scope %d ===\n", i);
                for (auto it = tables[i]->begin(); it != tables[i]->end(); ++it) {
                        printf("  '%s'\n", it->first.c_str());
                        printf("\tRecord Type: %s\n", rtype_str(it->second.rtype).c_str());
                        printf("\tType: %s\n", it->second.type.c_str());
                }
                printf("\n");
        }
}

std::string Symtable::rtype_str(record_type type) {
        if(type == record_type::variable) {
                return std::string("Variable");
        } else if(type == record_type::function) {
                return std::string("Function");
        } else if(type == record_type::funcarg) {
                return std::string("Function Argument");
        } else if(type == record_type::label) {
                return std::string("Label");
        } else {
                return std::string("");
        }
}
