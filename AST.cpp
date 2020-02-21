/**
 * @file AST.cpp
 * @brief Implementation of the AST class
 */


#include "AST.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>

/*AST::AST()
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
}*/

/*void AST::insert(char const **key, node *leaf)
{
	int i;
	int params = 0;
	int firstOp;

	//set up node for first function name hit
	//could be a function aside from main. will change to deal with that
	if (strncmp(key[0], "main", 4) == 0) {
		leaf->left = new node;
		leaf->left->Type = Main;
		leaf->left->left = NULL;    
		leaf->left->right = NULL;   
	}
	//count up params until first operator is hit
	for (i = 1; i < 3; i++) {
		if (strncmp(key[i], "return", 6) == 0) {//count until operator is hit
			firstOp = i;
			break;
		}
		params++;
	}

	if (params == 0) {
		leaf->left->right = new node;
		leaf = leaf->left->right;
		leaf->Type = Return; //change the logic if other ops are encountered instead
		leaf->left = NULL; //return has one child only; will change for other kinds of ops
	} else {
		//this block for setting up passed in params on left side of tree
	}

	for (i = (firstOp + 1); i < 3; i++) {
		char *end;
		long num = strtol(key[i], &end, 10); 
		//numbers      
		if (end != key[i]) {
			leaf->left = new node;
			leaf = leaf->left;
			leaf->Type = NumberValue;
			leaf->key_value = (int) num;
			leaf->left = NULL;
			leaf->right = NULL;
		} else {
			//more operators
			//more functions
		}
	}
}*/

/*void AST::insert(char const **key)
{
	root = new node;
	root->Type = Program;
	root->left = NULL;
	root->right = NULL;
	insert(key, root);
}*/

/*node *AST::search(int key)
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
		if (leaf->Type == 8)
			printf("%d\n", leaf->key_value);
		else 
			printf("%s\n", leaf->ASTTypes[leaf->Type]);
	}
}

void AST::printTree()  
{  
	int h = height(root);  
	int i;  
	for (i = 1; i <= h; i++)  
		printTree(root, i);  
}  

void AST::printTree(node *root, int level)  
{  
	if (root == NULL)  
		return;  
	if (level == 1)  
		if (root->Type == 8)
			printf("%d\n", root->key_value);
		else {
			printf("%s\n", root->ASTTypes[root->Type]); 
			printf("|\n");
		}
	else if (level > 1)  {  
		printTree(root->left, level - 1);  
		printTree(root->right, level - 1);  
	}  
}  

int AST::height(node *leaf)  
{  
	if (leaf == NULL)  
        	return 0;  
    	else {  */
		/* compute the height of each subtree */
		//int lheight = height(leaf->left);  
		//int rheight = height(leaf->right);  
  
        	/* use the larger one */
		/*if (lheight > rheight)  
			return(lheight + 1);  
		else return(rheight + 1);  
    	}  
}  

void AST::destroy_tree()
{
	destroy_tree(root);
}*/

/*void Scanner::GetNextToken(std::vector<token_t> tokens)
{
	m_crtToken.Value = 0;
	m_crtToken.Symbol = 0;
	const char *data = tokens[index].contents.data();

	if(index == 3) {
		m_crtToken.Type = EndOfText;
		return;
	}

	if(isdigit(data)) {
 		m_crtToken.Type = Number;
		char *end;
		long num = strtol(data, &end, 10); 
		//numbers      
		if (end != data) {
	 		m_crtToken.Value = (int) num;
 		return;
	}

	m_crtToken.Type = Error;

	switch(data) {
		case '+':
			m_crtToken.Type = Plus; 
			break;
		case '-': 
			m_crtToken.Type = Minus; 
			break;
		case '*': 
			m_crtToken.Type = Mul; 
			break;
		case '/': 
			m_crtToken.Type = Div; 
			break;
		case '(': 
			m_crtToken.Type = OpenParenthesis; 
			break;
		case ')': 
			m_crtToken.Type = ClosedParenthesis; 
			break;
	}

	if(m_crtToken.Type != Error) {
 		m_crtToken.Symbol = data;
 		index++;
  	} else {
 		std::stringstream sstr; 
 		sstr << "Unexpected token '" << data << "' at position " << index;
 		throw ParserException(sstr.str(), index);
	}
}*/

ASTNode* ASTNode::CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right)
{
      ASTNode* node = new ASTNode;
      node->Type = type;
      node->Left = left;
      node->Right = right;
      return node;
}

void ASTNode::Match(const char *expected, std::vector<token_t> tokens)
{
	const char *data = tokens[index].contents.data();
	if (strncmp(data, expected, 1) == 0)
		Counter(tokens);
	else {
		printf("Expected token %s at position %d\n", expected, index);
		exit(-1);
	}
}

