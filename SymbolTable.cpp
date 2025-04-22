//
// Created by Chiradip Mandal on 4/11/25.
//

#include "SymbolTable.h"

#include "Token.h"


// is var already in var_table?
bool SymbolTable::is_declared(const string& var) const {
    for (const variable &v: var_table) // NOLINT : Supressing Clang-Tidy: Replace loop by 'std::ranges::any_of()'
        if (v.name == var) return true;
    return false;
}

// return the value of the Variable named s
double SymbolTable::get_value(const string& s) const {
    for (const variable &v: var_table)
        if (v.name == s) return v.value;
    throw runtime_error("get: undefined variable " + s);
}

// set the Variable named s to d
double SymbolTable::set_value(const string& s, const double d) {
    for (variable &v: var_table)
        if (v.name == s) {
            if (v.constant) throw runtime_error("Can't overwrite constant variable");
            v.value = d;
            return d;
        }
    throw runtime_error("set: undefined variable " + s);
}

// add {var,val,con} to var_table
double SymbolTable::define_name(const string& var, const double val, const bool con) {
    if (is_declared(var)) throw runtime_error(var + " declared twice");
    var_table.emplace_back(var, val, con);
    return val;
}
