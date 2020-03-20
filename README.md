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


A basic setup with CMake is used, to compile "out-of-source":

mkdir build

cd build

cmake ../

make

