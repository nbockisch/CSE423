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

void X86::initVariables(Symtable *table, std::vector<item_t> IR) {
	int variable = 0;
	int varCount = 0;
	int type = 0;
	int stack = 1;
	int x;
	int x1;
	int x2;
	int perc = 37;
	for (uint i = 1; i < table->getNumScopes(); i++) {
                for (auto it = table->getScope(i)->begin(); it != table->getScope(i)->end(); ++it) {
			std::string record(table->rtype_str(it->second.rtype).c_str()); 
			x = record.compare("Variable");
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
	
	std::ofstream file ("assembly_output.s");

	for (item_t tmp : IR) {
		if (!tmp.label.empty()) {
			x = (tmp.label).compare("FUNC DECL");
			/*setting up functions*/
			if (x == 0) {
				if (!tmp.type.empty())
					x1 = (tmp.type).compare("int");
				if (x1 == 0) {
					type = 1;
				}
				/*setting up main function*/
				if (!tmp.id.empty())
					x2 = (tmp.id).compare("main");
				if (x2 == 0) {
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
				  	} else {
						std::cout << "Unable to open file";
					}
				}
			}
			/*setting up variable declaration*/
			x = (tmp.label).compare("VAR DECL");
			if (x == 0) {
				int count = 0;
				std::vector<std::string> dec; 
				for (auto test : tmp.params) {
					if (!test.val.empty()) {
						dec.push_back(test.val); 
						count++;
					}
				}
				/*basic variable declaration such as int x = 5*/
				if (count == 1) {
					if (file.is_open()) {
						file << "\tmovl $" << dec[0] << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
						stack++;
					} else {
						std::cout << "Unable to open file";
					}
				/*variable declarations such as int x = 7 + 8 */
				} else if (count == 3) {
					if (file.is_open()) {
						x1 = (dec[1]).compare("+");
						if (x1 == 0) {
							file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
							file << "\taddl $" << dec[2] << ", " << char(perc) << "eax\n";
							file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
							stack++;
						}
						x1 = (dec[1]).compare("-");
						if (x1 == 0) {
							file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
							file << "\tsubl $" << dec[2] << ", " << char(perc) << "eax\n";
							file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
							stack++;
						}
						x1 = (dec[1]).compare("*");
						if (x1 == 0) {
							file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
							file << "\timull $" << dec[2] << ", " << char(perc) << "eax\n";
							file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
							stack++;
						}
					} else {
						std::cout << "Unable to open file";
					}
				}
			}
			/*set up return statements*/
			x = (tmp.label).compare("RETURN");
			if (x == 0) {
				int count = 0;
				std::vector<std::string> dec; 
				for (auto test : tmp.params) {
					if (!test.val.empty()) {
						dec.push_back(test.val); 
						count++;
					}
				}
				/*basic return statement with no complex expression such as return 0*/
				if (count == 1) {
					if (file.is_open()) {
						file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
						file << "\tpopq ";
						file << char(perc);
						file <<"rbp\n";
						file <<"\tret\n";
					} else {
						std::cout << "Unable to open file";
					}

				}
			}
		}
	}

	for (item_t tmp : IR) {
		if (!tmp.label.empty()) {
		    std::cout << "Label: " << tmp.label << "\n";
		}
		if (!tmp.id.empty()) {
		    std::cout << "ID: " << tmp.id << "\n";
		}
		if (!tmp.type.empty()) {
		    std::cout << "Type: " << tmp.type << "\n";
		}
		if (!tmp.val.empty()) {
		    std::cout << "Value: " << tmp.val << "\n";
		}
		for (auto test : tmp.params) {
		     std::cout << "Param Value: " << test.val << "\n";
		}
		for (auto test : tmp.params) {
		     std::cout << "Param ID: " << test.id << "\n";
		}
		std::cout << std::endl;
	}
	file.close();
}
