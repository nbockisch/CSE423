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
	std::vector<int> varCount; 
	int type = 0;
	int stack = 1;
	int x;
	int x1;
	int x2;
	int perc = 37;
	std::vector<std::string> reg; 
	reg.push_back("edi");
	reg.push_back("esi");
	reg.push_back("edx");
	reg.push_back("ecx");
	reg.push_back("r8");
	reg.push_back("r9");

	int functions = table->getCount(0);

	/*count the number of variables for each function to set up space on stack*/
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
			varCount.push_back(table->getCount(i));
			variable = 0;
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
						stack = 1;
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
						file << (varCount[0] + 1) * 4;
						file <<", ";
						file << char(perc);
						file << "rbp\n";
				  	} else {
						std::cout << "Unable to open file";
					}
				/* other functions aside from main */
				} else if (x2 != 0) {
					int count = 0;
					std::vector<std::string> dec; 
					for (auto test : tmp.params) {
						if (!test.id.empty()) {
							dec.push_back(test.id); 
							count++;
						}
					}
					if (file.is_open()) {
						int i;
						int inc = 1;
						stack = 1;
						file << "\t.text\n";
						file << ".globl " << tmp.id << "\n";
						file << tmp.id << ":" << "\n";
						file << "\tpushq ";
						file << char(perc);
						file <<"rbp\n";
						file << "\tmovq ";
						file << char(perc);
						file << "rsp, ";
						file << char(perc);
						file <<"rbp\n";
						for (i = 0; i < count; i++) {
							file << "\tmovl " << char(perc) << reg[i] << ", " << -(((varCount[0] + 1) * 4) + (4 * 								inc)) << "(" << char(perc) << "rbp)\n";
							inc++;
						}
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

			/*set up function calls*/
			x = (tmp.label).compare("FUNCTION CALL");
			if (x == 0) {
				int count = 0;
				std::vector<std::string> dec; 
				for (auto test : tmp.params) {
					if (!test.val.empty()) {
						dec.push_back(test.val); 
						count++;
					}
				}
				/*function call with 0 params*/
				if (count == 0) {
					if (file.is_open()) {
						file << "\tcall " << tmp.id << "\n";
					} else {
						std::cout << "Unable to open file";
					}
				/* function call with 1 param */
				} else if (count == 1) {
					if (file.is_open()) {
						file << "\tmovl $" << dec[0] << ", " << char(perc) << "edi\n";
						file << "\tcall " << tmp.id << "\n";
					} else {
						std::cout << "Unable to open file";
					}
				} else if ((count > 1) && (count <= 6)) {
					int i = 0;
					if (file.is_open()) {
						for (i = 0; i < count; i++) {
							file << "\tmovl $" << dec[i] << ", " << char(perc) << reg[i] << "\n";
						}
						file << "\tcall " << tmp.id << "\n";
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
