#include "Scanner.h"
#include <iostream>
#include <cstdlib>

ScannerClass::ScannerClass(const std::string& inputFileName) {
    mFin.open(inputFileName.c_str(), std::ios::binary);
    if (!mFin) {
        std::cerr << "Error opening input file " << inputFileName;
        std::exit(1);
    }
}

ScannerClass::~ScannerClass() {
    if (mFin.is_open()) {
        mFin.close();
    }
}

TokenClass ScannerClass::GetNextToken() {
    StateMachineClass stateMachine;
    std::string lexeme;
    MachineState currentState;
    TokenType previousTokenType;

    do
    {
        char c = mFin.get();
        lexeme += c;
        currentState = stateMachine.UpdateState(c, previousTokenType);
        if (currentState == START_STATE || currentState == ENDFILE_STATE)
            lexeme = "";
    } while (currentState != CANTMOVE_STATE);

    if (previousTokenType == BAD_TOKEN)
    {
        std::cerr << "Error. BAD_TOKEN from lexeme " << lexeme;
        std::exit(1);
    }

    lexeme.pop_back();
    mFin.unget();

    return TokenClass(previousTokenType, lexeme);
}