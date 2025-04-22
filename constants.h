//
// Created by Chiradip Mandal on 4/11/25.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <unordered_set>

using namespace std;

constexpr string prompt = "> ";
constexpr string result = "= ";
constexpr string declKey = "let"; //declaration keyword
constexpr string sqrtKey = "sqrt";
constexpr string expKey = "pow";
constexpr string sinKey = "sin";
constexpr string cosKey = "cos";
constexpr string quitKey = "quit";
constexpr string helpKey = "help";

const unordered_set symbols = {'(', ')', '{', '}', '!', '+', '-', '*', '/', '%', '=', ',', '~', '&', '|', '^'};
const unordered_set digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
#endif //CONSTANTS_H
