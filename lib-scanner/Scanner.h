#ifndef _SCANNER_H
#define _SCANNER_H

#include <Token.h>
#include <StateMachine.h>
#include <fstream>
#include <string>

class ScannerClass {
    private:
        std::ifstream mFin;
    
    public:
        ScannerClass(const std::string& inputFileName);
        ~ScannerClass();
        TokenClass GetNextToken();
};

#endif /* _SCANNER_H */