//
// Created by Chiradip Mandal on 4/12/25.
//

#include <iostream>

#include "Calculator.h"

int main(int argc, char *argv[]) {
    auto calculator = Calculator();

    vector<string> evals = calculator.calculation("let a=7;let b=3; let c = a*b; a+b*8;");
    for (const auto &s : evals) {
        cout << s << endl;
    }
}
