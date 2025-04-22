//
// Created by Chiradip Mandal on 4/11/25.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <sstream>
#include <string>
using namespace std;

enum TokenKind {
    //prompt, result, declKey, sqrtKey, expKey, sinKey, cosKey, quitKey, helpKey
};

class Token final {
public:
    char kind;
    double value;
    string name;

    ~Token() = default;

    explicit Token(char k);

    // : kind{k}, value{0} {} // Clang-Tidy: Single-argument constructors must be marked explicit to avoid
    // unintentional implicit conversion
    Token(char k, double v); //  : kind{k}, value{v} {}
    Token(char k, string n); // : kind{k}, value{0}, name{std::move(n)} {}
};

class TokenStream {
public:
    istringstream iss;
    explicit TokenStream(istringstream iss) {
        this -> iss = std::move(iss);
    }
    Token get(); // get a Token
    void putback(const Token &t); // put a token back
    void ignore(char c); // discard characters up to and including a c
private:
    bool full{false}; // is there a Token in the buffer?
    Token buffer{'0'}; // here is where putback() stores a Token

};

#endif //TOKEN_H
