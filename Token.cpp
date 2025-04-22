//
// Created by Chiradip Mandal on 4/11/25.
//

#include "Token.h"
#include "constants.h"
#include <iostream>

#include "enums.h"

Token::Token(const char k) : kind{k}, value{0} {}
Token::Token(const char k, const double v) : kind{k}, value{v} {}
Token::Token(const char k, string n) : kind{k}, value{0}, name{std::move(n)} {}

// c represents the kind of Token
void TokenStream::ignore(const char c) {
    // first look in buffer
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;
    // now search for input
    char ch = 0;
    while (iss >> ch)
        if (ch == c) return;
}

void TokenStream::putback(const Token &t) {
    buffer = t; // copy t to buffer
    full = true; // buffer is now full
}
Token TokenStream::get() {
    if (full) {
        // do we already have a Token?
        full = false; // remove Token from buffer
        return buffer;
    }

    char ch;
    iss.get(ch); // look for any char including whitespace

    while (isspace(ch) && ch != '\n') iss.get(ch);

    if (ch == SLASH_N) {
        return Token{PRINT};
    }
    if (ch == PRINT || ch == QUIT || ch == HELP || symbols.contains(ch)) {
        return Token{ch}; // let each character represent itself
    }
    if (ch == DOT || digits.contains(ch)) {
        iss.putback(ch); // we need to read the float/double number as a whole
        double val;
        iss >> val; // now read the number as a whole and advanced the reading position
        return Token{NUMBER, val};
    }
    if (isalpha(ch)) {
        string s;
        s += ch;
        while (iss.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
            s += ch;
        iss.putback(ch); // extra character extracted in the above loop, putting it back
        if (s == declKey) return Token{LET}; // declaration keyword
        if (s == sqrtKey) return Token{SQ_ROOT};
        if (s == expKey) return Token{EXPONENT};
        if (s == sinKey) return Token{C_SIN};
        if (s == cosKey) return Token{C_COS};
        if (s == quitKey) return Token{QUIT};
        if (s == helpKey) return Token{HELP};
        return Token{NAME, s};
    }
    throw runtime_error("Bad token--");
}
