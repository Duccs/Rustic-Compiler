

#include <iostream>
#include <iomanip>
#include <Scanner.h>
#include <Parser.h>
#include <Symbol.h>
#include <Node.h>

int main() {

    std::cout << "Initializing scanner...\n";
    ScannerClass scanner("code.txt");
    std::cout << "Scanner initialized!\n";

    std::cout << "Creating symbol table...\n";
    SymbolTableClass symbolTable;
    std::cout << "Symbol table created!\n";

    std::cout << "Initializing parser...\n";
    ParserClass parser(&scanner, &symbolTable);
    std::cout << "Parser initialized!\n\n";

    std::cout << "Parsing...\n";
    StartNode* parseTree = parser.Start();
    std::cout << "Parsing completed successfully\n\n";    

    std::cout << "Executing code...\n";
    std::cout << "Output from parsed program:\n";
    parseTree->Interpret();

    return 0;
}