/**
 * @file printvisitor.h
 * @brief Uses the Visitor pattern to print nodes of the AST
 * 
 */
#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

#include "node.h"
#include "nodevisitor.h"
   

// Controls how many spacing characters to print at each level of the tree
#define INDENTSIZE 5

class PrintVisitor : public NodeVisitor {
public:
        void visit(const NExpression& node) {
                return;
        }
        
        void visit(const NStatement& node) {
                return;
        }

        void visit(const NInteger &node) {
                out.append(pindent(level, "~"));

                out.append("<INTEGER>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%lld", node.value);

                out.append(pindent(level+1, "~"));
                out.append(tmp);
                out.append("\n");
        }

        void visit(const NDouble &node) {
                out.append(pindent(level, "~"));

                out.append("<DOUBLE>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%f", node.value);

                out.append(pindent(level+1, "~"));
                out.append(tmp);
                out.append("\n");
        }
        
        void visit(const NIdentifier& node) {
                out.append(pindent(level, "~"));

                out.append("<IDENTIFIER>\n");
                out.append(pindent(level+1, "~"));
                out.append(node.name);
                out.append("\n");
        }
        
        void visit(const NType& node) {
                out.append(pindent(level, "~"));

                out.append("<TYPE>\n");
                out.append(pindent(level+1, "~"));
                out.append(node.name);
                out.append("\n");
        }
        
        void visit(const NMethodCall& node) {
                out.append(pindent(level, "~"));

                out.append("<FUNCTION CALL>\n");

                level++;
                node.id.accept(*this);
                
                for (auto argument : node.arguments) {
                        out.append("\n");
                        argument->accept(*this);
                }
                out.append("\n");
                level--;
        }
        
        void visit(const NBinaryOperator& node) {
                out.append(pindent(level, "~"));

                out.append("<BIN OP>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%d", node.op);

                level++;
                node.lhs.accept(*this);
                
                out.append(pindent(level, "~"));
                out.append("<OPERATOR>\n");
                out.append(pindent(level+1, "~"));
		switch(std::stoi(tmp)) {
			case 278:
				out.append("+");
				break;
			case 279:
				out.append("-");
				break;
			case 280:
				out.append("*");
				break;
			case 281:
				out.append("/");
				break;
			case 263:
				out.append("==");
				break;
			case 264:
				out.append("!=");
				break;
			case 265:
				out.append("<");
				break;
			case 266:
				out.append("<=");
				break;
			case 267:
				out.append(">");
				break;
			case 268:
				out.append(">=");
				break;
		}

                out.append("\n");

                node.rhs.accept(*this);
                level--;
        }

	void visit(const NUnaryOperator& node) {
                out.append(pindent(level, "~"));

                out.append("<UNARY OP>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%d", node.op);

                level++;
                node.expression.accept(*this);
                
                out.append(pindent(level, "~"));
                out.append("<OPERATOR>\n");
                out.append(pindent(level+1, "~"));
		switch(std::stoi(tmp)) {
			case 282:
				out.append("++");
				break;
			case 283:
				out.append("--");
				break;
			case 284:
				out.append("&");
				break;
			case 285:
				out.append("!");
				break;
			case 279:
				out.append("-");
				break;
		}

                out.append("\n");

                level--;
        }
        
        void visit(const NAssignment& node) {
                out.append(pindent(level, "~"));

                out.append("<ASSIGNMENT>\n");
                level++;
                node.lhs.accept(*this);
                node.rhs.accept(*this);
                level--;
        }
        
        void visit(const NBlock &node) {
                out.append(pindent(level, "~"));
                out.append("<BLOCK>\n");
                level++;
                
                for (auto statement : node.statements) {
                        statement->accept(*this);
                        out.append("\n");
                }
                level--;
        }

	void visit(const NGOTO &node) {
                out.append(pindent(level, "~"));
                out.append("<GOTO>\n");
                level++;
                node.id.accept(*this);
                level--;
        }

	void visit(const NGOTOBlock &node) {
                out.append(pindent(level, "~"));
                out.append("<GOTO LABEL>\n");
                level++;
                node.id.accept(*this);
                level--;
        }

	void visit(const NBreak &node) {
                out.append(pindent(level, "~"));
                out.append("<BREAK>\n");
        }
        
        void visit(const NExpressionStatement& node) {
                out.append(pindent(level, "~"));

                out.append("<EXPR STATEMENT>\n");

                level++;
                node.expression.accept(*this);
                level--;
        }
        
        void visit(const NReturnStatement& node) {
                out.append(pindent(level, "~"));
                
                out.append("<RETURN>\n");
                level++;
                node.expression.accept(*this);
                level--;
        }
        
        void visit(const NIfStatement& node) {
                out.append(pindent(level, "~"));
                
                out.append("<IF STATEMENT>\n");
                level++;
                node.expression.accept(*this);
                node.block.accept(*this);
                level--;
        }

	void visit(const NElseIfStatement& node) {
                out.append(pindent(level, "~"));
                
                out.append("<ELSE IF STATEMENT>\n");
                level++;
                node.expression.accept(*this);
                node.block.accept(*this);
                level--;
        }
                
        void visit(const NWhileStatement& node) {
                out.append(pindent(level, "~"));
                
                out.append("<WHILE STATEMENT>\n");
                level++;
                node.expression.accept(*this);
                node.block.accept(*this);
                level--;
        }
        
	void visit(const NForStatement& node) {
                out.append(pindent(level, "~"));
                
                out.append("<FOR STATEMENT>\n");
                level++;
                node.expression1.accept(*this);
		node.expression2.accept(*this);
		node.expression3.accept(*this);
                node.block.accept(*this);
                level--;
        }

        void visit(const NElseStatement& node) {
                out.append(pindent(level, "~"));
                
                out.append("<ELSE STATEMENT>\n");
                level++;
                node.block.accept(*this);
                level--;
        }
        
        void visit(const NVariableDeclaration& node) {
                out.append(pindent(level, "~"));

                out.append("<VAR DECL>\n");
                level++;
                node.type.accept(*this);
                node.id.accept(*this);
		if (node.assignmentExpr != NULL)
			node.assignmentExpr->accept(*this);
                level--;
        }
        
        void visit(const NFunctionDeclaration& node) {
                out.append(pindent(level, "~"));
                
                out.append("<FUNCTION DECL>\n");
                level++;
                node.type.accept(*this);
                node.id.accept(*this);

                for (auto argument : node.arguments) {
                        out.append("\n");
                        argument->accept(*this);
                }
                out.append("\n");

                node.block.accept(*this);

                level--;
        }
        
        std::string getResult() { return this->out; }
        
private:
        std::string out;
        int level = 0;

        std::string indent(int level, const char *c) const {
                std::string out;
                int n = INDENTSIZE*level;
                for (int i = 0; i < n; i++) {
                        out.append(c);
                }
                out.append(" ");
                return out;
        };

        /**
         * Prints spacing character c only between level-1 and level
         */
        std::string pindent(int level, const char *c) const {
                std::string out("");
                int n = INDENTSIZE*level;
                if(level == 0) {
                        // If we are at the root, just return empty string
                        return out;
                }
                for (int i = 0; i < n; i++) {
                        out.append(" ");
                }
                for (int i = n; i < INDENTSIZE*(level+1); i++) {
                        out.append(c);
                }
                out.append(" ");
                return out;
        };
};

#endif
