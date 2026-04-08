#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable) {
    mScanner = scanner;
    mSymbolTable = symbolTable;
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass token = mScanner->GetNextToken();

    if (token.GetTokenType() != expectedType) {
        std::cerr << "While matching token. Syntax error on line " << mScanner->GetLineNumber() 
                  << ": Expected token type " << expectedType 
                  << " but found " << token.GetTokenType() << std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " <<
        token.GetTokenTypeName() << ". Lexeme: \"" <<
        token.GetLexeme() << "\"");
    return token;
}

StartNode* ParserClass::Start() {
    ProgramNode* pn = Program();
    Match(ENDFILE_TOKEN);
    StartNode* sn = new StartNode(pn);
    return sn;
}

ProgramNode* ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode* bn = Block();
    ProgramNode* pn = new ProgramNode(bn);
    return pn;
}

BlockNode* ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroupNode* sgn = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode* bn = new BlockNode(sgn);
    return bn;
}

StatementGroupNode* ParserClass::StatementGroup() {
    StatementGroupNode* sgn = new StatementGroupNode();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == RCURLY_TOKEN)
        {
            return sgn;
        }
        else
        {
            StatementNode* sn = Statement();
            sgn->AddStatement(sn);
        }
    }
}

StatementNode* ParserClass::Statement() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == INT_TOKEN)
    {
        return DeclarationStatment();
    }
    else if(tt == IDENTIFIER_TOKEN)
    {
        return AssignmentStatement();
    }
    else if(tt == COUT_TOKEN)
    {
        return CoutStatement();
    }
    else if (tt == IF_TOKEN) 
    {
        return IfStatement();
    } 
    else if (tt == WHILE_TOKEN) 
    {
        return WhileStatement();
    } 
    else if (tt == BREAK_TOKEN) 
    {
        return BreakStatement();
    } 
    else if (tt == CONTINUE_TOKEN) 
    {
        return ContinueStatement();
    }    
    else if (tt == LCURLY_TOKEN)
    {
        return Block();
    } 
    else
    {
        std::cerr << "While Parsing Statement. Syntax error on line " << mScanner->GetLineNumber() 
                  << ": Unexpected token type " << tt << std::endl;
        exit(1);
    }
    StatementGroup();
}

DeclarationStatementNode* ParserClass::DeclarationStatment(){
    Match(INT_TOKEN);
    IdentifierNode* idn = Identifier();
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode* dsn = new DeclarationStatementNode(idn);
    return dsn;

}

AssignmentStatementNode* ParserClass::AssignmentStatement(){
    IdentifierNode* idn = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode* en = Or();
    Match(SEMICOLON_TOKEN);
    AssignmentStatementNode* asn = new AssignmentStatementNode(idn, en);
    return asn;
}

CoutStatementNode* ParserClass::CoutStatement(){
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode* en = Or();
    Match(SEMICOLON_TOKEN);
    CoutStatementNode* csn = new CoutStatementNode(en);
    return csn;
}

IfStatementNode* ParserClass::IfStatement() {
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* conditional = Or();
    Match(RPAREN_TOKEN);
    BlockNode* ifBlock = Block();
    IfStatementNode* elsenode = nullptr;
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == ELSE_TOKEN) {
        Match(ELSE_TOKEN);

        tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == IF_TOKEN) {
            elsenode = IfStatement();
        } else if (tt == LCURLY_TOKEN) {
            BlockNode* elseBlock = Block();
            IntegerNode* trueCondition = new IntegerNode(1); // Always true
            elsenode = new IfStatementNode(trueCondition, elseBlock, nullptr);
        }
    }
    IfStatementNode* ifsn = new IfStatementNode(conditional, ifBlock, elsenode);
    return ifsn;
}

WhileStatementNode* ParserClass::WhileStatement() {
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* conditional = Or();
    Match(RPAREN_TOKEN);
    BlockNode* block = Block();
    WhileStatementNode* wsn = new WhileStatementNode(conditional, block);
    return wsn;
}

