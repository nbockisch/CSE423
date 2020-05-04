/**
 * @X86.h
 * @defines class to build x86 assembly file
 */

#ifndef X86_H
#define X86_H

#include <stdio.h>
#include <iostream> 
#include <string>
#include<map>
#include "symtable.h"
#include "node.h"
#include <fstream>
#include "ir.h"

class X86 {

public:
        X86();
        ~X86();
  
        void initVariables(Symtable *table, std::vector<item_t> IR);


        void generate(std::vector<item_t> IR);
        
        void genFunc(item_t tmp);
        void genVarDecl(item_t tmp);
        void genReturn(item_t tmp);
        void genFuncCall(item_t tmp);
        int genIfStatement(item_t tmp);
	void genBreakStatement(item_t tmp);


        std::string getJumpInstr(std::string op);

private:
        Symtable *table;
        std::ofstream file;
        std::vector<std::string> reg;
        std::map<std::string, int> stackVars;
        std::vector<int> varCount;
        std::vector<std::string> ifs; //Holds labels of all if statements (format: .IF#)
        int stack = 1;
        int perc = 37;
	int len = 0;

};

#endif
