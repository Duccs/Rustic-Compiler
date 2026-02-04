#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

#include "Token.h"

enum MachineState{
    START_STATE,                    //0
    IDENTIFIER_STATE,               //1
    INTEGER_STATE,                  //2
    LESS_STATE,                     //3
    LESSEQUAL_STATE,                //4
    GREATER_STATE,                  //5
    GREATEREQUAL_STATE,             //6
    EQUAL_STATE,                    //7
    NOT_STATE,                      //8
    NOTEQUAL_STATE,                 //9
    INSERTION_STATE,                //10
    ASSIGNMENT_STATE,               //11
    PLUS_STATE,                     //12
    MINUS_STATE,                    //13
    TIMES_STATE,                    //14
    DIVIDE_STATE,                   //15
    SEMICOLON_STATE,                //16
    LPAREN_STATE,                   //17
    RPAREN_STATE,                   //18
    LCURLY_STATE,                   //19
    RCURLY_STATE,                   //20
    
    CANTMOVE_STATE,
    ENDFILE_STATE,
    LAST_STATE
};

enum CharacterType{
    LETTER_CHAR,
    DIGIT_CHAR,
    WHITESPACE_CHAR,
    LESS_CHAR,
    LESS_EQUAL_CHAR,
    GREATER_CHAR,
    GREATER_EQUAL_CHAR,
    EQUAL_CHAR,
    NOT_CHAR,
    INSERTION_CHAR,
    ASSIGN_CHAR,
    PLUS_CHAR,
    MINUS_CHAR,
    TIMES_CHAR,
    DIVIDE_CHAR,
    SEMICOLON_CHAR,
    LPAREN_CHAR,
    RPAREN_CHAR,
    LCURLY_CHAR,
    RCURLY_CHAR,

    BAD_CHAR,
    ENDFILE_CHAR,
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
        MachineState UpdateState(char currentCharacter, TokenType &previousTokenType);
};

#endif /* _STATEMACHINE_H */