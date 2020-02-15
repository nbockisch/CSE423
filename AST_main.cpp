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
	char const *order[3] = {"main", "return", "1"};
       	ast->insert(order);

	//ast->insert(7, 3);
	printf("Post order traversal of AST:\n");
	ast->postorder();
        delete ast;
        
        return 0;
}
