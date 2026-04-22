#include "Node.h"

// StartNode implementation
StartNode::StartNode(ProgramNode* program) : mProgram(program) {}
StartNode::~StartNode() {
    delete mProgram;
}
void StartNode::Interpret(){
    mProgram->Interpret();
}
void StartNode::Code(InstructionsClass &machineCode)
{
    mProgram->Code(machineCode);
}

// ProgramNode implementation
ProgramNode::ProgramNode(BlockNode* block) : mBlock(block) {}
ProgramNode::~ProgramNode() {
    delete mBlock;
}
void ProgramNode::Interpret(){
    mBlock->Interpret();
}
void ProgramNode::Code(InstructionsClass &machineCode)
{
    mBlock->Code(machineCode);
}


// BlockNode implementation
BlockNode::BlockNode(StatementGroupNode* statementGroup, SymbolTableClass* symbolTable)
    : mStatementGroup(statementGroup), mSymbolTable(symbolTable) {}
BlockNode::~BlockNode() {
    delete mStatementGroup;
}
void BlockNode::Interpret(){
    mSymbolTable->PushScope();
    try {
        mStatementGroup->Interpret();
    } catch (...) {
        mSymbolTable->PopScope();
        throw;
    }
    mSymbolTable->PopScope();
}
void BlockNode::Code(InstructionsClass &machineCode)
{
    mSymbolTable->PushScope();
    mStatementGroup->Code(machineCode);
    mSymbolTable->PopScope();
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
void StatementGroupNode::Interpret(){
    for (auto &s: mStatements){
        s->Interpret();
    }
}
void StatementGroupNode::Code(InstructionsClass &machineCode)
{
    for (auto &s: mStatements){
        s->Code(machineCode);
    }
}

// DeclarationStatementNode implementation
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* id) : identifier(id) {}
DeclarationStatementNode::~DeclarationStatementNode() {
    delete identifier;
}
void DeclarationStatementNode::Interpret(){
    identifier->DeclareVariable();
}
void DeclarationStatementNode::Code(InstructionsClass &machineCode)
{
    identifier->DeclareVariable();
}

// AssignmentStatementNode implementation
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* id, ExpressionNode* expr) 
: identifier(id), expression(expr) {}
AssignmentStatementNode::~AssignmentStatementNode() {
    delete identifier;
    delete expression;
    
}
void AssignmentStatementNode::Interpret(){
    int v = expression->Evaluate();
    identifier->SetValue(v);
}
void AssignmentStatementNode::Code(InstructionsClass &machineCode)
{
    expression->CodeEvaluate(machineCode);
    int index = identifier->GetIndex();
    machineCode.PopAndStore(index);
}

// PlusEqualStatementNode implementation
PlusEqualStatementNode::PlusEqualStatementNode(IdentifierNode* id, ExpressionNode* expr) 
: AssignmentStatementNode(id, expr) {}
void PlusEqualStatementNode::Interpret(){
    int v = expression->Evaluate();
    int curr = identifier->Evaluate();
    identifier->SetValue(curr + v);
}
void PlusEqualStatementNode::Code(InstructionsClass &machineCode)
{
    int index = identifier->GetIndex();
    machineCode.PushVariable(index);
    expression->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
    machineCode.PopAndStore(index);
}

// MinusEqualStatementNode implementation
MinusEqualStatementNode::MinusEqualStatementNode(IdentifierNode* id, ExpressionNode* expr) 
: AssignmentStatementNode(id, expr) {}
void MinusEqualStatementNode::Interpret(){
    int v = expression->Evaluate();
    int curr = identifier->Evaluate();
    identifier->SetValue(curr - v);
}
void MinusEqualStatementNode::Code(InstructionsClass &machineCode)
{
    int index = identifier->GetIndex();
    machineCode.PushVariable(index);
    expression->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
    machineCode.PopAndStore(index);
}

// CoutStatementNode implementation
CoutStatementNode::~CoutStatementNode() {
    for (ExpressionNode* expr : expressions) {
        delete expr;
    }
}
void CoutStatementNode::AddExpression(ExpressionNode* expression) {
    expressions.push_back(expression);
}
void CoutStatementNode::Interpret(){
    for (ExpressionNode* expression : expressions) {
        if (expression == nullptr) {
            std::cout << std::endl;
            continue;
        }
        int v = expression->Evaluate();
        std::cout << v << " ";
    }
}
void CoutStatementNode::Code(InstructionsClass &machineCode)
{
    for (ExpressionNode* expression : expressions) {
        if (expression == nullptr) {
            machineCode.WriteEndlLinux64();
            continue;
        }
    expression->CodeEvaluate(machineCode);
    machineCode.PopAndWrite();
    }
}

