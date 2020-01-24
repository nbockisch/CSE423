/**
 * @file main.cpp
 * @brief Main driver for compiler
 */

#include <stdio.h>
#include <stdlib.h>

#include "Scanner.h"

int main(int argc, char **argv) {

        Scanner *scanner = new Scanner(argv[1]);

        int size;
        char *charstream = scanner->removeWhitespace(size);

        printf("Size: %d\n", size);
        printf("Charstream:\n");
        printf("'%s'\n", charstream);
        
        delete scanner;
        free(charstream);
}
