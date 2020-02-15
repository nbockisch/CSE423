/**
 * @file AST.cpp
 * @brief Implementation of the AST class
 */


#include "AST.h"
#include <stdio.h>

AST::AST()
{
	root = NULL;
}

AST::~AST()
{
	destroy_tree();
}

void AST::destroy_tree(node *leaf)
{
	if(leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

node *AST::search(int key, node *leaf)
{
	if(leaf != NULL) {
		if(key == leaf->key_value)
			return leaf;
		if(key < leaf->key_value)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return NULL;
}

void AST::insert(int key[], node *leaf)
{
	int i;
	int params = 0;
	//int size = sizeof(key)/sizeof(key[0]);
	//printf("%d\n", size);
	for(i = 0; i < 11; i++) {
		if (key[i] == 3) //count until op is hit
			break;
		params++;
	}
	if(leaf->left != NULL)
		insert(key, leaf->left);
	else {
		leaf->left = new node;
		leaf->left->key_value = key[3];
		leaf->left->Type = OperatorPlus;
		leaf->left->left = NULL;    
		leaf->left->right = NULL;   
	}  

	/*if(key < leaf->key_value) {
		if(leaf->left != NULL)
			insert(key, leaf->left);
		else {
			leaf->left = new node;
			leaf->left->key_value = key[3];
			leaf->left->Type = OperatorPlus;
			leaf->left->left = NULL;    
			leaf->left->right = NULL;   
		}  
	}
	else if(key >= leaf->key_value) {
		if(leaf->right!=NULL)
			insert(key, leaf->right);
		else {
			leaf->right = new node;
			leaf->right->key_value = key;
			leaf->right->left = NULL; 
			leaf->right->right = NULL; 
		}
	}*/
}

void AST::insert(int key[])
{
	root = new node;
	root->Type = Program;
	root->left = NULL;
	root->right = NULL;
	insert(key, root);
}

node *AST::search(int key)
{
	return search(key, root);
}

void AST::postorder() {
	postorder(root);
}

void AST::postorder(node *leaf)
{
	if (leaf != NULL) {   
		postorder(leaf->left);
		postorder(leaf->right);
		printf("%d\n", leaf->key_value);
		printf("%s\n", leaf->ASTTypes[leaf->Type]);
	}
}

void AST::destroy_tree()
{
	destroy_tree(root);
}
