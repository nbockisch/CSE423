/**
 * @X86.cpp
 * @builds X86 assembly file
 */

#include "X86.h"

X86::X86() {
        //don't know if this is really necessary
}

X86::~X86() {
        
}

void X86::initVariables(Symtable *table) {
	int variable = 0;
	int varCount = 0;
	for (uint i = 1; i < table->getNumScopes(); i++) {
                for (auto it = table->getScope(i)->begin(); it != table->getScope(i)->end(); ++it) {
			std::string record(table->rtype_str(it->second.rtype).c_str()); 
			int x = record.compare("Variable");
			if (x != 0) {
				break;
			} else if (x == 0) {
				variable = 1;
				break;
			}
                }
		if (variable == 1) {
			varCount = table->getCount(i);
			break;
		}
        }
	int perc = 37;
	std::ofstream file ("assembly_output.s");
  	if (file.is_open()) {
		file << "\t.text\n";
		file << ".globl main\n";
		file << "main:\n";
		file << "\tpushq ";
		file << char(perc);
		file <<"rbp\n";
		file << "\tmovq ";
		file << char(perc);
		file << "rsp, ";
		file << char(perc);
		file <<"rbp\n";
		file << "\tsubq $";
		file << (varCount + 1) * 4;
		file <<", ";
		file << char(perc);
		file << "rbp\n";
		file <<"\tret\n";
		file.close();
  	}
  	else {
		std::cout << "Unable to open file";
	}
}
