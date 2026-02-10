#ifndef _SCANNER_H
#define _SCANNER_H

#include <Token.h>
#include <StateMachine.h>
#include <fstream>
#include <string>

class ScannerClass {
    private:
        std::ifstream mFin;
        int mLineNumber;
    
    public:
        ScannerClass(const std::string& inputFileName);
        ~ScannerClass();
        TokenClass GetNextToken();
        int GetLineNumber() const { return mLineNumber; }
};

#endif /* _SCANNER_H */