#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

#include "Token.h"

enum MachineState{
    START_STATE,                    //0

    // Comment States
    SINGLE_LINE_COMMENT_STATE,     // "//"
    COMMENT_OP_STATE,              // "/*"
    COMMENT_CL_STATE,              // "/* *"

    // Basic State types
    IDENTIFIER_STATE,               // "LETTERS"
    INTEGER_STATE,                  // "1234"

    // Comparison States
    LESS_STATE,                     // "<"
    LESSEQUAL_STATE,                // "<="
    GREATER_STATE,                  // ">"
    GREATEREQUAL_STATE,             // ">="
    EQUAL_STATE,                    // "=="
    NOT_STATE,                      // "!"
    NOTEQUAL_STATE,                 // "!="
    INSERTION_STATE,                // "<<"
    ASSIGNMENT_STATE,               // "="

    // Arithmetic States
    PLUS_STATE,                     // "+"
    MINUS_STATE,                    // "-"
    TIMES_STATE,                    // "*"
    DIVIDE_STATE,                   // "/"

    // Separator States
    SEMICOLON_STATE,                // ";"
    LPAREN_STATE,                   // "("
    RPAREN_STATE,                   // ")"
    LCURLY_STATE,                   // "{"
    RCURLY_STATE,                   // "}"
    
    // Special States
    CANTMOVE_STATE,
    ENDFILE_STATE,
    LAST_STATE
};

enum CharacterType{
    // Basic characters
    LETTER_CHAR,
    DIGIT_CHAR,
    WHITESPACE_CHAR,

    // Comparison characters
    LESS_CHAR,
    LESS_EQUAL_CHAR,
    GREATER_CHAR,
    GREATER_EQUAL_CHAR,
    EQUAL_CHAR,
    NOT_CHAR,
    INSERTION_CHAR,
    ASSIGN_CHAR,

    // Arthmetic characters
    PLUS_CHAR,
    MINUS_CHAR,
    TIMES_CHAR,
    DIVIDE_CHAR,

    // Separators
    SEMICOLON_CHAR,
    LPAREN_CHAR,
    RPAREN_CHAR,
    LCURLY_CHAR,
    RCURLY_CHAR,

    // Special characters
    BAD_CHAR,
    ENDFILE_CHAR,
    NEWLINE_CHAR,
    LAST_CHAR
};

class StateMachineClass {
    private:
        MachineState mcurrentState;
        
        // The matrix of legal moves:
        MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

        // Which end-machine-states correspond to which token types.
        // (non end states correspond to the BAD_TOKEN token type)
        TokenType mCorrespondingTokenTypes[LAST_STATE];

    public:
        StateMachineClass();
        MachineState UpdateState(int currentCharacter, TokenType &previousTokenType);
};

#endif /* _STATEMACHINE_H */