#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>
#include <Debug.h>

enum TokenType {
    // Reserved Words:
    VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN,
    // Relational Operators:
    LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
    EQUAL_TOKEN, NOTEQUAL_TOKEN,
    // Other Operators:
    INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
    TIMES_TOKEN, DIVIDE_TOKEN,
    // Other Characters:
    SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
    RCURLY_TOKEN,
    // Other Token Types:
    IDENTIFIER_TOKEN, INTEGER_TOKEN,
    BAD_TOKEN, ENDFILE_TOKEN
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const std::string gTokenTypeNames[] = {
    "VOID", "MAIN", "INT", "COUT",
    "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL",
    "NOTEQUAL",
    "INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
    "SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
    "IDENTIFIER", "INTEGER",
    "BAD", "ENDFILE"
};

class TokenClass {
    private:
        TokenType mtype;
        std::string mlexeme;

    public:
        TokenClass(TokenType type, const std::string &lexeme);
        TokenType GetTokenType() const { return mtype; };
        const std::string& GetTokenTypeName() const {
            return gTokenTypeNames[mtype];
        };
        std::string GetLexeme() const { return mlexeme; };
        static const std::string& GetTokenTypeName(TokenType type) {
            return gTokenTypeNames[type];
        };

    
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);

#endif