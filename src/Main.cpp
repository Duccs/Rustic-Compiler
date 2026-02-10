
#include <Scanner.h>
#include <iostream>


int main() {
    ScannerClass scanner("code.txt");
    MSG("Scanner initialized. Starting tokenization...");
    TokenType tt;
    do {
        TokenClass tc = scanner.GetNextToken();
        std::cout << "Line number: " << scanner.GetLineNumber() << " " << tc << std::endl;
        tt = tc.GetTokenType();
    } while (tt != ENDFILE_TOKEN);

    return 0;
}