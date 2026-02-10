#include "StateMachine.h"

StateMachineClass::StateMachineClass() {

    mcurrentState = START_STATE;

    // initialize all the mLegalMoves to CANTMOVE_STATE
    for (int state = 0; state < LAST_STATE; state++) {
        for (int charType = 0; charType < LAST_CHAR; ++charType) {
            mLegalMoves[state][charType] = CANTMOVE_STATE;
        }
    }

    // Define legal transitions

    // From START_STATE
    // ----------------
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;

    mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
    mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
    mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;
    mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;

    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
    mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
    
    mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;

    mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;

    // From IDENTIFIER_STATE
    // ---------------------
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;

    // From INTEGER_STATEs
    // -------------------
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;

    // Comment States
    // -----------------
    // Single line comment
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = SINGLE_LINE_COMMENT_STATE;
    for (int charType = 0; charType < LAST_CHAR; ++charType) {
        mLegalMoves[SINGLE_LINE_COMMENT_STATE][charType] = SINGLE_LINE_COMMENT_STATE;
    }
    mLegalMoves[SINGLE_LINE_COMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
    mLegalMoves[SINGLE_LINE_COMMENT_STATE][NEWLINE_CHAR] = START_STATE;

    // Multi-line comment
    mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = COMMENT_OP_STATE;
    for (int charType = 0; charType < LAST_CHAR; ++charType) {
        mLegalMoves[COMMENT_OP_STATE][charType] = COMMENT_OP_STATE;
    }
    mLegalMoves[COMMENT_OP_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
    mLegalMoves[COMMENT_OP_STATE][TIMES_CHAR] = COMMENT_CL_STATE;
    for (int charType = 0; charType < LAST_CHAR; ++charType) {
        mLegalMoves[COMMENT_CL_STATE][charType] = COMMENT_OP_STATE;
    }
    mLegalMoves[COMMENT_CL_STATE][TIMES_CHAR] = COMMENT_CL_STATE;
    mLegalMoves[COMMENT_CL_STATE][DIVIDE_CHAR] = START_STATE;

    // From OTHER
    // -------------------
    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;
    mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
    mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;
    mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;

    for(int i = 0; i < LAST_STATE; i++) {
        mCorrespondingTokenTypes[i] = BAD_TOKEN;
    }

    // Initialize corresponding token types
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;

    mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
    mCorrespondingTokenTypes[CANTMOVE_STATE] = BAD_TOKEN;
    mCorrespondingTokenTypes[START_STATE] = BAD_TOKEN;
}

MachineState StateMachineClass::UpdateState(int currentCharacter, TokenType &previousTokenType) {
    CharacterType charType = BAD_CHAR;

    // Determine character type
    if (isalpha(currentCharacter)) {
        charType = LETTER_CHAR;
    } else if (isdigit(currentCharacter)) {
        charType = DIGIT_CHAR;
    } else if (currentCharacter == '\n') {
        charType = NEWLINE_CHAR;
    } else if (isspace(currentCharacter)) {
        charType = WHITESPACE_CHAR;
    } else if (currentCharacter == '<') {
        charType = LESS_CHAR;
    } else if (currentCharacter == '>') {
        charType = GREATER_CHAR;
    } else if (currentCharacter == '=') {
        charType = EQUAL_CHAR;
    } else if (currentCharacter == '!') {
        charType = NOT_CHAR;
    } else if (currentCharacter == '+') {
        charType = PLUS_CHAR;
    } else if (currentCharacter == '-') {
        charType = MINUS_CHAR;
    } else if (currentCharacter == '*') {
        charType = TIMES_CHAR;
    } else if (currentCharacter == '/') {
        charType = DIVIDE_CHAR;
    } else if (currentCharacter == ';') {
        charType = SEMICOLON_CHAR;
    } else if (currentCharacter == '(') {
        charType = LPAREN_CHAR;
    } else if (currentCharacter == ')') {
        charType = RPAREN_CHAR;
    } else if (currentCharacter == '{') {
        charType = LCURLY_CHAR;
    } else if (currentCharacter == '}') {
        charType = RCURLY_CHAR;
    } else if (currentCharacter == EOF) {
        charType = ENDFILE_CHAR;
    }

    // Update previous token type
    previousTokenType = mCorrespondingTokenTypes[mcurrentState];
    
    // Update state based on legal moves
    mcurrentState = mLegalMoves[mcurrentState][charType];

    return mcurrentState;
}