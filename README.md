# CSE423 Compiler
## Group Members:
* Eva Domschott (spiritofthegael)
* Brandon Bicknell (Bicknell125)
* Coleman Kendrick (ckendrick)
* Nathan Bockisch (nbockisch)

## Project Structure
* src - The folder holding the source code for the project. ([more info](src/src.md))
* test - The folder holding the C source files to test the compiler with. ([more info](test/test.md))

## Building
The project is compiled using `gcc` and a `Makefile`. Ensure both `gcc` (or another compiler bound to the `gcc` command), and `make` are installed on your system. Then simply do the following:
1. `cd src`
2. `make`

## Usage
`./compiler -p -t -f <source file>`
`-p`: Print the parse tree
`-t`: Print the tokens
`-f`: Pass in a source file as an argument

## Design Decisions and Implementation
### Lexer
The lexer was implemented with Flex due to time considerations.

### Parser
The parser was implemented with Bison due to time considerations.

## Supported Features
