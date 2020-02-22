/**
 * @file AST.h
 * @brief Defines the AST tree structure, a binary tree
 */

#include <stdio.h>
#include "Scanner.h"
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <vector>

enum ASTNodeType 
{
	/* need to add other operators */
	Undefined,
	Return,
	OperatorPlus,
	Program,
	Main,
	OperatorMinus,
	OperatorMul,
	OperatorDiv,
	NumberValue

};

struct node
{
	ASTNodeType Type;
	int key_value;
	node *left;
	node *right;
	char ASTTypes[10][10] = {"undefined", "return", "+", "program", "main", "-", "*", "/", "Number"};

};

class AST
{
	public:
		AST();
		~AST();
		ASTNodeType Type;
   		double Value;
		void insert(char const **key);
		void postorder();
		void printTree();
		node *search(int key);
		void destroy_tree();

	private:
		void destroy_tree(node *leaf);
		void printTree(node *root, int level);
		void postorder(node *leaf);
		int height(node *leaf);
		void insert(char const **key, node *leaf);
		node *search(int key, node *leaf);
		node *root;
};


