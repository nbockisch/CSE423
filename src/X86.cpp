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
	 
	/* registers used for param passing */
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
			printf("%d\n", table->getCount(i));
			len++;
			variable = 0;
		} 
                
        }

	file.open("assembly_output.s");


        // changed loop to this way so we can skip over items that have already been processed
        for(int i = 0; i < IR.size(); i++) {
                item_t tmp = IR[i];
                        //for (item_t tmp : IR) {
		if (!tmp.label.empty()) {
			x = (tmp.label).compare("FUNC DECL");
			/*setting up functions*/
			if (x == 0) {
				genFunc(tmp);
			}
			/*setting up variable declaration*/ /* still need to deal with function calls */
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
			/* set up if statements */
                        x = (tmp.label).compare("IF STATEMENT");
			if (x == 0) {
                                int hasElse = 0;
                                item_t *elseb = NULL;
                                if(IR.size() > i+1) {
                                        
                                
                                        //        elseb = &(IR[i+2]);
                                        //        if(!elseb->label.empty())

                                        for(int j = i+1; j < IR.size(); j++) {
                                                if(!IR[j].label.compare("IF STATEMENT")) {
                                                        //Stop if we hit another if
                                                        break;
                                                }
                                                if(!IR[j].label.compare("ELSE STATEMENT")) {
                                                        //Stop when we hit an else
                                                        hasElse = 1;
                                                        elseb = &IR[j];
                                                        break;
                                                }
                                        }
                                
                                        /*
                                        if(!elseb->label.compare("ELSE STATEMENT"))  {
                                                hasElse = 1;
                                                printf("potential else label '%s'\n", elseb->label.c_str());
                                                printf("detected else\n");
                                        }
                                        */
                                }
                                
                                // This call returns an int to skip over the next item_t's so that this loop doesn't double-process them.
                                if(!hasElse) {
                                        i+=genIfStatement(tmp, NULL);
                                } else {
                                        i+=genIfStatement(tmp, elseb);
                                }
                                
                        }
			/* set up break statements */
			x = (tmp.label).compare("BREAK");
			if (x == 0) {
                                genBreakStatement(tmp);
                                
                        }

			/* set up goto blocks */
			x = (tmp.label).compare("GOTO BLOCK");
			if (x == 0) {
                                genGoToBlock(tmp);
                                
                        }
			
			/* set up goto */
			x = (tmp.label).compare("GOTO");
			if (x == 0) {
                                genGoTo(tmp);
                                
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
		     int i;
		     std::cout << "Param Label: " << test.label << "\n";
		     for (auto test2 : test.params) {
		     	std::cout << "Param ID: " << test2.id << "\n";
			std::cout << "Param Val: " << test2.val << "\n";
		       // std::cout << "Param var: " << tes2.val << "\n";
		     }
		}
		for (auto test : tmp.params) {
		     std::cout << "Param ID: " << test.id << "\n";
		}
		std::cout << std::endl;
	}
	file.close();
}

/**
 * This function is needed when a inner block is hit (like an if statement block)
 * Since initVars setups up the stack and things, this one should just generate instrs
 * for a small subset of item_t's.
 */
void X86::generate(std::vector<item_t> IR) {
        int x;
        //Function processes a block
        for (item_t tmp : IR) {
		if (!tmp.label.empty()) {
                        x = (tmp.label).compare("BLOCK END");
                        if(x == 0) {
                                //printf("HIT END BLOCK -- RETURNING FROM BLOCK GEN\n");
                                return;
                        }
                        
			x = (tmp.label).compare("FUNC DECL");
			/*setting up functions*/
			if (x == 0) {
				genFunc(tmp);
			}
			/*setting up variable declaration*/
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
                                genIfStatement(tmp, NULL);
                        }

                        /* set up break statements */
			x = (tmp.label).compare("BREAK");
			if (x == 0) {
                                genBreakStatement(tmp);
                                
                        }

			/* set up goto blocks */
			x = (tmp.label).compare("GOTO BLOCK");
			if (x == 0) {
                                genGoToBlock(tmp);
                                
                        }
			
			/* set up goto */
			x = (tmp.label).compare("GOTO");
			if (x == 0) {
                                genGoTo(tmp);
                                
                        }	
		}
	}
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
			if (len != 0) {
		                file << "\tsubq $";
		                file << (varCount[len - 1] + 1) * 4;
		                file <<", ";
		                file << char(perc);
		                file << "rbp\n";
			}
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
			int inc2 = 0;
                        for (i = 0; i < count; i++) {
				if (i < 6) {
		                        stackVars.insert(std::pair<std::string, int>(dec[i], i + 4));
					if (len != 0) {
				                file << "\tmovl " << char(perc) << reg[i] << ", " << -(((varCount[len - 1] + 1) * 4) + (4 * 								inc)) << "(" << char(perc) << "rbp)\n";
				                inc++;
					} else if (len == 0) {
						file << "\tmovl " << char(perc) << reg[i] << ", " << stack * -4 << "(" << char(perc) << "rbp)\n";
						stack++;
					}
				} else if (i > 5) {
					stackVars.insert(std::pair<std::string, int>(dec[i], 16 + (8 * inc2)));
					inc++;
				}
                        }

                } else {
                        std::cout << "Unable to open file";
                }

        }
        
}

