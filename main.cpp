/**
 * @file main.cpp
 * @brief Main driver for compiler
 */

#include <stdio.h>
#include <stdlib.h>

#include "Scanner.h"

int main(int argc, char **argv) {

        Scanner *scanner = new Scanner(argv[1]);
	struct token_t *tokens = NULL;

        int size;
        char *charstream = scanner->removeWhitespace(size);

        /* printf("Size: %d\n", size);
        printf("Charstream:\n");
        printf("'%s'\n", charstream); */

	tokens = scanner->tokenize(charstream, size);
        
        delete scanner;
        free(charstream);
	free(tokens);
}
