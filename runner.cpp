//
// Created by Chiradip Mandal on 4/12/25.
//

#include <iostream>

#include "Calculator.h"

int main(int argc, char *argv[]) {
    Calculator calculator = Calculator();
    const auto res = calculator.statement("1+2;");
    cout << "d = " << res << '\n';

    calculator.calculation("let a=7;let b=3; let c = a*b; a+b*8;");
}
