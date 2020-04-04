/**
 * @file symvisitor.h
 * @brief Uses the Visitor pattern to traverse AST and fill the symbol table
 */
#ifndef SYMVISITOR_H
#define SYMVISITOR_H

#include "node.h"
#include "nodevisitor.h"
#include "symtable.h"

class SymVisitor : public NodeVisitor {
public:
        SymVisitor(Symtable *table) {
                if(table == NULL) {
                        printf("Error: SymVisitor expected an existing Symtable object!\n");
                        exit(-1);
                }
                
                this->table = table;
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
        
        void visit(const NAssignment& node) {
                node.lhs.accept(*this);
                node.rhs.accept(*this);
        }
        
        void visit(const NBlock &node) {
                // Everytime we encounter a block, that means a new scope.. so create a new table
                table->initializeScope();

                for( auto statement : node.statements) {
                        statement->accept(*this);
                }
                
                table->finalizeScope();
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
                
        void visit(const NWhileStatement& node) {
                node.block.accept(*this);
        }
        
        void visit(const NElseStatement& node) {
                node.block.accept(*this);
        }
        
        void visit(const NVariableDeclaration& node) {

                record_t entry;
                entry.name = node.id.name;
                entry.rtype = record_type::variable;
                entry.type = node.type.name;
                entry.node = &node;

                table->insert(entry.name, entry);
        }
        
        void visit(const NFunctionDeclaration& node) {
                record_t entry;
                entry.name = node.id.name;
                entry.rtype = record_type::function;
                entry.type = node.type.name;
                entry.node = &node;

                table->insert(entry.name, entry);
                
                // Create a new scope for the function arguments?
                if(node.arguments.size() != 0) {
                        table->initializeScope();
                        for (auto var : node.arguments) {
                                record_t entry;
                                entry.name = var->id.name;
                                entry.rtype = record_type::funcarg;
                                entry.type = var->type.name;
                                entry.node = var;
                                
                                table->insert(entry.name, entry);
                        }
                        table->finalizeScope();
                }
                
                node.block.accept(*this);
        }
                
private:
        Symtable *table;
};



#endif
