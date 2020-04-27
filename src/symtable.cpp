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
 * Returns a pointer to the record object in the current symbol table scope using name as the key
 * @param name The key to search in the table
 * @returns Pointer to record object if found, NULL if record not in table
 */
record_t *Symtable::lookup(std::string name) {
        if(cur_table < 0) {
                initializeScope();
        }
        if(!tables[cur_table]->empty()) {
                auto it = tables[cur_table]->find(name);
                if(it == tables[cur_table]->end()) {
                        printf("Error: table (%d) lookup  of '%s' failed!\n", cur_table, name.c_str());
                        return NULL;
                }

                return &(it->second);
        }
        return NULL;
}

/**
 * Returns a pointer to the record object in the specified symbol table scope using name as the key
 * @param name The key to search in the table
 * @param scope The scope index in which to search for name
 * @returns Pointer to record object if found, NULL if record not in table
 */
record_t *Symtable::lookup(std::string name, int scope) {
        if(cur_table < 0) {
                initializeScope();
        }
        if(!tables[cur_table]->empty()) {
                auto it = tables[scope]->find(name);
                if(it == tables[scope]->end()) {
                        printf("Error: table (%d) lookup  of '%s' failed!\n", scope, name.c_str());
                        return NULL;
                }

                return &(it->second);
        }
        return NULL;
}

/**
 * Stores the given record in the current symbol table scope with name as its key.
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
 * Stores the given record in the specified symbol table scope with name as its key.
 * @param name The key used to store record
 * @param record The symbol record to store in the table
 * @returns 0 on success, -1 on error
 */
int Symtable::insert(std::string name, record_t record, int scope) {

        // Check if name already exists in the table
        auto check = tables[scope]->find(name);
        if(check != tables[scope]->end()) {
                // Name already exists in table, so throw error
                printf("Error: name '%s' already exists in symbol table (%d).\n", name.c_str(), scope);
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
        table_t *root = new table_t();
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
 * Returns the number of elements in the current symtable scope.
 */
int Symtable::getCurCount() {
        return this->tables[this->cur_table]->size();
}

/**
 * Returns the number of elements in a specific symtable scope
 */
int Symtable::getCount(int scope) {
        return this->tables[scope]->size();
}

/**
 * Returns the total number of scopes within the symtable
 */
int Symtable::getNumScopes() {
        return this->tables.size();
}

/**
 * Return the hash map of the specified scope
 */
table_t *Symtable::getScope(int scope) {
        return this->tables[scope];
}

/**
 * Prints every record for each scope/table
 */
void Symtable::print() {
        for (uint i = 0; i < tables.size(); i++) {
                printf("=== Scope %d (%d entries) ===\n", i, this->getCount(i));
                for (auto it = tables[i]->begin(); it != tables[i]->end(); ++it) {
                        printf("  '%s'\n", it->first.c_str());
                        printf("\tRecord Type: %s\n", rtype_str(it->second.rtype).c_str());
                        printf("\tType: %s\n", it->second.type.c_str());
                }
                printf("\n");
        }
}

/**
 * Returns a string version of a record type
 */
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
