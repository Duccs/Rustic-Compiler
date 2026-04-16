#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

const int MAX_INSTRUCTIONS = 5000;
const int MAX_DATA = 5000;

class InstructionsClass
{
public:
    InstructionsClass();
    void PrintAllMachineCodes();
    void WriteSpaceLinux64();
    void WriteEndlLinux64();
    void PopAndWrite();
    unsigned char *GetAddress();
    unsigned char *SkipIfZeroStack();
    unsigned char *Jump();
    void SetOffset(unsigned char *codeAddress, int offset);
    void PushValue(int value);
    void PushVariable(int variableIndex);
    void PopAndStore(int variableIndex);
    void PopPopDivPush();
    void PopPopAddPush();
    void PopPopSubPush();
    void PopPopMulPush();
    void PopPopLessPush();
    void PopPopLessEqualPush();
    void PopPopGreaterPush();
    void PopPopGreaterEqualPush();
    void PopPopEqualPush();
    void PopPopNotEqualPush();
    void PopPopAndPush();
    void PopPopOrPush();
    void Finish();
    void Execute();

private:
    void Encode(unsigned char c);
    void Encode(int x);
    void Encode(long long x);
    void Encode(void *p);
    int *GetMem(int index);
    void PrintIntegerLinux64();
    void WriteMinusLinux64();
    void Call(void *function_address);
    void PopPopComparePush(unsigned char relational_operator);

    unsigned char mCode[MAX_INSTRUCTIONS];
    int mData[MAX_DATA];
    int mCurrent; // where we are in mCode
    int mPrintInteger;
    // Location to store an integer about to be printed.
    int mTempInteger;
    // Location to store one char of integer to be printed.
    int mStartOfPrint;
    // The value of mCurrent where PrintIntegerLinux 64 starts.
    // Jump to this offset of mCode to print.
    int mStartOfMain;
    // the value of mCurrent after coding the Print functions.
    // Jump to this offset of mCode to start program execution.
    char mMinusString; // Holds '-'
    char mSpaceString; // Holds ' '
    char mNewLineString; // Holds '\n'
};

#endif