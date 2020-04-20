/**
 * @file irvisitor.h
 * @brief Uses the Visitor pattern to gather the tokens for the IR 
 */
#ifndef IRVISITOR_H
#define IRVISITOR_H

#include <stdio.h>
#include <string>
#include <stack>
#include <sstream>
#include "node.h"
#include "nodevisitor.h"
#include "ir.h"

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
                std::stringstream ss;
                ss << node.value;

                exp_comp.push(ss.str());
                return;
        }
        
	void visit(const NBreak &node) {
		return;
	}

        void visit(const NDouble &node) {
                std::stringstream ss;
                ss << node.value;

                exp_comp.push(ss.str());
                return;
        }
        
        void visit(const NIdentifier& node) {
                exp_comp.push(node.name);
                return;
        }
        
        void visit(const NType& node) {
                exp_comp.push(node.name);
                return;
        }
        
        void visit(const NMethodCall& node) {
                item_t item;
                item.label = "FUNCTION CALL";
                while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }

                ir_obj->items.push_back(item);
                return;
        }
        
        void visit(const NBinaryOperator& node) {
                item_t item;
                item_t op;
                item.label = "BIN OP";
                
                node.lhs.accept(*this);
                
                while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }

                switch (node.op) {
                    case 278:
                        op.id = "+";
                        break;
                    case 279:
                        op.id = "-";
                        break;
                    case 280:
                        op.id = "*";
                        break;
                    case 281:
                        op.id = "/";
                        break;
                    case 263:
                        op.id = "==";
                        break;
                    case 264:
                        op.id = "!=";
                        break;
                    case 265:
                        op.id = "<";
                        break;
                    case 266:
                        op.id = "<=";
                        break;
                    case 267:
                        op.id = ">";
                        break;
                    case 268:
                        op.id = ">=";
                        break;
                     
                }
                item.params.push_back(op);

                node.rhs.accept(*this);

                while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }

                ir_obj->items.push_back(item);
        }
        
	void visit(const NUnaryOperator& node) {
                node.expression.accept(*this);
        }

        void visit(const NAssignment& node) {
                node.lhs.accept(*this);
                item_t item;
                item.label = "ASSIGNMENT";
                item.id = node.lhs.name;
                
                node.rhs.accept(*this);
                while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }
                ir_obj->items.push_back(item);

        }
        
        void visit(const NBlock &node) {
                // Everytime we encounter a block, that means a new scope.. so create a new table
                //*table->initializeScope();

                for( auto statement : node.statements) {
                        statement->accept(*this);
                }
                
                //table->finalizeScope();
        }
        
        void visit(const NExpressionStatement& node) {
                node.expression.accept(*this);
        }
        
        void visit(const NReturnStatement& node) {
                item_t item;
                node.expression.accept(*this);

                item.label = "RETURN";
                while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    //std::cout << "tmp id = " << tmp.id << std::endl;
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }
                ir_obj->items.push_back(item);
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
            while (!exp_comp.empty()) {
                item_t tmp;
                tmp.id = exp_comp.top();
                item.params.push_back(tmp);
                exp_comp.pop();
            }
            ir_obj->items.push_back(item);
        }

	void visit(const NGOTO &node) {
                item_t item;
                item.label = "GOTO";
                item.id = node.id.name;
                ir_obj->items.push_back(item);
                return;
        }

	void visit(const NGOTOBlock &node) {
		return;
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
            node.block.accept(*this);

        }
                
private:
        ir *ir_obj;
        std::stack<std::string> exp_comp;
};



#endif
