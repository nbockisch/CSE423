/**
 * @file nodevisitor.h
 * @brief Defines a virtual Visitor Pattern class for use with the AST
 */

#ifndef NODEVISITOR_H
#define NODEVISITOR_H

class NExpression;
class NStatement;
class NInteger;
class NDouble;
class NIdentifier;
class NType;
class NBreak;
class NMethodCall;
class NBinaryOperator;
class NAssignment;
class NBlock;
class NGOTO;
class NGOTOBlock;
class NExpressionStatement;
class NReturnStatement;
class NUnaryOperator;
class NIfStatement;
class NWhileStatement;
class NForStatement;
class NElseStatement;
class NVariableDeclaration;
class NFunctionDeclaration;

class NodeVisitor {
public:
        virtual void visit(const NExpression& node) = 0;
        virtual void visit(const NStatement& node) = 0;
        virtual void visit(const NInteger& node) = 0;
        virtual void visit(const NDouble& node) = 0;
        virtual void visit(const NIdentifier& node) = 0;
        virtual void visit(const NType& node) = 0;
        virtual void visit(const NMethodCall& node) = 0;
        virtual void visit(const NBinaryOperator& node) = 0;
	virtual void visit(const NUnaryOperator& node) = 0;
        virtual void visit(const NAssignment& node) = 0;
        virtual void visit(const NBlock& node) = 0;
	virtual void visit(const NBreak& node) = 0;
	virtual void visit(const NGOTO& node) = 0;
	virtual void visit(const NGOTOBlock& node) = 0;
        virtual void visit(const NExpressionStatement& node) = 0;
        virtual void visit(const NReturnStatement& node) = 0;
        virtual void visit(const NIfStatement& node) = 0;
        virtual void visit(const NWhileStatement& node) = 0;
	virtual void visit(const NForStatement& node) = 0;
        virtual void visit(const NElseStatement& node) = 0;
        virtual void visit(const NVariableDeclaration& node) = 0;
        virtual void visit(const NFunctionDeclaration& node) = 0;
};

#endif
