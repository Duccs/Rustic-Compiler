#include <Parser.h>

void CodeAndExecute(std::string inputFile)
{
    // Create scanner, symbol table, and parser objects.
    ScannerClass scanner(inputFile);
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);
    // Do the parsing, which results in a parse tree.
    StartNode * root = parser.Start();
    // Create the machine code instructions from the parse tree
    InstructionsClass machineCode;
    root->Code(machineCode);
    machineCode.Finish();
    machineCode.PrintAllMachineCodes();
    // Execute the machine code instructions previously created
    machineCode.Execute();
    // cleanup recursively
    delete root;
}

int main()
{
    //std::cout << "Running machine code test..." << std::endl;
    //std::cout << "\n";
    CodeAndExecute("code.txt");
    //std::cout << "\n";
    //std::cout << "Machine code test completed!" << std::endl;
    return 0;
}

