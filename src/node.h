/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
//#include <llvm/IR/Value.h>

#include <typeinfo>
#include <cxxabi.h>

#include <stdio.h>
#include <string>
#include "nodevisitor.h"

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

class Node {
public:
        virtual ~Node() {}
        //virtual llvm::Value* codeGen(CodeGenContext& context) { return NULL; }
                
        /**
         * Returns a string of the demangled class name
         */
        std::string getType() const {
                int status = 0;
                char *type = abi::__cxa_demangle(typeid(*this).name(), 0,0, &status);
                return std::string(type);
        };
};

class NExpression : public Node {
public:
        virtual void accept(NodeVisitor& visitor) const = 0;        
};

class NStatement : public Node {
public:
        virtual void accept(NodeVisitor& visitor) const = 0;
};

class NInteger : public NExpression {
public:
	long long value;
	NInteger(long long value) : value(value) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); };
};

class NDouble : public NExpression {
public:
 	double value;
	NDouble(double value) : value(value) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override {  }

};

class NIdentifier : public NExpression {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override{ visitor.visit(*this); }
       
};

class NType : public NExpression {
public:
	std::string name;
	NType(const std::string& name) : name(name) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
                
};


class NMethodCall : public NExpression {
public:
	const NIdentifier& id;
	ExpressionList arguments;
	NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
		id(id), arguments(arguments) { }
	NMethodCall(const NIdentifier& id) : id(id) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NBinaryOperator : public NExpression {
public:
	int op;
	NExpression& lhs;
	NExpression& rhs;
	NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
                op(op), lhs(lhs), rhs(rhs) { }
	// llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NUnaryOperator : public NExpression {
public:
	int op1,op2;
	NExpression& expr;
	NUnaryOperator(int op1, NExpression& expr, int op2) :
                op1(op1), expr(expr), op2(op2) { }
	// llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NAssignment : public NExpression {
public:
	NIdentifier& lhs;
	NExpression& rhs;
	NAssignment(NIdentifier& lhs, NExpression& rhs) : 
		lhs(lhs), rhs(rhs) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

class NBlock : public NExpression {
public:
	StatementList statements;
	NBlock() { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NExpressionStatement : public NStatement {
public:
	NExpression& expression;
	NExpressionStatement(NExpression& expression) : 
		expression(expression) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

class NReturnStatement : public NStatement {
public:
	NExpression& expression;
	NReturnStatement(NExpression& expression) : 
		expression(expression) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

class NBreak : public NStatement {
public:
	//virtual llvm::Value* codeGen(CodeGenContext& context);
	NBreak() {}
        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

class NGOTO : public NStatement {
public:
	const NIdentifier& id;
	NGOTO(const NIdentifier& id) :
		id(id) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NGOTOBlock : public NStatement {
public:
	const NIdentifier& id;
	NGOTOBlock(const NIdentifier& id) :
		id(id) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NIfStatement : public NStatement {
public:
	NBlock& block;
	NExpression& expression;
	NIfStatement(NExpression& expression, NBlock& block) : 
                block(block), expression(expression) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

class NWhileStatement : public NStatement {
public:
	NBlock& block;
	NExpression& expression;
	NWhileStatement(NExpression& expression, NBlock& block) : 
                block(block), expression(expression)  { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
           
};

class NForStatement : public NStatement {
public:
	NBlock& block;
	NExpression& expression1;
	NExpression& expression2;
	NExpression& expression3;
	NForStatement(NExpression& expression1, NExpression& expression2, NExpression& expression3, NBlock& block) : 
                block(block), expression1(expression1), expression2(expression2), expression3(expression3)  { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
           
};

class NElseStatement : public NStatement {
public:
	NBlock& block;
	NElseStatement(NBlock& block) : 
		block(block) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }

};

class NVariableDeclaration : public NStatement {
public:
	const NType& type;
	NIdentifier& id;
	NExpression *assignmentExpr;
	NVariableDeclaration(const NType& type, NIdentifier& id) :
                type(type), id(id) { assignmentExpr = NULL; };
	NVariableDeclaration(const NType& type, NIdentifier& id, NExpression *assignmentExpr) :
		type(type), id(id), assignmentExpr(assignmentExpr) { };
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

//ToDo (Maybe), add label declaration

class NFunctionDeclaration : public NStatement {
public:
	const NType& type;
	const NIdentifier& id;
	VariableList arguments;
	NBlock& block;
	NFunctionDeclaration(const NType& type, const NIdentifier& id, 
			const VariableList& arguments, NBlock& block) :
		type(type), id(id), arguments(arguments), block(block) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        void accept(NodeVisitor& visitor) const override { visitor.visit(*this); }
        
};

#endif
