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
        this->table = table;
	int variable = 0;
	int type = 0;
	int x;
	int x1;
	int x2;
	 
	/* dictionary to look up where variable was placed on stack */
	reg.push_back("edi");
	reg.push_back("esi");
	reg.push_back("edx");
	reg.push_back("ecx");
	reg.push_back("r8d");
	reg.push_back("r9d");

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
			len++;
			variable = 0;
		}
                // Quick fix to fix segfault when accessing varCount if function has no args (like int main() )?
                else {
                        varCount.push_back(0);
                }
        }
	printf("%d\n", varCount[0]);
	
	file.open("assembly_output.s");

	for (item_t tmp : IR) {
		if (!tmp.label.empty()) {
			x = (tmp.label).compare("FUNC DECL");
			/*setting up functions*/
			if (x == 0) {
				genFunc(tmp);
			}
			/*setting up variable declaration*/ /* still need to deal with function calls */ /*need negative numbers */
			x = (tmp.label).compare("VAR DECL");
			if (x == 0) {
				genVarDecl(tmp);
			}
			/*set up return statements*/
			x = (tmp.label).compare("RETURN");
			if (x == 0) {
				genReturn(tmp);
			}

			/*set up function calls*/
			x = (tmp.label).compare("FUNCTION CALL");
			if (x == 0) {
				genFuncCall(tmp);
			}

                        x = (tmp.label).compare("IF STATEMENT");
			if (x == 0) {
                                genIfStatement(tmp);
                                
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


void X86::genFunc(item_t tmp) {
        int x1;
        int x2;
        int type;
        if (!tmp.type.empty())
                x1 = (tmp.type).compare("int");
        if (x1 == 0) {
                type = 1;
        }
        /*setting up main function*/
        if (!tmp.id.empty())
                x2 = (tmp.id).compare("main");
        if (x2 == 0) {
                stackVars.clear();
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
                        file << (varCount[len - 1] + 1) * 4;
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
                stackVars.clear();
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
                        /* put passed in variables onto stack */
                        for (i = 0; i < count; i++) {
                                stackVars.insert(std::pair<std::string, int>(dec[i], i + 4));
                                file << "\tmovl " << char(perc) << reg[i] << ", " << -(((varCount[len - 1] + 1) * 4) + (4 * 								inc)) << "(" << char(perc) << "rbp)\n";
                                inc++;
                        }

                } else {
                        std::cout << "Unable to open file";
                }

        }
        
}

void X86::genVarDecl(item_t tmp) {
        int x1;
        int count = 0;
        int count2 = 0;
        std::vector<std::string> dec; 
        std::vector<std::string> var; 
        for (auto test : tmp.params) {
                if (!test.val.empty()) {
                        dec.push_back(test.val); 
                        count++;
                }
        }

        for (auto test : tmp.params) {
                if (!test.id.empty()) {
                        var.push_back(test.id); 
                        count2++;
                }
        }

        /* expressions such as int x = a + b */
        if (count2 == 2) {
                if (file.is_open()) {
                        stackVars.insert(std::pair<std::string, int>(tmp.id, stack));
                        x1 = (dec[0]).compare("+");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "edx\n";
                                file << "\taddl " << char(perc) << "edx" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "edx\n";
                                file << "\tsubl " << char(perc) << "edx" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "edx\n";
                                file << "\timull " << char(perc) << "edx" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tidivl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << "\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                } else {
                        std::cout << "Unable to open file";
                }
                /*basic variable declaration such as int x = 5*/
        } else if (count == 1) {
                if (file.is_open()) {
                        file << "\tmovl $" << dec[0] << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
                        stackVars.insert(std::pair<std::string, int>(tmp.id, stack));
                        stack++;
                } else {
                        std::cout << "Unable to open file";
                }
                /*variable declarations such as int x = 7 + 8 */
        } else if (count == 3) {
                if (file.is_open()) {
                        x1 = (dec[1]).compare("+");
                        stackVars.insert(std::pair<std::string, int>(tmp.id, stack));
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\taddl $" << dec[2] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[1]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tsubl $" << dec[2] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[1]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\timull $" << dec[2] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[1]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tidivl $" << dec[2] << "\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                } else {
                        std::cout << "Unable to open file";
                }
                /*variable declarations such as int x = y + 2 */
        } else if (count == 2) {
                if (file.is_open()) {
                        stackVars.insert(std::pair<std::string, int>(tmp.id, stack));
                        x1 = (dec[1]).compare("+");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\taddl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[1]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tsubl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[1]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\timull $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[1]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl " << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tidivl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << "\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("+");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\taddl $" << dec[1] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tsubl $" << dec[1] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\timull $" << dec[1] << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                        x1 = (dec[0]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tidivl $" << dec[1] << "\n";
                                file << "\tmovl " << char(perc) << "eax" << ", " << stack * -4 << "(" << char(perc) 
                                     << "rbp)\n";
                                stack++;
                        }
                } else {
                        std::cout << "Unable to open file";
                } 
                /* expression such as int x = b */
        } else if (count2 == 1) {
                if (file.is_open()) {
                        file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                             << "rbp)" << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
                        stackVars.insert(std::pair<std::string, int>(tmp.id, stack));
                        stack++;
                } else {
                        std::cout << "Unable to open file";
                }
        }
        
}


void X86::genReturn(item_t tmp) {
        int count = 0;
        int count2 = 0;
        std::vector<std::string> dec; 
        std::vector<std::string> var; 
        for (auto test : tmp.params) {
                if (!test.val.empty()) {
                        dec.push_back(test.val); 
                        count++;
                }
        }

        for (auto test : tmp.params) {
                if (!test.id.empty()) {
                        var.push_back(test.id); 
                        count2++;
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
                /* expression such as return x */
        } else if (count2 == 1) {
                if (file.is_open()) {
                        file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                             << "rbp)" << ", " << char(perc) << "eax\n";
                        file << "\tpopq ";
                        file << char(perc);
                        file <<"rbp\n";
                        file <<"\tret\n";
                } else {
                        std::cout << "Unable to open file";
                }
        }
}

void X86::genFuncCall(item_t tmp) {
        int count = 0;
        int count2 = 0;
        int count3 = 0;
        std::vector<std::string> dec; 
        std::vector<int> flag; 
        for (auto test : tmp.params) {
                if (!test.val.empty()) {
                        dec.push_back(test.val); 
                        flag.push_back(0);
                        count++;
                }
                if (!test.id.empty()) {
                        dec.push_back(test.id); 
                        flag.push_back(1);
                        count2++;
                }
        }

        count3 = count + count2;
        /*function call with 0 params*/
        if (count3 == 0) {
                if (file.is_open()) {
                        file << "\tcall " << tmp.id << "\n";
                } else {
                        std::cout << "Unable to open file";
                }
                /* function call with 1 param */
        } else if (count3 == 1) {
                if (file.is_open()) {
                        /*passed in number */
                        if (count == 1) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "edi\n";
                                /* passed in variable */
                        } else if (count2 == 1) {
                                file << "\tmovl " << stackVars[dec[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "edi\n";
                        }
                        file << "\tcall " << tmp.id << "\n";
                } else {
                        std::cout << "Unable to open file";
                }
                /*function call with 2 to 6 params*/ /* need more than 6 params */
        } else if ((count3 > 1) && (count3 <= 6)) {
                int i = 0;
                if (file.is_open()) {

                        for (i = 0; i < count3; i++) {
                                /* passed in numbers */
                                if (flag[i] == 0) {
                                        file << "\tmovl $" << dec[i] << ", " << char(perc) << reg[i] << "\n";
                                        /* passed in variables */
                                } else if (flag[i] == 1) {
                                        file << "\tmovl " << stackVars[dec[i]] * -4 << "(" << char(perc) 
                                             << "rbp)" << ", " << char(perc) << reg[i] << "\n";
                                }						
                        }
                        file << "\tcall " << tmp.id << "\n";
                } else {
                        std::cout << "Unable to open file";
                }
        }
}

void X86::genIfStatement(item_t tmp) {
        printf("IF STATEMENT\n");

        int count = 0;
        int count2 = 0;
        std::vector<std::string> dec; 
        std::vector<int> flag; 
        for (auto test : tmp.params) {
                printf("PARAMSSSSSS = %s\n", test.label.c_str());
                if (!test.val.empty()) {
                        dec.push_back(test.val); 
                        flag.push_back(0);
                        printf("dec test val = %s\n", test.val.c_str());
                        count++;
                }
                if (!test.id.empty()) {
                        printf("dec test id = %s\n", test.id.c_str());
                        dec.push_back(test.id); 
                        flag.push_back(1);
                        count2++;
                }
        }
                                
        
}
