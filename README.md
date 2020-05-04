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
`-r <ir file>`: Read in an IR file as an argument  
`-f <source file>`: Pass in a source file as an argument  
`-o <ir file>`: Output the IR results to a file  

## Design Decisions and Implementation
### Lexer
The lexer was implemented with Flex due to time considerations.The lexer does not currently deal with comments in code.

[tokens for sample4 in test folder](docs/tokens.txt) 

### Parser
The parser was implemented with Bison due to time considerations.

Checklist of required features for the Parser:
- [x] Identifiers, variables, functions
- [x] Keywords
- [x] Arithmetic expressions
- [x] Assignment
- [x] Boolean expressions
- [x] Goto statements
- [x] If / Else control flow (supports Else If as well)
- [x] Unary operators (++, --, &, and -)
- [x] Return statements
- [x] Break statements
- [x] While loops

Checklist of optional features for the parser:
- [x] Types other than integers (supports void for functions)
- [ ] binary operators
- [x] for loops (i must be declared before for loop. Example:
`int i;  
for(i = 0; i < 5; i++) {  
  #do something  
}`)  
- [ ] switch statements
- [ ] -=, +=, *=, /=

Sample of a printed parse tree: ([parse tree for sample4 in test folder](docs/parsetree.txt)) 

### IR
Checklist of required features by the IR:
- [x] Identifiers, variables, functions
- [x] Keywords
- [x] Arithmetic expressions
- [x] Assignment
- [x] Boolean expressions
- [x] Goto statements
- [x] If / Else control flow
- [x] Unary operators
- [x] Return statements
- [x] Break statements
- [x] While loops

Checklist of optional features for the parser:
- [x] Types other than integers (supports void for functions)
- [ ] binary operators
- [ ] for loops
- [ ] switch statements
- [ ] ++, —, &, !, sizeof
- [ ] -=, +=, *=, /=

The IR was implemented by reading in the string form of the parse tree and parsing that information. This was done due to difficulties traversing the tree, however going forward this issue should be resolved and the IR will be changed to use this method instead. The string parsing method is not ideal, as it does give unexpected results in certain edge cases.

### Symbol Table

The symbol table is roughly implemented following the section in the textbook. It uses an unordered map to store records containing the variable name, record type (variable, function, function argument, label), variable type, and the AST node. To support multiple scopes, the symbol table is an array of unordered maps, where each element represents a new scope.

The symbol table is filled by traversing the AST using the visitor pattern. When an AST node containing a block node is visited, a new symbol table scope is created via `initializeScope()`. When a variable declaration or function declaration is visited, a new record is created and inserted into the active symbol table scope. After a block node is done being visited, the active scope is switched to the previous scope via `finalizeScope()`.

If there are blocks in the input with no variable definitions, then a scope level is still created but is empty (it contains no records).

### Assembly
Assembly follows gcc x86 assembly. A file called assembly_output.s is created. Variables must be declared like this: 
`int i = 5; `
Variable declarations without assignment are not supported, such as this:
`int i;
i = 5;`

Return statements can handle complex expressions but only with binary options. return x + y works, but return x + y + z will fail.

Checklist of required features for the Parser:
- [x] Identifiers, variables, functions
- [x] Keywords
- [x] Arithmetic expressions
- [x] Assignment
- [] Boolean expressions
- [x] Goto statements
- [] If / Else control flow (supports Else If as well)
- [x] Unary operators (negative numbers)
- [x] Return statements
- [x] Break statements
- [] While loops
