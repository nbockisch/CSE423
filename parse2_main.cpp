#include <iostream>
#include <unistd.h>
#include "node.h"

extern NBlock* root;
extern int yyparse();
extern int p_tokens;

int main(int argc, char **argv)
{
    int opt;
    p_tokens = 0;

    while ((opt = getopt(argc, argv,  ":if:ax"))  != -1) {
        switch(opt) {
            case 'i':
                /* print out tokens */
                p_tokens = 1;
                break;
        }
    }
    if (p_tokens) {
        printf("Print tokens\n");
    }
	yyparse();
	std::cout << root << std::endl;

	return 0;
}


