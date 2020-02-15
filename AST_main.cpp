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
	char order[3][7] = {"main", "return", "1"};
       	ast->insert(order);

	//ast->insert(7, 3);
	ast->postorder();
        delete ast;
        
        return 0;
}
