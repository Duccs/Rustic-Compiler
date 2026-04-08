#include "Instructions.h"

int main()
{
    InstructionsClass code;

    // Test Comparison Operations
    code.PushValue(3);
    code.PushValue(4);
    code.PopPopEqualPush();
    code.PopAndWrite(); // should print 0

    code.PushValue(4);
    code.PushValue(4);
    code.PopPopLessEqualPush();
    code.PopAndWrite(); // should print 1

    code.PushValue(5);
    code.PushValue(4);
    code.PopPopGreaterPush();
    code.PopAndWrite(); // should print 1

    code.PushValue(5);
    code.PushValue(5);
    code.PopPopGreaterEqualPush();
    code.PopAndWrite(); // should print 1

    code.PushValue(3);
    code.PushValue(4);
    code.PopPopLessPush();
    code.PopAndWrite(); // should print 1

    code.PushValue(5);
    code.PushValue(4);
    code.PopPopNotEqualPush();
    code.PopAndWrite(); // should print 1

    // Test Arithmetic Operations
    code.PushValue(5);
    code.PushValue(3);
    code.PopPopAddPush();
    code.PopAndWrite(); // should print 8

    code.PushValue(10);
    code.PushValue(3);
    code.PopPopSubPush();
    code.PopAndWrite(); // should print 7

    code.PushValue(4);
    code.PushValue(5);
    code.PopPopMulPush();
    code.PopAndWrite(); // should print 20

    code.PushValue(20);
    code.PushValue(4);
    code.PopPopDivPush();
    code.PopAndWrite(); // should print 5

    // Test Logical Operations
    code.PushValue(1);
    code.PushValue(1);
    code.PopPopAndPush();
    code.PopAndWrite(); // should print 1

    code.PushValue(0);
    code.PushValue(1);
    code.PopPopOrPush();
    code.PopAndWrite(); // should print 1

    // Test Variable Operations
    code.PushValue(42);
    code.PopAndStore(0); // Store 42 in mData[0]

    code.PushValue(17);
    code.PopAndStore(1); // Store 17 in mData[1]

    code.PushVariable(0); // Push mData[0] (42)
    code.PopAndWrite(); // should print 42

    code.PushVariable(1); // Push mData[1] (17)
    code.PopAndWrite(); // should print 17

    // Test combination of operations
    code.PushValue(100);
    code.PopAndStore(2);

    code.PushVariable(2); // Get 100
    code.PushValue(30);
    code.PopPopSubPush(); // 100 - 30 = 70
    code.PopAndWrite(); // should print 70

    code.Finish();
    code.Execute();
    return 0;
}