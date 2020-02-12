/**
 * @file Symbol_Table.h
 * @brief Defines the class used for the symbol table
 **/
#include <stdio.h>

// Symbol types
enum sym_types {
        integer
};

// Data structure for manipulating symbols
struct symbol_t {
        std::string value;
        std::string id;
        enum sym_types type;
};

class Symbol_Table {
public:
        Symbol_Table(string namespace);
};
