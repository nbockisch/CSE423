/**
 * @file AST_main.cpp
 * @brief Main driver for AST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "AST.h"

int main(int argc, char **argv) {
        AST *ast = new AST();
       	ast->insert(2, 0);
	ast->insert(3, 1);
	ast->insert(5, 1);
	ast->insert(6, 2);
	//ast->insert(7, 3);
	ast->postorder();
        delete ast;
        
        return 0;
}
