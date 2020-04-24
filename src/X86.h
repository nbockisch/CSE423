/**
 * @X86.h
 * @defines class to build x86 assembly file
 */

#ifndef X86_H
#define X86_H

#include <stdio.h>
#include <iostream> 
#include <string>
#include "symtable.h"
#include "node.h"
#include <fstream>

class X86 {

public:
        X86();
        ~X86();
  
        void initVariables(Symtable *table);

};

#endif
