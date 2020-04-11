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

There are some compilation warnings that pop up from other things that are being worked on but it should have no effect on anything that has been documented to be supported shown down below. 

## Usage
`./compiler -s -p -t -r <ir file> -f <source file> -o <output file>`  
`-s`: Print the symbol table  
`-i`: Print the IR  
`-p`: Print the parse tree  
`-t`: Print the tokens  
`-r <ir file`: Read in an IR file as an argument  
`-f <source file>`: Pass in a source file as an argument  
`-o <ir file>`: Output the IR results to a file  

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
- [ ] ++, —, &, !, sizeof
- [ ] -=, +=, *=, /=

Sample of a printed parse tree: ([parse tree for sample4 in test folder](docs/parsetree.txt)) 

### Symbol Table



### IR
Checklist of required features by the IR:
- [x] Identifiers, variables, functions
- [x] Keywords
- [x] Arithmetic expressions
- [x] Assignment
- [ ] Boolean expressions
- [ ] Goto statements
- [ ] If / Else control flow
- [ ] Unary operators
- [x] Return statements
- [ ] Break statements
- [ ] While loops

Checklist of optional features for the parser:
- [x] Types other than integers (supports double for numbers and void for functions)
- [ ] binary operators
- [ ] for loops
- [ ] switch statements
- [ ] ++, —, &, !, sizeof
- [ ] -=, +=, *=, /=

The IR was implemented by reading in the string form of the parse tree and parsing that information. This was done due to difficulties traversing the tree, however going forward this issue should be resolved and the IR will be changed to use this method instead. The string parsing method is not ideal, as it does give unexpected results in certain edge cases. 
