# CSE423 Compiler
## Group Members:
* Eva Domschott (spiritofthegael)
* Brandon Bicknell (Bicknell125)
* Coleman Kendrick (ckendrick)
* Nathan Bockisch (nbockisch)

## Project Structure
* src - The folder holding the source code for the project. ([more info](docs/src.md))
* test - The folder holding the C source files to test the compiler with. ([more info](docs/test.md))

## Building
The project is compiled using `gcc` and a `Makefile`. Ensure both `gcc` (or another compiler bound to the `gcc` command), and `make` are installed on your system. Then simply do the following:
1. `cd src`
2. `make`

## Usage
`./compiler -s -p -t -f <source file> -o <ir file>`  
`-s`: Print the symbol table
`-i`: Print the IR
`-p`: Print the parse tree  
`-t`: Print the tokens  
`-f <source file>`: Pass in a source file as an argument  
`-o <ir file>`: Pass in an ir file as an argument

## Design Decisions and Implementation
### Lexer
The lexer was implemented with Flex due to time considerations.

[tokens for sample4 in test folder](docs/tokens.txt) 

### Parser
The parser was implemented with Bison due to time considerations.

Checklist of required features for the Parser:
- [x] Identifiers, variables, functions
- [x] Keywords
- [x] Arithmetic expressions
- [x] Assignment
- [x] Boolean expressions
- [ ] Goto statements
- [x] If / Else control flow
- [ ] Unary operators
- [x] Return statements
- [ ] Break statements
- [x] While loops

Checklist of optional features for the parser:
- [x] Types other than integers (supports double for numbers and void for functions)
- [ ] binary operators
- [ ] for loops
- [ ] switch statements
- [ ] ++, —, -=, +=, *=, /=

Sample of a printed parse tree: ([parse tree for sample4 in test folder](docs/parsetree.txt)) 

### Symbol Table



### IR
To be added

## Supported Features
To be added
