#include "Symbol.h"

bool SymbolTableClass::Exists(const std::string & s) {
    // Check if <s> exists in the symbol table
    for (const auto& var : mVariables) {
        if (var.mLabel == s) {
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string & s) {
    // Add <s> to the symbol table, or quit if it was already there
    if (Exists(s)) {
        std::cerr << "Error: Variable " << s << " already exists in the symbol table.";
        std::exit(1);
    }
    mVariables.push_back({s, 0}); // Initialize with value 0
}

int SymbolTableClass::GetValue(const std::string & s) {
    // Get the current value of variable <s>
    for (const auto& var : mVariables) {
        if (var.mLabel == s) {
            return var.mValue;
        }
    }
    std::cerr << "Error: Variable " << s << " does not exist in the symbol table.";
    std::exit(1);
}

void SymbolTableClass::SetValue(const std::string & s, int v) {
    // Set variable <s> to the given value
    for (auto& var : mVariables) {
        if (var.mLabel == s) {
            var.mValue = v;
            return;
        }
    }
    std::cerr << "Error: Variable " << s << " does not exist in the symbol table.";
    std::exit(1);
}

int SymbolTableClass::GetIndex(const std::string & s) {
    // Get the unique index of where variable <s> is
    for (size_t i = 0; i < mVariables.size(); ++i) {
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