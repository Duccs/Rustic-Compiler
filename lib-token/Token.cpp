#include "Token.h"
#include <ostream>

TokenClass::TokenClass(TokenType type, const std::string &lexeme)
    : mtype(type), mlexeme(lexeme) {
        //Check for reserved words
        if (lexeme == "void"){
            mtype = VOID_TOKEN;
        } else if (lexeme == "main"){
            mtype = MAIN_TOKEN;
        } else if (lexeme == "int"){
            mtype = INT_TOKEN;
        } else if (lexeme == "cout"){
            mtype = COUT_TOKEN; 
        } else if (lexeme == "if"){
            mtype = IF_TOKEN;
        } else if (lexeme == "else"){
            mtype = ELSE_TOKEN;
        } else if (lexeme == "while"){
            mtype = WHILE_TOKEN;
        } else if (lexeme == "break"){
            mtype = BREAK_TOKEN;
        } else if (lexeme == "continue"){
            mtype = CONTINUE_TOKEN;
        } else if (lexeme == "do"){
            mtype = DO_TOKEN;
        } else if (lexeme == "print"){
            mtype = PRINT_TOKEN;
        } else if (lexeme == "endl"){
            mtype = ENDL_TOKEN;
        }
    }

std::ostream & operator<<(std::ostream & out, const TokenClass & tc) {
    out << " Name=" << tc.GetTokenTypeName()
        << " Lexeme=\"" << tc.GetLexeme() << "\"";
    return out;
}
