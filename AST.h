/**
 * @file AST.h
 * @brief Defines the AST tree structure, a binary tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

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
		void insert(char const **key);
		void postorder();
		node *search(int key);
		void destroy_tree();

	private:
		void destroy_tree(node *leaf);
		void postorder(node *leaf);
		void insert(char const **key, node *leaf);
		node *search(int key, node *leaf);
		node *root;
};