void X86::genBreakStatement(item_t tmp) {
	if (file.is_open()) {
		file << "\tjmp .L2\n";
		file << ".L2:\n";
        } else {
                std::cout << "Unable to open file";
        }
}

void X86::genGoToBlock(item_t tmp) {
	if (file.is_open()) {
		file << "." << tmp.val << ":\n";
        } else {
                std::cout << "Unable to open file";
        }
}

void X86::genGoTo(item_t tmp) {
	if (file.is_open()) {
		file << "\tjmp " << "." << tmp.val << "\n";
        } else {
                std::cout << "Unable to open file";
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
	int x1;
        std::vector<std::string> dec; 
        std::vector<std::string> var; 
        for (auto test : tmp.params) {
                if (!test.val.empty()) {
                        dec.push_back(test.val); 
                        count++;
                }
		for (auto test2 : test.params) {
			if (!test2.val.empty()) {
		                dec.push_back(test2.val); 
		                count++;
		        }
		}
        }

        for (auto test : tmp.params) {
                if (!test.id.empty()) {
                        var.push_back(test.id); 
                        count2++;
                }
		for (auto test2 : test.params) {
			if (!test2.id.empty()) {
		                var.push_back(test2.id); 
		                count2++;
		        }
		}
        }
	/* expression such as return a + b */
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
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "edx\n";
                                file << "\tsubl " << char(perc) << "edx" << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tmovl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "edx\n";
                                file << "\timull " << char(perc) << "edx" << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tidivl " << stackVars[var[1]] * -4 << "(" << char(perc) 
                                     << "rbp)" << "\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                } else {
                        std::cout << "Unable to open file";
                }
                /*basic return statement with no complex expression such as return 0*/
        } else if (count == 1) {
                if (file.is_open()) {
                        file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                        file << "\tpopq ";
                        file << char(perc);
                        file <<"rbp\n";
                        file <<"\tret\n";
                } else {
                        std::cout << "Unable to open file";
                }
                /*expression such as return 7 + 8 */
        }  else if (count == 3) {
                if (file.is_open()) {
                        x1 = (dec[1]).compare("+");
                        
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\taddl $" << dec[2] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[1]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tsubl $" << dec[2] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[1]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\timull $" << dec[2] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[1]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tidivl $" << dec[2] << "\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                } else {
                        std::cout << "Unable to open file";
                }
                /*expression such as return y + 2 */
        } else if (count == 2) {
                if (file.is_open()) {
                        x1 = (dec[1]).compare("+");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\taddl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[1]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tsubl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[1]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\timull $" << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[1]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl " << dec[0] << ", " << char(perc) << "eax\n";
                                file << "\tidivl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << "\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("+");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\taddl $" << dec[1] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("-");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tsubl $" << dec[1] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("*");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\timull $" << dec[1] << ", " << char(perc) << "eax\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
                        x1 = (dec[0]).compare("/");
                        if (x1 == 0) {
                                file << "\tmovl " << stackVars[var[0]] * -4 << "(" << char(perc) 
                                     << "rbp)" << ", " << char(perc) << "eax\n";
                                file << "\tidivl $" << dec[1] << "\n";
                                file << "\tpopq ";
		                file << char(perc);
		                file <<"rbp\n";
		                file <<"\tret\n";
                        }
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
                /*function call with 2 or more params*/ 
        } else if (count3 > 1) {
                int i = 0;
                if (file.is_open()) {
			int pushed = 0;
                        for (i = 0; i < count3; i++) {
				/* for more than six params push onto stack */
				if (i > 5) {
					if (flag[i] == 0) {
						file << "\tpushq $" << dec[i] << "\n";
					} else if (flag[i] == 1) {
						file << "\tpushq " << stackVars[dec[i]] * -4 << "(" << char(perc) 
                                             	<< "rbp)" << "\n";
					}
					pushed++;
					/*pass in numbers*/
				} else if (flag[i] == 0) {
                                        file << "\tmovl $" << dec[i] << ", " << char(perc) << reg[i] << "\n";
                                        /* passed in variables */
                                } else if (flag[i] == 1) {
                                        file << "\tmovl " << stackVars[dec[i]] * -4 << "(" << char(perc) 
                                             << "rbp)" << ", " << char(perc) << reg[i] << "\n";
                                }						
                        }
                        file << "\tcall " << tmp.id << "\n";
			/* if params were pushed onto stack */
			if (i > 5) {
				file << "\taddq $" << (pushed * 8) << ", " << char(perc) << "rsp" << "\n";

			}
                } else {
                        std::cout << "Unable to open file";
                }
        }
}

int X86::genIfStatement(item_t tmp, item_t *elseb) {
        std::vector<std::string> vars; 
        std::vector<std::string> literals;
        std::vector<item_t> ifblock;
        std::vector<item_t> elseblock;
        std::string op;
        std::string instr = std::string("");
        int hasconditional = 0;
       
        for (auto test : tmp.params) {
                //printf("IF --- test.label = %s\n", test.label.c_str());
                if(!test.label.compare("BIN OP")) {
                        for (auto expr : test.params) {

                                // printf("SUB PARAM %s\n", expr.label.c_str());

                                if (!expr.label.compare("OP")) {
                                        op = expr.val;
                                        continue;
                                }
                                
                                if (!expr.val.empty()) {
                                        literals.push_back(expr.val);
                                }
                                if (!expr.id.empty()) {
                                        vars.push_back(expr.id); 
                                }
                        }
                        
                        // compare literal value with the value on the stack
                        file << "\tcmpl $" << literals[0] << ", " << stackVars[vars[0]] * -4 << "(" << char(perc) << "rbp)\n";

                        hasconditional = 1;
                } else if(!test.label.compare("IDENTIFIER")) {

                        //printf("ident.id = %s\n", test.id.c_str());

                        // Statements like "if (x)" should just resolve to cmpl $0 x, jne.
                        //printf("stack vars:\n");
                        std::cout << stackVars[test.id];

                        // compare implied literal with the value on the stack
                        file << "\tcmpl $0, " << stackVars[test.id] * -4 << "(" << char(perc) << "rbp)\n";
                                                
                        hasconditional = 1;
                        
                } else {
                        if(!hasconditional) {
                                printf("Error - unrecognized if statement condition '%s'\n", test.label.c_str());
                                exit(-1);
                        }

                        /* This should be a BLOCK now */
                        std::string else_lab;
                        if(elseb != NULL) {
                                if(ifs.empty()) {
                                        else_lab = std::string(".IF0");
                                } else {
                                        else_lab = std::string(".IF"+std::to_string(ifs.size()));
                                }
                                ifs.push_back(else_lab);
                        }
                       
                        
                        // Set up the IF statement label
                        std::string if_lab;
                        if(ifs.empty()) {
                                if_lab = std::string(".IF0");
                        } else {
                                if_lab = std::string(".IF"+std::to_string(ifs.size()));
                        }
                        //printf("IF LABEL: '%s'\n", if_lab.c_str());
                        ifs.push_back(if_lab);


                        // Figure which jump op to use based on operator
                        std::string jump = getJumpInstr(op);

                        if(elseb != NULL) {
                                file << "\t" << jump << " " << ifs[ifs.size()-2] << "\n";
                        } else {
                                file << "\t" << jump << " " << ifs[ifs.size()-1] << "\n";
                        }
                        // Generate instructions for rest of the if block here
                        if(!test.label.compare("BLOCK")) {
                                
                                for(auto subitem : test.params) {
                                        //printf(" --------> Appending subitem label '%s' to ifblock\n", subitem.label.c_str());
                                        ifblock.push_back(subitem);
                                }

                                //printf("CALLING IF BLOCK SUB GENERATION\n");
                                generate(ifblock);
                        }

                        if(elseb != NULL) {
                                file << "\tjmp " << ifs[ifs.size()-1] << "\n";

                                // Ending label to jump to if the statement was false
                                file << ifs[ifs.size()-2] << ":\n";
                                
                                if(!elseb->params[0].label.compare("BLOCK")) {

                                        //
                                        for(auto subitem : elseb->params[0].params) {
                                                //printf(" --------> Appending subitem label '%s' to ifblock\n", subitem.label.c_str());
                                                elseblock.push_back(subitem);
                                        }
                                        
                                        //printf("CALLING ELSE BLOCK SUB GENERATION\n");
                                        generate(elseblock);
                                }
                        }

                        

                        // Ending label to jump to if the statement was false
                        file << ifs[ifs.size()-1] << ":\n";
                
                }
        }

        // Return number of item_t's to skip so the block items dont get duplicated after this function
        int nskip = ifblock.size() + 1;
        if(elseb!=NULL) {
                nskip += elseblock.size();
        }
        
        return nskip;
                
}

/**
 * Based on the operation, return corresponding X86 opposite jump instr (i.e for skipping over if statement blocks, etc)
 */
std::string X86::getJumpInstr(std::string op) {
        std::string compinstr;
        if(!op.compare("==")) {
                compinstr = std::string("jne");
        } else if(!op.compare(">")) {
                compinstr = std::string("jle");
        } else if(!op.compare(">=")) {
                compinstr = std::string("js");
        } else if(!op.compare("<")) {
                compinstr = std::string("jns");
        } else if(!op.compare("<=")) {
                compinstr = std::string("jg");
        } else {
                compinstr = std::string("je");
        }
        return compinstr;
}
