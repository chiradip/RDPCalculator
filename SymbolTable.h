//
// Created by Chiradip Mandal on 4/11/25.
//

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <vector>

#include "variable.h"

using namespace std;
class SymbolTable {
    std::vector<variable> var_table;

public:
    [[nodiscard]] bool is_declared(const string&) const;
    [[nodiscard]] double get_value(const string&) const;
    double set_value(const string&, double);
    double define_name(const string&, double, bool con = false);
};

#endif //SYMBOL_TABLE_H
