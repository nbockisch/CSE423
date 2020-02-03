/**
 * @file parser_main.cpp
 * @brief Main driver for parser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Scanner.h"
#include "Parser.h"

int main(int argc, char **argv) {
        
        Parser *parser = new Parser("grammar.txt");
        int err = parser->loadGrammar();
        if(err != 0) {
                return err;
        }

        parser->printRules();


        delete parser;
        
        return 0;
}
