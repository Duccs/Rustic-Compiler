
#include <Symbol.h>
#include <cassert>
#include <iostream>

int main() {
    
    SymbolTableClass table;
    
    // Test AddEntry and Exists
    table.AddEntry("x");
    assert(table.Exists("x") == true);
    assert(table.Exists("y") == false);
    std::cout << "AddEntry and Exists work\n";
    
    // Test SetValue and GetValue
    table.SetValue("x", 42);
    assert(table.GetValue("x") == 42);
    std::cout << "SetValue and GetValue work\n";
    
    // Test GetCount
    table.AddEntry("y");
    assert(table.GetCount() == 2);
    std::cout << "GetCount works\n";
    
    // Test GetIndex
    assert(table.GetIndex("x") == 0);
    assert(table.GetIndex("y") == 1);
    std::cout << "GetIndex works\n";
    
    std::cout << "\nAll tests passed!\n";

    // Error testing
    // -------------

    // Test duplicate AddEntry
    // table.AddEntry("x");

    // Test GetValue non-existent
    // int val = table.GetValue("nonexistent");

    // Test SetValue non-existent
    // table.SetValue("nonexistent", 10);

    return 0;
}

// Scanner testing 
// ---------------
// int main() {
//     ScannerClass scanner("code.txt");
//     MSG("Scanner initialized. Starting tokenization...");
//     TokenType tt;
//     do {
//         TokenClass tc = scanner.GetNextToken();
//         std::cout << "Line number: " << scanner.GetLineNumber() << " " << tc << std::endl;
//         tt = tc.GetTokenType();
//     } while (tt != ENDFILE_TOKEN);

//     return 0;
// }