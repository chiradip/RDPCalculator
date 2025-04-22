//
// Created by Chiradip Mandal on 4/12/25.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "SymbolTable.h"
#include "Token.h"

class Calculator {
    SymbolTable st;
    TokenStream *ts{};
    double declaration();
    double expression_bitwise();
    double expression();
    double term();
    double secondary();
    double primary();
    double calc_sqrt();
    double calc_pow();
    double calc_sin();
    double calc_cos();
    double handle_variable(Token &t);

public:
    double statement(const string& expr);

    void calculation(const string &expr);
};
#endif //CALCULATOR_H
