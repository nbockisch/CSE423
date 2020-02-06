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
	OperatorPlus,
	OperatorMinus,
	OperatorMul,
	OperatorDiv,
	UnaryMinus,
	NumberValue
};

struct node
{
	ASTNodeType Type;
	int key_value;
	node *left;
	node *right;
};

class AST
{
	public:
		AST();
		~AST();
		void insert(ASTNodeType key, int priority);
		void postorder();
		node *search(int key);
		void destroy_tree();

	private:
		void destroy_tree(node *leaf);
		void postorder(node *leaf);
		void insert(int key, int priority, node *leaf);
		node *search(int key, node *leaf);
		node *root;
};