// IfStatementNode implementation
IfStatementNode::IfStatementNode(ExpressionNode* cond, StatementNode* blk, IfStatementNode* els) : conditional(cond), ifBlock(blk), elsenode(els) {}
IfStatementNode::~IfStatementNode() {
    delete conditional;
    delete ifBlock;
    delete elsenode;
}
void IfStatementNode::Interpret(){
    if (conditional->Evaluate()) {
        ifBlock->Interpret();
    } else if (elsenode != nullptr) {
        elsenode->Interpret();
    }
}
void IfStatementNode::Code(InstructionsClass &machineCode)
{
    conditional->CodeEvaluate(machineCode);
    unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char * address1 = machineCode.GetAddress();
    ifBlock->Code(machineCode);
    unsigned char * address2 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress, (int)(address2-address1));
}

// WhileStatementNode implementation
WhileStatementNode::WhileStatementNode(ExpressionNode* cond, StatementNode* blk) : conditional(cond), block(blk) {}
WhileStatementNode::~WhileStatementNode() {
    delete conditional;
    delete block;
}
void WhileStatementNode::Interpret(){
    while (conditional->Evaluate()) {
        try{
            block->Interpret();
        } catch (const ContinueException& e) {
            continue;
        } catch (const BreakException& e) {
            break;
        }
    }
}
void WhileStatementNode::Code(InstructionsClass &machineCode)
{
    unsigned char * address1 = machineCode.GetAddress();
    conditional->CodeEvaluate(machineCode);
    unsigned char * InsertAddressToSkip = machineCode.SkipIfZeroStack();
    unsigned char * address2 = machineCode.GetAddress();
    block->Code(machineCode);
    unsigned char * InsertAddressToJump = machineCode.Jump();
    unsigned char * address3 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddressToSkip, (int)(address3-address2));
    machineCode.SetOffset(InsertAddressToJump, (int)(address1-address3));
}

// BreakStatementNode implementation
void BreakStatementNode::Interpret() {
    throw BreakException();
}
void BreakStatementNode::Code(InstructionsClass &machineCode)
{
    // unsigned char * callAddress = machineCode.GetAddress();
    // unsigned char * InsertAddressToSkip = machineCode.SkipIfZeroStack();
    // // Addresss of the first instruction after the loop
    // unsigned char * afterLoopAddress = machineCode.GetAddress();
    // machineCode.SetOffset(InsertAddressToSkip, (int)(afterLoopAddress-callAddress));
    return;
}
// ContinueStatementNode implementation
void ContinueStatementNode::Interpret() {
    throw ContinueException();
}
void ContinueStatementNode::Code(InstructionsClass &machineCode)
{
    // unsigned char * callAddress = machineCode.GetAddress();
    // unsigned char * InsertAddressToJump = machineCode.Jump();
    // // Addresss of the first instruction before the loop condition
    // unsigned char * beforeLoopAddress = machineCode.GetAddress();
    // machineCode.SetOffset(InsertAddressToJump, (int)(beforeLoopAddress-callAddress));
    return; 
}

// IntegerNode implementation
IntegerNode::IntegerNode(int value) : mValue(value) {}
int IntegerNode::Evaluate() const {
    return mValue;
}
void IntegerNode::CodeEvaluate(InstructionsClass &machineCode)
{
    machineCode.PushValue(mValue);
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
void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode)
{
    machineCode.PushVariable(this->GetIndex());
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
void PlusNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}

// MinusNode implementation
MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int MinusNode::Evaluate() const {
    return mLeftExpr->Evaluate() - mRightExpr->Evaluate();
}
void MinusNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}


// TimesNode implementation
TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int TimesNode::Evaluate() const {
    return mLeftExpr->Evaluate() * mRightExpr->Evaluate();
}
void TimesNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
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
void DivideNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

// LessNode implementation
LessNode::LessNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int LessNode::Evaluate() const {
    return (mLeftExpr->Evaluate() < mRightExpr->Evaluate()) ? 1 : 0;
}
void LessNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

// LessEqualNode implementation
LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int LessEqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() <= mRightExpr->Evaluate()) ? 1 : 0;
}
void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

// GreaterNode implementation
GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int GreaterNode::Evaluate() const {
    return (mLeftExpr->Evaluate() > mRightExpr->Evaluate()) ? 1 : 0;
}
void GreaterNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

// GreaterEqualNode implementation
GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int GreaterEqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() >= mRightExpr->Evaluate()) ? 1 : 0;
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}

// EqualNode implementation
EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int EqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() == mRightExpr->Evaluate()) ? 1 : 0;
}
void EqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

// NotEqualNode implementation
NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int NotEqualNode::Evaluate() const {
    return (mLeftExpr->Evaluate() != mRightExpr->Evaluate()) ? 1 : 0;
}
void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
}


// AndNode implementation
AndNode::AndNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int AndNode::Evaluate() const {
    return (mLeftExpr->Evaluate() && mRightExpr->Evaluate()) ? 1 : 0;
}
void AndNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

// OrNode implementation
OrNode::OrNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {}
int OrNode::Evaluate() const {
    return (mLeftExpr->Evaluate() || mRightExpr->Evaluate()) ? 1 : 0;
}
void OrNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeftExpr->CodeEvaluate(machineCode);
    mRightExpr->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}