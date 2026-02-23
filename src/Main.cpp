
#include <Node.h>
#include <Symbol.h>
#include <cassert>
#include <iostream>

// Parse Tree testing
// ------------------
int main() {

    std::cout << "Parse Tree Testing\n";
    std::cout << "------------------\n";

    // Simple arithmetic expression with assignment
    std::cout << "var = (3 + 4) * 5\n";
    std::cout << "Building parse tree...\n";
    {
        SymbolTableClass symbolTable;
        
        // Build expression
        IntegerNode* three = new IntegerNode(3);
        IntegerNode* four = new IntegerNode(4);
        IntegerNode* five = new IntegerNode(5);
        PlusNode* plus = new PlusNode(three, four);
        TimesNode* times = new TimesNode(plus, five);

        // Build statements
        StatementGroupNode* statementGroup = new StatementGroupNode();
        
        IdentifierNode* varDecl = new IdentifierNode("var", &symbolTable);
        DeclarationStatementNode* declaration = new DeclarationStatementNode(varDecl);
        IdentifierNode* varAssign = new IdentifierNode("var", &symbolTable);
        AssignmentStatementNode* assignment = new AssignmentStatementNode(varAssign, times);
        statementGroup->AddStatement(declaration);
        statementGroup->AddStatement(assignment);

        BlockNode* block = new BlockNode(statementGroup);
        ProgramNode* program = new ProgramNode(block);
        StartNode* start = new StartNode(program);

        // Verify expression evaluation
        int result = times->Evaluate();
        std::cout << "Expression (3 + 4) * 5 evaluated to: " << result << "\n";
        assert(result == 35);

        std::cout << "Deleting parse tree...\n";
        delete start;
        std::cout << "Parse tree deleted successfully!\n\n";
    }

    // Multiple statements with shared symbol table
    std::cout << "x = 10; y = 20; z = (x + y) * 2\n";
    std::cout << "Building parse tree...\n";
    {
        SymbolTableClass symbolTable;
        
        StatementGroupNode* statementGroup = new StatementGroupNode();

        // x = 10
        IdentifierNode* xDecl = new IdentifierNode("x", &symbolTable);
        DeclarationStatementNode* xDeclaration = new DeclarationStatementNode(xDecl);
        statementGroup->AddStatement(xDeclaration);
        
        IdentifierNode* xAssignId = new IdentifierNode("x", &symbolTable);
        IntegerNode* ten = new IntegerNode(10);
        AssignmentStatementNode* xAssignment = new AssignmentStatementNode(xAssignId, ten);
        statementGroup->AddStatement(xAssignment);

        // y = 20
        IdentifierNode* yDecl = new IdentifierNode("y", &symbolTable);
        DeclarationStatementNode* yDeclaration = new DeclarationStatementNode(yDecl);
        statementGroup->AddStatement(yDeclaration);
        
        IdentifierNode* yAssignId = new IdentifierNode("y", &symbolTable);
        IntegerNode* twenty = new IntegerNode(20);
        AssignmentStatementNode* yAssignment = new AssignmentStatementNode(yAssignId, twenty);
        statementGroup->AddStatement(yAssignment);

        // z = (x + y) * 2
        IdentifierNode* zDecl = new IdentifierNode("z", &symbolTable);
        DeclarationStatementNode* zDeclaration = new DeclarationStatementNode(zDecl);
        statementGroup->AddStatement(zDeclaration);
        
        IdentifierNode* xExpr = new IdentifierNode("x", &symbolTable);
        IdentifierNode* yExpr = new IdentifierNode("y", &symbolTable);
        PlusNode* sum = new PlusNode(xExpr, yExpr);
        IntegerNode* two = new IntegerNode(2);
        TimesNode* product = new TimesNode(sum, two);
        
        IdentifierNode* zAssignId = new IdentifierNode("z", &symbolTable);
        AssignmentStatementNode* zAssignment = new AssignmentStatementNode(zAssignId, product);
        statementGroup->AddStatement(zAssignment);

        BlockNode* block = new BlockNode(statementGroup);
        ProgramNode* program = new ProgramNode(block);
        StartNode* start = new StartNode(program);

        std::cout << "Deleting parse tree...\n";
        delete start;
        std::cout << "Parse tree deleted successfully!\n\n";
    }

    // Expressions with comparisons
    std::cout << "result = (5 + 3) < (2 * 3)\n";
    std::cout << "Building parse tree...\n";
    {
        SymbolTableClass symbolTable;
        
        StatementGroupNode* statementGroup = new StatementGroupNode();

        // Declare result
        IdentifierNode* resultDecl = new IdentifierNode("result", &symbolTable);
        DeclarationStatementNode* declaration = new DeclarationStatementNode(resultDecl);
        statementGroup->AddStatement(declaration);

        // left side: 5 + 3
        IntegerNode* five = new IntegerNode(5);
        IntegerNode* three = new IntegerNode(3);
        PlusNode* leftSum = new PlusNode(five, three);

        // right side: 2 * 3
        IntegerNode* two = new IntegerNode(2);
        IntegerNode* three2 = new IntegerNode(3);
        TimesNode* rightProduct = new TimesNode(two, three2);

        // (5 + 3) < (2 * 3)
        LessNode* comparison = new LessNode(leftSum, rightProduct);

        IdentifierNode* resultAssign = new IdentifierNode("result", &symbolTable);
        AssignmentStatementNode* assignment = new AssignmentStatementNode(resultAssign, comparison);
        statementGroup->AddStatement(assignment);

        BlockNode* block = new BlockNode(statementGroup);
        ProgramNode* program = new ProgramNode(block);
        StartNode* start = new StartNode(program);

        // Check (5 + 3) < (2 * 3) = (8 < 6) = 0
        int cmpResult = comparison->Evaluate();
        std::cout << "Comparison (5 + 3) < (2 * 3) evaluated to: " << cmpResult << "\n";
        assert(cmpResult == 0);

        std::cout << "Deleting parse tree...\n";
        delete start;
        std::cout << "Parse tree deleted successfully!\n\n";
    }

    // Nested expression with multiple operator types
    std::cout << "Nested expression with multiple operators\n";
    std::cout << "x = ((10 - 3) + (8 / 2)) * (5 == 5)\n";
    std::cout << "Building parse tree...\n";
    {
        SymbolTableClass symbolTable;
        
        StatementGroupNode* statementGroup = new StatementGroupNode();

        IdentifierNode* xDecl = new IdentifierNode("x", &symbolTable);
        DeclarationStatementNode* declaration = new DeclarationStatementNode(xDecl);
        statementGroup->AddStatement(declaration);

        // (10 - 3)
        IntegerNode* ten = new IntegerNode(10);
        IntegerNode* three = new IntegerNode(3);
        MinusNode* subtract = new MinusNode(ten, three);

        // (8 / 2)
        IntegerNode* eight = new IntegerNode(8);
        IntegerNode* two = new IntegerNode(2);
        DivideNode* divide = new DivideNode(eight, two);

        // (10 - 3) + (8 / 2)
        PlusNode* sum = new PlusNode(subtract, divide);

        // (5 == 5)
        IntegerNode* five1 = new IntegerNode(5);
        IntegerNode* five2 = new IntegerNode(5);
        EqualNode* equal = new EqualNode(five1, five2);

        // ((10 - 3) + (8 / 2)) * (5 == 5)
        TimesNode* product = new TimesNode(sum, equal);

        IdentifierNode* xAssign = new IdentifierNode("x", &symbolTable);
        AssignmentStatementNode* assignment = new AssignmentStatementNode(xAssign, product);
        statementGroup->AddStatement(assignment);

        BlockNode* block = new BlockNode(statementGroup);
        ProgramNode* program = new ProgramNode(block);
        StartNode* start = new StartNode(program);

        // (10 - 3) + (8 / 2) = 11
        int result = product->Evaluate();
        std::cout << "Expression ((10 - 3) + (8 / 2)) * (5 == 5) evaluated to: " << result << "\n";
        assert(result == 11);

        std::cout << "Deleting parse tree...\n";
        delete start;
        std::cout << "Parse tree deleted successfully!\n\n";
    }

    return 0;
}


// Symbol Table testing
// --------------------
// int main() {

//     SymbolTableClass table;
    
//     // Test AddEntry and Exists
//     table.AddEntry("x");
//     assert(table.Exists("x") == true);
//     assert(table.Exists("y") == false);
//     std::cout << "AddEntry and Exists work\n";
    
//     // Test SetValue and GetValue
//     table.SetValue("x", 42);
//     assert(table.GetValue("x") == 42);
//     std::cout << "SetValue and GetValue work\n";
    
//     // Test GetCount
//     table.AddEntry("y");
//     assert(table.GetCount() == 2);
//     std::cout << "GetCount works\n";
    
//     // Test GetIndex
//     assert(table.GetIndex("x") == 0);
//     assert(table.GetIndex("y") == 1);
//     std::cout << "GetIndex works\n";
    
//     std::cout << "\nAll tests passed!\n";

//     // Error testing
//     // -------------

//     // Test duplicate AddEntry
//     // table.AddEntry("x");

//     // Test GetValue non-existent
//     // int val = table.GetValue("nonexistent");

//     // Test SetValue non-existent
//     // table.SetValue("nonexistent", 10);

//     return 0;
// }

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