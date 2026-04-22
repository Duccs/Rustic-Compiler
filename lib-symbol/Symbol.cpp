#include "Symbol.h"

void SymbolTableClass::PushScope() {
    mScopeStarts.push_back(mVariables.size());
}

void SymbolTableClass::PopScope() {
    size_t start = mScopeStarts.empty() ? 0 : mScopeStarts.back();
    if (!mScopeStarts.empty()) {
        mScopeStarts.pop_back();
    }
    mVariables.resize(start);
}

bool SymbolTableClass::Exists(const std::string & s) {
    // Check if <s> exists in the symbol table annd in the visible scope
    for (size_t i = mVariables.size(); i-- > 0; ) {
        if (mVariables[i].mLabel == s) {
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string & s) {
    // Add <s> to the symbol table, or quit if it was already there. Only reject redeclaration within the current scope
    size_t start = mScopeStarts.empty() ? 0 : mScopeStarts.back();
    for (size_t i = start; i < mVariables.size(); ++i) {
        if (mVariables[i].mLabel == s) {
            std::cerr << "Error: Variable " << s << " already exists in the symbol table.";
            std::exit(1);
        }
    }
    mVariables.push_back({s, 0}); // Initialize with value 0
}

int SymbolTableClass::GetValue(const std::string & s) {
    // Get the current value of variable <s>. Innermost-first lookup
    for (size_t i = mVariables.size(); i-- > 0; ) {
        if (mVariables[i].mLabel == s) {
            return mVariables[i].mValue;
        }
    }
    std::cerr << "Error: Variable " << s << " does not exist in the symbol table.";
    std::exit(1);
}

void SymbolTableClass::SetValue(const std::string & s, int v) {
    // Set variable <s> to the given value. Innermost-first lookup
    for (size_t i = mVariables.size(); i-- > 0; ) {
        if (mVariables[i].mLabel == s) {
            mVariables[i].mValue = v;
            return;
        }
    }
    std::cerr << "Error: Variable " << s << " does not exist in the symbol table.";
    std::exit(1);
}

int SymbolTableClass::GetIndex(const std::string & s) {
    // Get the unique index of where variable <s> is
    for (size_t i = mVariables.size(); i-- > 0; ) {
        if (mVariables[i].mLabel == s) {
            return static_cast<int>(i);
        }
    }
    return -1; // Variable <s> is not there
}

size_t SymbolTableClass::GetCount() {
    // Get the current number of variables in the symbol table
    return mVariables.size();
}