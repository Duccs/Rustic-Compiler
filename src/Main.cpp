
#include <Scanner.h>
#include <iostream>


int main() {
    ScannerClass scanner("code.txt");
    TokenType tt;
    do {
        TokenClass tc = scanner.GetNextToken();
        std::cout << tc << std::endl;
        tt = tc.GetTokenType();
    } while (tt != ENDFILE_TOKEN);

    return 0;
}