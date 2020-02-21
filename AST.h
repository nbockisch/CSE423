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

//enum ASTNodeType 
//{
	/* need to add other operators */
	/*Undefined,
	Return,
	OperatorPlus,
	Program,
	Main,
	OperatorMinus,
	OperatorMul,
	OperatorDiv,
	NumberValue*/
	/*Undefined,
	OperatorPlus,
	OperatorMinus,
	OperatorMul,
	OperatorDiv,
	UnaryMinus,
	NumberValue

};*/

/*struct node
{
	ASTNodeType Type;
	int key_value;
	node *left;
	node *right;
	char ASTTypes[10][10] = {"undefined", "return", "+", "program", "main", "-", "*", "/", "Number"};

};*/

/*class AST
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
};*/

enum ASTNodeType 
{
	Undefined,
	Program,
	Declaration,
	OperatorPlus,
	OperatorMinus,
	OperatorMul,
	OperatorDiv,
	UnaryMinus,
	NumberValue
};
 
class ASTNode
{
	public:
		int index = 0;
		ASTNodeType Type;
		char ASTTypes[11][12] = {"undefined", "program", "declaration", "+", "-", "*", "/", "-", "Number"};
		int      Value;
		ASTNode*    Left;
		ASTNode*    Right;
		void postorder(ASTNode *leaf);
		ASTNode *Parse(std::vector<token_t> tokens);
		void printTree(ASTNode *root);
		ASTNode()
		{
			Type = Undefined;
			Value = 0;
			Left = NULL;
			Right = NULL;
		}
	 
		~ASTNode()
		{
			delete Left;
			delete Right;
		}
	private:
		void printTree(ASTNode *root, int level);
		int height(ASTNode *leaf);
		void Counter(std::vector<token_t> tokens);
		void Match(const char *expected, std::vector<token_t> tokens);
		ASTNode* CreateUnaryNode(ASTNode* left);
		ASTNode* CreateNodeNumber(double value);
		ASTNode* Factor(std::vector<token_t> tokens);	
		ASTNode* Term1(std::vector<token_t> tokens);
		ASTNode* Term(std::vector<token_t> tokens);
		ASTNode* Expression1(std::vector<token_t> tokens);
		ASTNode* Expression(std::vector<token_t> tokens);
		ASTNode* CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right);
};
