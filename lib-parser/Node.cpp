#include "Node.h"

// StartNode implementation
StartNode::StartNode(ProgramNode* program) : mProgram(program) {}
StartNode::~StartNode() {
    delete mProgram;
}

// ProgramNode implementation
ProgramNode::ProgramNode(BlockNode* block) : mBlock(block) {}
ProgramNode::~ProgramNode() {
    delete mBlock;
}

// BlockNode implementation
BlockNode::BlockNode(StatementGroupNode* statementGroup) : mStatementGroup(statementGroup) {}
BlockNode::~BlockNode() {
    delete mStatementGroup;
}

// StatementGroupNode implementation
StatementGroupNode::~StatementGroupNode() {
    for (StatementNode* stmt : mStatements) {
        delete stmt;
    }
}
void StatementGroupNode::AddStatement(StatementNode* statement) {
    mStatements.push_back(statement);
}

// DeclarationStatementNode implementation
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* id) : identifier(id) {}
DeclarationStatementNode::~DeclarationStatementNode() {
    delete identifier;
}

// AssignmentStatementNode implementation
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* id, ExpressionNode* expr) 
: identifier(id), expression(expr) {}
AssignmentStatementNode::~AssignmentStatementNode() {
    delete identifier;
    delete expression;
    
}

// CoutStatementNode implementation
CoutStatementNode::CoutStatementNode(ExpressionNode* expr) : expression(expr) {}
CoutStatementNode::~CoutStatementNode() {
    delete expression;
}

// IntegerNode implementation
IntegerNode::IntegerNode(int value) : mValue(value) {}
int IntegerNode::Evaluate() const {
    return mValue;
}

// IdentifierNode implementation
IdentifierNode::IdentifierNode(const std::string& label, SymbolTableClass* symbolTable) 
: mLabel(label), mSymbolTable(symbolTable) {}
void IdentifierNode::DeclareVariable() {
    mSymbolTable->AddEntry(mLabel);
}
void IdentifierNode::SetValue(int v) {
    mSymbolTable->SetValue(mLabel, v);
}
int IdentifierNode::GetIndex() const {
    return mSymbolTable->GetIndex(mLabel);
}
int IdentifierNode::Evaluate() const {
    return mSymbolTable->GetValue(mLabel);
}

// BinaryOperatorNode implementation
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right) : mLeftExpr(left), mRightExpr(right) {}
BinaryOperatorNode::~BinaryOperatorNode() {
    delete mLeftExpr;
    delete mRightExpr;
}

// PlusNode implementation
PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int PlusNode::Evaluate() const {
    return mLeftExpr->Evaluate() + mRightExpr->Evaluate();
}

// MinusNode implementation
MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int MinusNode::Evaluate() const {
    return mLeftExpr->Evaluate() - mRightExpr->Evaluate();
}

// TimesNode implementation
TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int TimesNode::Evaluate() const {
    return mLeftExpr->Evaluate() * mRightExpr->Evaluate();
}

// DivideNode implementation
DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int DivideNode::Evaluate() const {
    int denominator = mRightExpr->Evaluate();
    if (denominator == 0) {
        throw std::runtime_error("Division by zero");
    }
    return mLeftExpr->Evaluate() / denominator;
}

// LessNode implementation
LessNode::LessNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int LessNode::Evaluate() const {
    return (mLeftExpr->Evaluate() < mRightExpr->Evaluate()) ? 1 : 0;
}

// LessEqualNode implementation
LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int LessEqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() <= mRightExpr->Evaluate()) ? 1 : 0;
}

// GreaterNode implementation
GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int GreaterNode::Evaluate() const {
    return (mLeftExpr->Evaluate() > mRightExpr->Evaluate()) ? 1 : 0;
}

// GreaterEqualNode implementation
GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int GreaterEqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() >= mRightExpr->Evaluate()) ? 1 : 0;
}

// EqualNode implementation
EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int EqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() == mRightExpr->Evaluate()) ? 1 : 0;
}

// NotEqualNode implementation
NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int NotEqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() != mRightExpr->Evaluate()) ? 1 : 0;
}