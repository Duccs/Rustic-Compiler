#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>
#include <vector>
#include <iostream>

class SymbolTableClass {
    private:
        struct Variable {
            std::string mLabel;
            int mValue;
        };

        std::vector<Variable> mVariables;
        std::vector<size_t> mScopeStarts;
    public:
        SymbolTableClass() = default;
        ~SymbolTableClass() = default;

        void PushScope();
        void PopScope();

        bool Exists(const std::string & s);

        void AddEntry(const std::string & s);

        int GetValue(const std::string & s);
        void SetValue(const std::string & s, int v);

        int GetIndex(const std::string & s);

        size_t GetCount();
};

#endif /* _SYMBOL_H_ */