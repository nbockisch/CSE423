#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include "node.h"

extern NBlock* root;
extern int yyparse();
extern int p_tokens;

int main(int argc, char **argv)
{
    int opt;
    p_tokens = 0;
    int p_tree = 0;
    std::string fname;

    while ((opt = getopt(argc, argv,  ":itf:ax"))  != -1) {
        switch(opt) {
            case 'f':
                // get filename and open file
                yyin = fopen(optarg, "r");

                yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
                std::cout << fname << std::endl;
            case 'i':
                // print out tokens 
                p_tokens = 1;
                break;
            case 't':
                // print out the tree
                p_tree = 1;
                break;
        }
    }

    yyparse();
    //std::cout << root << std::endl;

    if (p_tree) {
        std::string tree = root->print(0);
        printf("%s\n", tree.c_str());
    }
    
    return 0;
}


