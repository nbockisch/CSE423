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
                item_t item;
                item.label = "EXPRESSION";
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                blocks.push(item);
                return;
        }
        
        void visit(const NStatement& node) {
                item_t item;
                item.label = "STATEMENT";
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                blocks.push(item);
                return;
        }
        
        void visit(const NInteger &node) {
                item_t item;
                std::stringstream ss;
                
                ss << node.value;
                item.label = "INTEGER";
                item.val = ss.str();

                blocks.push(item);
                //exp_comp.push(ss.str());

                return;
        }
        
	void visit(const NBreak &node) {
		return;
	}

        void visit(const NDouble &node) {
                item_t item;
                std::stringstream ss;
                
                ss << node.value;
                item.label = "DOUBLE";
                item.val = ss.str();

                blocks.push(item);
                return;
        }
        
        void visit(const NIdentifier& node) {
                item_t item;
                
                item.label = "IDENTIFIER";
                item.id = node.name;

                blocks.push(item);
                //exp_comp.push(node.name);
                return;
        }
        
        void visit(const NType& node) {
                item_t item;
                
                item.label = "TYPE";
                item.type = node.name;

                blocks.push(item);
                //exp_comp.push(node.name);
                return;
        }
        
        void visit(const NMethodCall& node) {
                item_t item;
                item.label = "FUNCTION CALL";
                item.id = node.id.name;

                if (node.arguments.size() != 0) {
                    for (auto exp : node.arguments) {
                        exp->accept(*this);
                        while (!blocks.empty()) {
                            item.params.push_back(blocks.top());
                            blocks.pop();
                        }
                    }
                }

                blocks.push(item);
                return;
        }
        
        void visit(const NBinaryOperator& node) {
                item_t item;
                item_t op;
                item.label = "BIN OP";
                
                node.lhs.accept(*this);
                
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                switch (node.op) {
                    case 278:
                        op.val = "+";
                        break;
                    case 279:
                        op.val = "-";
                        break;
                    case 280:
                        op.val = "*";
                        break;
                    case 281:
                        op.val = "/";
                        break;
                    case 263:
                        op.val = "==";
                        break;
                    case 264:
                        op.val = "!=";
                        break;
                    case 265:
                        op.val = "<";
                        break;
                    case 266:
                        op.val = "<=";
                        break;
                    case 267:
                        op.val = ">";
                        break;
                    case 268:
                        op.val = ">=";
                        break;
                     
                }
                item.params.push_back(op);

                node.rhs.accept(*this);

                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                /*while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }

                ir_obj->items.push_back(item);*/
                blocks.push(item);
        }
        
	void visit(const NUnaryOperator& node) {
                node.expression.accept(*this);
                item_t item;
                item.label = "UNARY OP";
                
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                blocks.push(item);

        }

        void visit(const NAssignment& node) {
                node.lhs.accept(*this);
                item_t item;
                item.label = "ASSIGNMENT";
                //item.id = node.lhs.name;
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                
                node.rhs.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                /*while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }*/
                //ir_obj->items.push_back(item);
                blocks.push(item);
        }
        
        void visit(const NBlock &node) {
                // Everytime we encounter a block, that means a new scope.. so create a new table
                //*table->initializeScope();
                item_t item;
                item.label = "BLOCK";

                for( auto statement : node.statements) {
                        statement->accept(*this);
                        
                        while (!blocks.empty()) {
                            item.params.push_back(blocks.top());
                            blocks.pop();
                        }
                }
                blocks.push(item);

                ir_obj->blocks = blocks;
                //table->finalizeScope();
        }
        
        void visit(const NExpressionStatement& node) {
                node.expression.accept(*this);
                item_t item;
                item.label = "EXPRESSION STATEMENT";
                
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                blocks.push(item);
        }
        
        void visit(const NReturnStatement& node) {
                item_t item;
                node.expression.accept(*this);

                item.label = "RETURN";
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                /*while (!exp_comp.empty()) {
                    item_t tmp;
                    tmp.id = exp_comp.top();
                    //std::cout << "tmp id = " << tmp.id << std::endl;
                    item.params.push_back(tmp);
                    exp_comp.pop();
                }
                ir_obj->items.push_back(item);*/
                blocks.push(item);
        }
        
        void visit(const NIfStatement& node) {
                item_t item;
                item.label = "IF STATEMENT";
                node.expression.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                node.block.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                blocks.push(item);
        }

	 void visit(const NElseIfStatement& node) {
                item_t item;
                item.label = "ELSE IF STATEMENT";
                node.expression.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                node.block.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                blocks.push(item);
        }
                
        void visit(const NWhileStatement& node) {
                item_t item;
                item.label = "WHILE STATEMENT";
                node.expression.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                node.block.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                blocks.push(item);
        }

	void visit(const NForStatement& node) {
                item_t item;
                item.label = "FOR STATEMENT";
                node.expression1.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                node.expression2.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                node.expression3.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }

                node.block.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                blocks.push(item);
        }

        
        void visit(const NElseStatement& node) {
                item_t item;
                item.label = "ELSE STATEMENT";

                node.block.accept(*this);
                while (!blocks.empty()) {
                    item.params.push_back(blocks.top());
                    blocks.pop();
                }
                blocks.push(item);
        }
        
        void visit(const NVariableDeclaration& node) {
            item_t item;
            item.label = "VAR DECL";
            item.type = node.type.name;
            item.id = node.id.name;
            //node.assignmentExpr->accept(*this);
            while (!blocks.empty()) {
                item.params.push_back(blocks.top());
                blocks.pop();
            }
            blocks.push(item);
        }

	void visit(const NGOTO &node) {
                item_t item;
                item.label = "GOTO";
                item.val = node.id.name;
                blocks.push(item); 
                return;
        }

	void visit(const NGOTOBlock &node) {
            item_t item;
            item.label = "GOTO BLOCK";
            item.val = node.id.name;
            blocks.push(item); 
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
            /*if (node.arguments.size() != 0) {
                for (auto var : node.arguments) {
                    item_t tmp;
                    tmp.type = var->type.name;
                    tmp.id = var->id.name;
                    item.params.push_back(tmp);
                }
            }

            ir_obj->items.push_back(item); */
            node.block.accept(*this);
            while (!blocks.empty()) {
                item.params.push_back(blocks.top());
                blocks.pop();
            }
            blocks.push(item);

        }
                
private:
        ir *ir_obj;
        //std::stack<std::string> exp_comp;
        std::stack<item_t> blocks;
};



#endif
