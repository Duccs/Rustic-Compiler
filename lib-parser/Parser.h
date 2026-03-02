#ifndef _PARSER_H
#define _PARSER_H

#include "Scanner.h"
#include "Symbol.h"

class ParserClass {
    private:
        ScannerClass* mScanner;
        SymbolTableClass* mSymbolTable;

        TokenClass Match(TokenType expectedType);

        // Nonterminal methods
        void Program();
        void Block();
        void StatementGroup();
        void Statement();
        void Expression();
        void Relational();
        void PlusMinus();
        void TimesDivide();
        void Factor();

    public:
        ParserClass(ScannerClass* scanner, SymbolTableClass* symbolTable);
        void Start();
};

#endif /* _PARSER_H */