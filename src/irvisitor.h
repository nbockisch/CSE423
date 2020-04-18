/**
 * @file irvisitor.h
 * @brief Uses the Visitor pattern to gather the tokens for the IR
 * 
 */
#ifndef IRVISITOR_H
#define IRVISITOR_H

#include "node.h"
#include "nodevisitor.h"
#include "ir.h"
   

// Controls how many spacing characters to print at each level of the tree
//#define INDENTSIZE 5

class IrVisitor : public NodeVisitor {
public:
        IrVisitor(ir *ir_obj) {
            this->ir_obj = ir_obj;

        }
        void visit(const NExpression& node) {
                return;
        }
        
        void visit(const NStatement& node) {
                return;
        }

        void visit(const NInteger &node) {
                return;
        }

        void visit(const NDouble &node) {
                return;
        }
        
        void visit(const NIdentifier& node) {
                return;
        }
        
        void visit(const NType& node) {
                return;
        }
        
        void visit(const NMethodCall& node) {
                return;
        }
        
        void visit(const NBinaryOperator& node) {
                node.lhs.accept(*this);
                node.rhs.accept(*this);
        }

	void visit(const NUnaryOperator& node) {
                node.expression.accept(*this);
        }
        
        void visit(const NAssignment& node) {
            item_t item;
            item.label = "ASSIGNMENT";
            node.lhs.accept(*this);
            node.rhs.accept(*this);
        }
        
        void visit(const NBlock &node) {
            for (auto statement : node.statements) {
                statement->accept(*this);
            }

        }

	void visit(const NGOTO &node) {
            return;
        }

	void visit(const NGOTOBlock &node) {
            return;
        }

	void visit(const NBreak &node) {
            return;
        }
        
        void visit(const NExpressionStatement& node) {
            node.expression.accept(*this);
        }
        
        void visit(const NReturnStatement& node) {
            node.expression.accept(*this);
        }
        
        void visit(const NIfStatement& node) {
            node.block.accept(*this);
        }

	void visit(const NElseIfStatement& node) {
            node.block.accept(*this);
        }
                
        void visit(const NWhileStatement& node) {
            node.block.accept(*this);
        }
        
	void visit(const NForStatement& node) {
            node.block.accept(*this);
        }

        void visit(const NElseStatement& node) {
            node.block.accept(*this);
        }
        
        void visit(const NVariableDeclaration& node) {
            item_t item;
            item.label = "VAR DECL";
            item.type = node.type.name;
            item.id = node.id.name;
            ir_obj->items.push_back(item);
        }
        
        void visit(const NFunctionDeclaration& node) {
            item_t item;
            item.label = "FUNC DECL";
            item.type = node.type.name;
            item.id = node.id.name;
           
            if (node.arguments.size() != 0) {
                for (auto var : node.arguments) {
                    item_t tmp;
                    tmp.type = var->type.name;
                    tmp.id = var->id.name;
                    item.params.push_back(tmp);
                }
            }

            ir_obj->items.push_back(item);
        }
private:
    ir *ir_obj;
                
};

#endif
