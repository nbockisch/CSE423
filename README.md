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
- [x] ++, —, &, !, sizeof
- [x] -=, +=, *=, /=

The IR works by using the visitor pattern to traverse the parse tree. It stores the contents of the tree in structs called item\_t which are found in ir.h. These structs hold the item's label (e.g. RETURN, VAR DECL), its type (e.g. int), its value (e.g. 5), and its id (e.g. x). It also contains a vector called params which is used to store item\_t objects that are leafs to an object in the tree. For example, a VAR DECL object may have in its params an IDENTIFIER assignment.

In its current state, the IR supports most required features in SSA format. There are exceptions, however. There are errors with SSA when creating an assignment to a binary operation for example. 

It should also be noted that reading in an IR file produces an IR representation internally in the program which is significantly inaccurate. This is due to an issue in the recursive function traverseIrFile in ir.cpp. Outputting the IR to a file produces mostly accurate results however. The IR representation appears as a series of lines for each line of the IR, where each line is represented in the following format:

[tree level],[label],[type],[id],[val],

They are separated by commas for ease of processing when reading the IR files in.

### Symbol Table

The symbol table is roughly implemented following the section in the textbook. It uses an unordered map to store records containing the variable name, record type (variable, function, function argument, label), variable type, and the AST node. To support multiple scopes, the symbol table is an array of unordered maps, where each element represents a new scope.

The symbol table was adjusted to be included within the grammar. This allowed for runtime semantic checking, such as whether a variable was previously defined or not. Variable and function references are able to be checked by the symbol table during the parsing of the grammar, which results in better syntax errors for re-declared, or unreferenced types.

Furthermore, the symbol table can check a previously defined scope for a name if it is not found within the current scope (such as for global functions). However, this feature is still limited and does not quite fully support many nested scope levels due to time considerations.

If there are blocks in the input with no variable definitions, then a scope level is still created but is empty (it contains no records).

### Assembly
Assembly follows gcc x86 assembly. A file called assembly_output.s is created. Variables must be declared like this: 
`int i = 5; `
Variable declarations without assignment are not supported, such as this:
`int i;
i = 5;`

Return statements can handle complex expressions but only with binary options. return 3 + 4 works, but return 3 + 4 + 5 will fail. Return statements with variables may not work because variable memory location lookup is buggy.

Variables cannot be set equal to function calls, such as int x = test(). Function calls have to be done alone such as test();

Variable declarations do not fully support other variables within them. For instance, int y = 3 + x may or may not work correctly. Variable memory location look up is buggy. Variables that are passed into functions may also not work.They work sometimes. Variable declarations and function calls with all numbers are fully supported.

There are some potential problems with assembly instructions being duplicated during an else block. Potential issues could arise when if/else statements are nested within each other as well.

If statements should be supported for comparisons like "if (x == 1)" "if (x >= 0)" and so on. if(x) is also handled. Complex statements such as "if(x == y + z)" are not likely to be supported, so it is recommended to pull these binary ops out before a conditional statement.

Checklist of required features for the Parser:
- [x] Identifiers, variables, functions
- [x] Keywords
- [x] Arithmetic expressions
- [x] Assignment
- [x] Boolean expressions
- [x] Goto statements
- [x] If / Else control flow (else support not quite fully implemented - assembly labels for else blocks are not quite correct)
- [x] Unary operators (negative numbers)
- [x] Return statements
- [x] Break statements
- [ ] While loops