ASTNode* ASTNode::CreateUnaryNode(ASTNode* left)
{
	ASTNode* node = new ASTNode;
	node->Type = UnaryMinus;
	node->Left = left;
	node->Right = NULL;
	return node;
}

ASTNode* ASTNode::CreateNodeNumber(double value)
{
	ASTNode* node = new ASTNode;
	node->Type = NumberValue;
	node->Value = value;
	return node;
}

ASTNode* ASTNode::Factor(std::vector<token_t> tokens)
{
	ASTNode* node;
	char *end;
	const char *data = tokens[index].contents.data();
	long num = strtol(data, &end, 10); 
	if (strncmp(data, "(", 1) == 0) {
		Counter(tokens);
		node = Expression(tokens);
         	Match(")", tokens);
         	return node;
	} else if (strncmp(data, "-", 1) == 0) {
		Counter(tokens);
		node = Factor(tokens);
         	return CreateUnaryNode(node);
	} else if (end != data) {
		int value = (int) num;
		Counter(tokens);
		return CreateNodeNumber(value);
	} else {
		printf("Unexpected token %s at %d\n", data, index);
		exit(-1);
	}
}


ASTNode* ASTNode::Term1(std::vector<token_t> tokens)
{
	ASTNode* fnode;
	ASTNode* t1node;
	const char *data = tokens[index].contents.data();
	if (strncmp(data, "*", 1) == 0) {
		Counter(tokens);
		fnode = Factor(tokens);
	 	t1node = Term1(tokens);
	 	return CreateNode(OperatorMul, t1node, fnode);
	} else if (strncmp(data, "/", 1) == 0) {
		Counter(tokens);
		fnode = Factor(tokens);
	 	t1node = Term1(tokens);
	 	return CreateNode(OperatorDiv, t1node, fnode);
	} 
	return CreateNodeNumber(-1);
}

ASTNode* ASTNode::Term(std::vector<token_t> tokens)
{
	ASTNode *fnode = Factor(tokens);
	ASTNode *t1node = Term1(tokens);
	return CreateNode(Declaration, fnode, t1node);
}

ASTNode* ASTNode::Expression1(std::vector<token_t> tokens)
{
	ASTNode* tnode;
	ASTNode* e1node;
	const char *data = tokens[index].contents.data();
	if (strncmp(data, "+", 1) == 0) {
		Counter(tokens);
		tnode = Term(tokens);
	 	e1node = Expression1(tokens);
	 	return CreateNode(OperatorPlus, e1node, tnode);
	
	} else if (strncmp(data, "-", 1) == 0) {
		Counter(tokens);
		tnode = Term(tokens);
         	e1node = Expression1(tokens);
		return CreateNode(OperatorMinus, e1node, tnode);
	} 

	return CreateNodeNumber(-1);
}

void ASTNode::Counter(std::vector<token_t> tokens)
{
	if (index < (int) (tokens.size() - 1)) {
		index++;
	} else {
		return;
	}	
}


ASTNode* ASTNode::Expression(std::vector<token_t> tokens)
{
	ASTNode* tnode = Term(tokens);
	ASTNode* e1node = Expression1(tokens);
	return CreateNode(Program, tnode, e1node);
}

ASTNode* ASTNode::Parse(std::vector<token_t> tokens)
{
	return Expression(tokens);
}

void ASTNode::printTree(ASTNode *root)  
{  
	int h = height(root);  
	int i;  
	for (i = 1; i <= h; i++)  
		printTree(root, i);  
}  

void ASTNode::printTree(ASTNode *root, int level)  
{  
	if (root == NULL)  
		return;  
	if (level == 1)  
		if (root->Type == 8)
			printf("%d\n", root->Value);
		else {
			printf("%s\n", root->ASTTypes[root->Type]); 
			printf("|\n");
		}
	else if (level > 1)  {  
		printTree(root->Left, level - 1);  
		printTree(root->Right, level - 1);  
	}  
}  

int ASTNode::height(ASTNode *leaf)  
{  
	if (leaf == NULL)  
        	return 0;  
    	else {  
		/* compute the height of each subtree */
		int lheight = height(leaf->Left);  
		int rheight = height(leaf->Right);  
  
        	/* use the larger one */
		if (lheight > rheight)  
			return(lheight + 1);  
		else 
			return(rheight + 1);  
    	}  
}  

void ASTNode::postorder(ASTNode *leaf)
{
	if (leaf != NULL) {  
		postorder(leaf->Left);
		postorder(leaf->Right);
		if (leaf->Type == 8)
			printf("%d\n", leaf->Value);
		else 
			printf("%s\n", leaf->ASTTypes[leaf->Type]);
	}
}

