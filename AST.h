/**
 * @file AST.h
 * @brief Defines the AST tree structure, a binary tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>

struct node
{
	int key_value;
	node *left;
	node *right;
};

class AST
{
	public:
		AST();
		~AST();
		void insert(int key);
		void postorder();
		node *search(int key);
		void destroy_tree();

	private:
		void destroy_tree(node *leaf);
		void postorder(node *leaf);
		void insert(int key, node *leaf);
		node *search(int key, node *leaf);
		node *root;
};
