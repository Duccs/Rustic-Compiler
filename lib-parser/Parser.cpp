#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable) {
    mScanner = scanner;
    mSymbolTable = symbolTable;
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass token = mScanner->GetNextToken();

    if (token.GetTokenType() != expectedType) {
        std::cerr << "Syntax error on line " << mScanner->GetLineNumber() 
                  << ": Expected token type " << expectedType 
                  << " but found " << token.GetTokenType() << std::endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " <<
        token.GetTokenTypeName() << ". Lexeme: \"" <<
        token.GetLexeme() << "\"");
    return token;
}

void ParserClass::Start() {
    Program();
    Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    Block();
}

void ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroup();
    Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == RCURLY_TOKEN)
        {
            return;
        }
        else
        {
            Statement();
        }
    }
}

void ParserClass::Statement() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == INT_TOKEN)
    {
        Match(INT_TOKEN);
        Match(IDENTIFIER_TOKEN);
        Match(SEMICOLON_TOKEN);
    }
    else if(tt == IDENTIFIER_TOKEN)
    {
        Match(IDENTIFIER_TOKEN);
        Match(ASSIGNMENT_TOKEN);
        Relational();
        Match(SEMICOLON_TOKEN);
    }
    else if(tt == COUT_TOKEN)
    {
        Match(COUT_TOKEN);
        Match(INSERTION_TOKEN);
        Relational();
        Match(SEMICOLON_TOKEN);
    }
    else if (tt == LCURLY_TOKEN)
    {
        Block();
    }
    else
    {
        std::cerr << "Syntax error on line " << mScanner->GetLineNumber() 
                  << ": Unexpected token type " << tt << std::endl;
        exit(1);
    }
    StatementGroup();
}

void ParserClass::Expression() {
    Relational();
}

void ParserClass::Relational() {
    PlusMinus();

    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == LESS_TOKEN)
    {
        Match(tt);
        PlusMinus();
    }
    else if(tt == LESSEQUAL_TOKEN)
    {
        Match(tt);
        PlusMinus();
    }
    else if(tt == GREATER_TOKEN)
    {
        Match(tt);
        PlusMinus();
    }
    else if(tt == GREATEREQUAL_TOKEN)
    {
        Match(tt);
        PlusMinus();
    }
    else if(tt == EQUAL_TOKEN)
    {
        Match(tt);
        PlusMinus();
    }
    else if(tt == NOTEQUAL_TOKEN)
    {
        Match(tt);
        PlusMinus();
    }
    return;
}

void ParserClass::PlusMinus() {
    TimesDivide();

    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == PLUS_TOKEN)
        {
            Match(tt);
            TimesDivide();
        }
        else if(tt == MINUS_TOKEN)
        {
            Match(tt);
            TimesDivide();
        }
        else
        {
            return;
        }
    }
}

void ParserClass::TimesDivide() {
    Factor();

    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == TIMES_TOKEN)
        {
            Match(tt);
            Factor();
        }
        else if(tt == DIVIDE_TOKEN)
        {
            Match(tt);
            Factor();
        }
        else
        {
            return;
        }
    }
}

void ParserClass::Factor() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == IDENTIFIER_TOKEN)
    {
        Match(IDENTIFIER_TOKEN);
    }
    else if(tt == INTEGER_TOKEN)
    {
        Match(INTEGER_TOKEN);
    }
    else if(tt == LPAREN_TOKEN)
    {
        Match(LPAREN_TOKEN);
        Expression();
        Match(RPAREN_TOKEN);
    }
    else
    {
        std::cerr << "Syntax error on line " << mScanner->GetLineNumber() 
                  << ": Unexpected token type " << tt << std::endl;
        exit(1);
    }
}