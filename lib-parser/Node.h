#ifndef _NODE_H_
#define _NODE_H_

#include <Symbol.h>
#include <Instructions.h>
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
class PlusEqualStatementNode;
class MinusEqualStatementNode;
class CoutStatementNode;
class IfStatementNode;
class WhileStatementNode;
class BreakStatementNode;
class ContinueStatementNode;
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
class AndNode;
class OrNode;

// Control flow:
class BreakException : public std::exception {
public:
    const char* what() const noexcept override { return "break"; }
};

class ContinueException : public std::exception {
public:
    const char* what() const noexcept override { return "continue"; }
};


// Node class hierarchy:
class Node {
    public:
        virtual ~Node() = default;
        virtual void Interpret() = 0;
        virtual void Code(InstructionsClass &machineCode) = 0;
};

class StartNode : public Node {
    private:
        ProgramNode* mProgram;
    public:
        StartNode(ProgramNode* program);
        ~StartNode() override;
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class ProgramNode : public Node {
    private:
        BlockNode* mBlock;
    public:
        ProgramNode(BlockNode* block);
        ~ProgramNode() override;
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class StatementGroupNode : public Node {
    private:
        std::vector<StatementNode*> mStatements;
    public:
        StatementGroupNode() = default;
        ~StatementGroupNode() override;
        void AddStatement(StatementNode* statement);
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
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
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class DeclarationStatementNode : public StatementNode {
    private:
        IdentifierNode* identifier;
    public:
        DeclarationStatementNode(IdentifierNode* identifier);
        ~DeclarationStatementNode() override;
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class AssignmentStatementNode : public StatementNode {
    protected:
        IdentifierNode* identifier;
        ExpressionNode* expression;
    public:
        AssignmentStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
        ~AssignmentStatementNode() override;
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class PlusEqualStatementNode : public AssignmentStatementNode {
    public:
        PlusEqualStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class MinusEqualStatementNode : public AssignmentStatementNode {
    public:
        MinusEqualStatementNode(IdentifierNode* identifier, ExpressionNode* expression);
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class CoutStatementNode : public StatementNode {
    private:
        std::vector<ExpressionNode*> expressions;
    public:
        CoutStatementNode() = default;
        ~CoutStatementNode() override;
        void AddExpression(ExpressionNode* expression);
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class IfStatementNode : public StatementNode {
    private:
        ExpressionNode* conditional;
        StatementNode* ifBlock;
        IfStatementNode* elsenode;  // Null if doesn't exist
    public:
        IfStatementNode(ExpressionNode* conditional, StatementNode* ifBlock, IfStatementNode* elsenode);
        ~IfStatementNode() override;
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class WhileStatementNode : public StatementNode {
    private:
        ExpressionNode* conditional;
        StatementNode* block;
    public:
        WhileStatementNode(ExpressionNode* conditional, StatementNode* block);
        ~WhileStatementNode() override;
        void Interpret() override;
        void Code(InstructionsClass &machineCode) override;
};

class BreakStatementNode : public StatementNode {
public:
    BreakStatementNode() = default;
    ~BreakStatementNode() override = default;
    void Interpret() override;
    void Code(InstructionsClass &machineCode) override;
};

class ContinueStatementNode : public StatementNode {
public:
    ContinueStatementNode() = default;
    ~ContinueStatementNode() override = default;
    void Interpret() override;
    void Code(InstructionsClass &machineCode) override;
};

class ExpressionNode {
    public:
        virtual ~ExpressionNode() = default;
        virtual int Evaluate() const = 0;
        virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;
};

class IntegerNode : public ExpressionNode {
    private:
        int mValue;
    public:
        IntegerNode(int value);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
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
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class BinaryOperatorNode : public ExpressionNode {
    protected:
        ExpressionNode* mLeftExpr;
        ExpressionNode* mRightExpr;
    public:
        BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
        virtual ~BinaryOperatorNode();
        virtual int Evaluate() const = 0;
        virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;
};

class PlusNode : public BinaryOperatorNode {
    public:
        PlusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class MinusNode : public BinaryOperatorNode {
    public:
        MinusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class TimesNode : public BinaryOperatorNode {
    public:
        TimesNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class DivideNode : public BinaryOperatorNode {
    public:
        DivideNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class LessNode : public BinaryOperatorNode {
    public:
        LessNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class LessEqualNode : public BinaryOperatorNode {
    public:
        LessEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class GreaterNode : public BinaryOperatorNode {
    public:
        GreaterNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class GreaterEqualNode : public BinaryOperatorNode {
    public:
        GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class EqualNode : public BinaryOperatorNode {
    public:
        EqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};
        
class NotEqualNode : public BinaryOperatorNode {
    public:
        NotEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class AndNode : public BinaryOperatorNode {
    public:
        AndNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

class OrNode : public BinaryOperatorNode {
    public:
        OrNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate() const override;
        void CodeEvaluate(InstructionsClass &machineCode) override;
};

#endif /* _NODE_H_ */