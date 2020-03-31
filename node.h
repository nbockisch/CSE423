/*code modified from this source https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/*/
#include <iostream>
#include <vector>
//#include <llvm/IR/Value.h>

#include <typeinfo>
#include <cxxabi.h>

#include <stdio.h>

class CodeGenContext;
class NStatement;
class NFunctionDeclaration;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NFunctionDeclaration*> FunctionList;
typedef std::vector<NVariableDeclaration*> VariableList;

// Controls how many spacing characters to print at each level of the tree
#define INDENTSIZE 5

class Node {
public:
	virtual ~Node() {}
	//virtual llvm::Value* codeGen(CodeGenContext& context) { return NULL; }

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

        /**
         * Returns a string of the demangled class name
         */
        std::string getType() const {
                int status = 0;
                char *type = abi::__cxa_demangle(typeid(*this).name(), 0,0, &status);
                return std::string(type);
        };
};

class NVariableDeclaration : public Node {
public:
        virtual std::string print(int level) const {
                return std::string("");
        };
};

class NFunctionDeclaration : public Node {
public:
        virtual std::string print(int level) const {
                return std::string("");
        };
};

class NInteger : public NExpression {
public:
	long long value;
	NInteger(long long value) : value(value) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        
        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<INTEGER>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%lld", value);

                out.append(pindent(level+1, "-"));
                out.append(tmp);
                out.append("\n");
                return out;
        };
        
};

class NDouble : public NExpression {
public:
 	double value;
	NDouble(double value) : value(value) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<DOUBLE>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%f", value);

                out.append(pindent(level+1, "-"));
                out.append(tmp);
                out.append("\n");
                return out;
        };
};

class NIdentifier : public NExpression {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<IDENTIFIER>\n");
                out.append(pindent(level+1, "-"));
                out.append(this->name);
                out.append("\n");
                return out;
        };
};

class NType : public NExpression {
public:
	std::string name;
	NType(const std::string& name) : name(name) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<TYPE>\n");
                out.append(pindent(level+1, "-"));
                out.append(this->name);
                out.append("\n");
                return out;
        };
};

class NMethodCall : public NExpression {
public:
	const NIdentifier& id;
	ExpressionList arguments;
	NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
		id(id), arguments(arguments) { }
	NMethodCall(const NIdentifier& id) : id(id) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);


        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<FUNCTION CALL>\n");
                level ++;
                out.append(id.print(level));

                for (auto argument : arguments) {
                        out.append("\n");
                        out.append(argument->print(level));
                }
                out.append("\n");
                                
                return out;
                
        };
};

class NBinaryOperator : public NExpression {
public:
	int op;
	NExpression& lhs;
	NExpression& rhs;
	NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
		lhs(lhs), rhs(rhs), op(op) { }
	// llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<BIN OP>\n");
                
                char tmp[128];
                snprintf(tmp, 128, "%d", op);
                
                out.append(lhs.print(level+1));
                
                out.append(pindent(level+1, "-"));
                out.append("<OPERATOR>\n");
                out.append(pindent(level+2, "-"));
                out.append(tmp);
                out.append("\n");

                out.append(rhs.print(level+1));

                return out;
        };
};

class NAssignment : public NExpression {
public:
	NIdentifier& lhs;
	NExpression& rhs;
	NAssignment(NIdentifier& lhs, NExpression& rhs) : 
		lhs(lhs), rhs(rhs) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<ASSIGNMENT>\n");
                out.append(lhs.print(level+1));
                out.append(rhs.print(level+1));

                return out;
        };
        
};

class NBlock : public NExpression {
public:
	StatementList statements;
	NBlock() { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));
                out.append("<BLOCK>\n");
                level ++;
                
                for (NStatement *statement : this->statements) {
                        out.append(statement->print(level));
                        out.append("\n");
                }
                
                return out;
        };
};

class NExpressionStatement : public NStatement {
public:
	NExpression& expression;
	NExpressionStatement(NExpression& expression) : 
		expression(expression) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<EXPR STATEMENT>\n");
                out.append(expression.print(level+1));

                return out;
        };
};

class NReturnStatement : public NStatement {
public:
	NExpression& expression;
	NReturnStatement(NExpression& expression) : 
		expression(expression) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));
                
                out.append("<RETURN>\n");
                out.append(expression.print(level+1));

                return out;
        };
       
};

class NIfStatement : public NStatement {
public:
	NBlock& block;
	NExpression& expression;
	NIfStatement(NExpression& expression, NBlock& block) : 
		expression(expression), block(block) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));
                
                out.append("<IF STATEMENT>\n");
                out.append(expression.print(level+1));
                out.append(block.print(level+1));
                
                return out;
        };
        
};

class NWhileStatement : public NStatement {
public:
	NBlock& block;
	NExpression& expression;
	NWhileStatement(NExpression& expression, NBlock& block) : 
		expression(expression), block(block) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);


        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));
                
                out.append("<WHILE STATEMENT>\n");
                out.append(expression.print(level+1));
                out.append(block.print(level+1));
                
                return out;
        };
        
};


class NElseStatement : public NStatement {
public:
	NBlock& block;
	NElseStatement(NBlock& block) : 
		block(block) { }
	//virtual llvm::Value* codeGen(CodeGenContext& context);

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));
                
                out.append("<ELSE STATEMENT>\n");
                out.append(block.print(level+1));
                
                return out;
        };
};

class NForStatement : public NStatement {
public:
	NBlock& block;
	NForStatement(NBlock& block) :
		block(block) {}
	
	std::string print(int level) const {
		std::string out;
		out.append(pindent(level, "-"));
		out.append("<FOR STATEMENT>\n");
		out.append(block.print(level+1);
	};
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

        
       std::string print(int level) const {
               std::string out;
               out.append(pindent(level, "-"));

               out.append("<VAR DECL>\n");
               out.append(type.print(level+1));
               out.append(id.print(level+1));

               return out;
       };
};


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

        std::string print(int level) const {
                std::string out;
                out.append(pindent(level, "-"));

                out.append("<FUNCTION DECL>\n");
                level ++;
                out.append(type.print(level));
                out.append(id.print(level));
                                
                for (auto argument : arguments) {
                        out.append("\n");
                        out.append(argument->print(level));
                }
                out.append("\n");

                out.append(block.print(level));
                                
                return out;
                
        };
};

