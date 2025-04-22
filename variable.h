//
// Created by Chiradip Mandal on 4/11/25.
//

#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>

using namespace std;

class variable {
public:
    string name;
    double value;
    bool constant;

    variable(string n, const double v, const bool c = false)
        : name{std::move(n)}, value{v}, constant{c} {
    }
};

#endif //VARIABLE_H
