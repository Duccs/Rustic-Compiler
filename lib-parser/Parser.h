#ifndef _PARSER_H
#define _PARSER_H

#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"

class ParserClass {
    private:
        ScannerClass* mScanner;
        SymbolTableClass* mSymbolTable;

        TokenClass Match(TokenType expectedType);

        // Nonterminal methods
        ProgramNode* Program();
        BlockNode* Block();
        StatementGroupNode* StatementGroup();
        StatementNode* Statement();
        DeclarationStatementNode* DeclarationStatment();
        AssignmentStatementNode* AssignmentStatement();
        CoutStatementNode* CoutStatement();
        IfStatementNode* IfStatement();
        WhileStatementNode* WhileStatement();
        BreakStatementNode* BreakStatement();
        ContinueStatementNode* ContinueStatement();
        ExpressionNode* Expression();
        IntegerNode* Integer();
        IdentifierNode* Identifier();
        ExpressionNode* Or();
        ExpressionNode* And();
        ExpressionNode* Relational();
        ExpressionNode* PlusMinus();
        ExpressionNode* TimesDivide();
        ExpressionNode* Factor();


    public:
        ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable);
        StartNode* Start();
};

#endif /* _PARSER_H */