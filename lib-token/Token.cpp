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
        }
    }

std::ostream & operator<<(std::ostream & out, const TokenClass & tc) {
    out << "Type=" << static_cast<int>(tc.GetTokenType())
        << " Name=" << tc.GetTokenTypeName()
        << " Lexeme=\"" << tc.GetLexeme() << "\"";
    return out;
}