BreakStatementNode* ParserClass::BreakStatement() {
    Match(BREAK_TOKEN);
    Match(SEMICOLON_TOKEN);
    return new BreakStatementNode();
}

ContinueStatementNode* ParserClass::ContinueStatement() {
    Match(CONTINUE_TOKEN);
    Match(SEMICOLON_TOKEN);
    return new ContinueStatementNode();
}

ExpressionNode* ParserClass::Expression() {
    ExpressionNode* en = Or();
    return en;
}

IntegerNode* ParserClass::Integer(){
    TokenClass intToken = Match(INTEGER_TOKEN);
    int value = std::stoi(intToken.GetLexeme());
    IntegerNode* intn = new IntegerNode(value);
    return intn;
}

IdentifierNode* ParserClass::Identifier(){
    TokenClass idnToken = Match(IDENTIFIER_TOKEN);
    IdentifierNode* idn = new IdentifierNode(idnToken.GetLexeme(), mSymbolTable);
    return idn;
}

ExpressionNode* ParserClass::Or() {
    ExpressionNode* current = And();

    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == OR_TOKEN) {
            Match(tt);
            current = new OrNode(current, And());
        } else {
            return current;
        }
    }
}

ExpressionNode* ParserClass::And() {
    ExpressionNode* current = Relational();

    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == AND_TOKEN) {
            Match(tt);
            current = new AndNode(current, Relational());
        } else {
            return current;
        }
    }
}

ExpressionNode* ParserClass::Relational() {
    ExpressionNode* current = PlusMinus();

    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == LESS_TOKEN)
    {
        Match(tt);
        current = new LessNode(current, PlusMinus());
    }
    else if(tt == LESSEQUAL_TOKEN)
    {
        Match(tt);
        current = new LessEqualNode(current, PlusMinus());

    }
    else if(tt == GREATER_TOKEN)
    {
        Match(tt);
        current = new GreaterNode(current, PlusMinus());
    }
    else if(tt == GREATEREQUAL_TOKEN)
    {
        Match(tt);
        current = new GreaterEqualNode(current, PlusMinus());
    }
    else if(tt == EQUAL_TOKEN)
    {
        Match(tt);
        current = new EqualNode(current, PlusMinus());
    }
    else if(tt == NOTEQUAL_TOKEN)
    {
        Match(tt);
        current = new NotEqualNode(current, PlusMinus());
    }
    return current;
}

ExpressionNode* ParserClass::PlusMinus() {
    ExpressionNode* current = TimesDivide();

    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == PLUS_TOKEN)
        {
            Match(tt);
            current = new PlusNode(current, TimesDivide());
        }
        else if(tt == MINUS_TOKEN)
        {
            Match(tt);
            current = new MinusNode(current, TimesDivide());
        }
        else
        {
            return current;
        }
    }
}

ExpressionNode* ParserClass::TimesDivide() {
    ExpressionNode* current = Factor();

    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == TIMES_TOKEN)
        {
            Match(tt);
            current = new TimesNode(current, Factor());
        }
        else if(tt == DIVIDE_TOKEN)
        {
            Match(tt);
            current = new DivideNode(current, Factor());
        }
        else
        {
            return current;
        }
    }
}

ExpressionNode* ParserClass::Factor() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == IDENTIFIER_TOKEN)
    {
        return Identifier();
    }
    else if(tt == INTEGER_TOKEN)
    {
        return Integer();
    }
    else if(tt == LPAREN_TOKEN)
    {
        Match(LPAREN_TOKEN);
        ExpressionNode* en = Expression();
        Match(RPAREN_TOKEN);
        return en;
    }
    else
    {
        std::cerr << "While Parsing Factor. Syntax error on line " << mScanner->GetLineNumber() 
                  << ": Unexpected token type " << tt << std::endl;
        exit(1);
    }
}