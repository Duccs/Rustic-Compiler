#ifndef _NODE_H_
#define _NODE_H_

#include <Symbol.h>
#include <string>
#include <vector>

// forward declarations:
class Node;
class StartNode;
class ProgramNode;
class StatementGroupNode;
class StatementNode;
class BlockNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;

class Node {
    public:
        virtual ~Node() = default;
};

class StartNode : public Node {
    private:
        ProgramNode* mProgram;
    public:
        StartNode(ProgramNode* program);
        ~StartNode() override;
};

class ProgramNode : public Node {
    private:
        BlockNode* mBlock;
    public:
        ProgramNode(BlockNode* block);
        ~ProgramNode() override;
};

class StatementGroupNode : public Node {
    private:
        std::vector<StatementNode*> mStatements;
    public:
        StatementGroupNode() = default;
        ~StatementGroupNode() override;
        void AddStatement(StatementNode* statement);
};

class StatementNode : public Node {
    public:
        virtual ~StatementNode() = default;
};

class BlockNode : public StatementNode {
    private:
        StatementGroupNode* mStatementGroup;
    public:
        BlockNode(StatementGroupNode* statementGroup);
        ~BlockNode() override;
};

class DeclarationStatementNode : public StatementNode {
    private:
        IdentifierNode* identifier;
    public:
        DeclarationStatementNode(IdentifierNode* identifier);
        ~DeclarationStatementNode() override;
};

class AssignmentStatementNode : public StatementNode {
    private:
        IdentifierNode* identifier;
        ExpressionNode* expression;
    public:
        AssignmentStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
        ~AssignmentStatementNode() override;
};

class CoutStatementNode : public StatementNode {
    private:
        ExpressionNode* expression;
    public:
        CoutStatementNode(ExpressionNode* expression);
        ~CoutStatementNode() override;
};

class ExpressionNode {
    public:
        virtual ~ExpressionNode() = default;
        virtual int Evaluate() const = 0;
};

class IntegerNode : public ExpressionNode {
    private:
        int mValue;
    public:
        IntegerNode(int value);
        int Evaluate() const override;
};

class IdentifierNode : public ExpressionNode {
    private:
        std::string mLabel;
        SymbolTableClass* mSymbolTable;
    public:
        IdentifierNode(const std::string& label, SymbolTableClass* symbolTable);
        void DeclareVariable();
        void SetValue(int v);
        int GetIndex() const;
        int Evaluate() const override;
};

class BinaryOperatorNode : public ExpressionNode {
    protected:
        ExpressionNode* mLeftExpr;
        ExpressionNode* mRightExpr;
    public:
        BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
        virtual ~BinaryOperatorNode();
        virtual int Evaluate() const = 0;
};

class PlusNode : public BinaryOperatorNode {
    public:
        PlusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class MinusNode : public BinaryOperatorNode {
    public:
        MinusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class TimesNode : public BinaryOperatorNode {
    public:
        TimesNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class DivideNode : public BinaryOperatorNode {
    public:
        DivideNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class LessNode : public BinaryOperatorNode {
    public:
        LessNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class LessEqualNode : public BinaryOperatorNode {
    public:
        LessEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class GreaterNode : public BinaryOperatorNode {
    public:
        GreaterNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class GreaterEqualNode : public BinaryOperatorNode {
    public:
        GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

class EqualNode : public BinaryOperatorNode {
    public:
        EqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};
        
class NotEqualNode : public BinaryOperatorNode {
    public:
        NotEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
};

#endif /* _NODE_H_ */