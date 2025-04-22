//
// Created by Chiradip Mandal on 4/12/25.
//

#include "Calculator.h"

#include <iostream>

#include "constants.h"
#include "enums.h"
#include "utility.h"


vector<string> Calculator::calculation(const string &expr) {
    vector<string> tokens;
    stringstream ss(expr);
    constexpr char separator = ';';
    string token;
    while (getline(ss, token, separator)) {
        tokens.push_back(token);
    }
    vector<string> results;
    for (const auto & stmt : tokens) {
        string s = stmt;
        s.erase(s.find_last_not_of(" \n\r\t")+1);
        //cout << stmt << " EVAL-> ";
        const auto eval = statement(s + ';');
        //cout << eval << endl;
        results.push_back(stmt + " EVAL=> " + std::to_string(eval));
    }
    return results;
}

double Calculator::statement(const string& expr) {
    istringstream iss(expr);
    ts = new TokenStream(std::move(iss));
    switch (const Token t = ts->get(); t.kind) {
        case LET:
            return declaration();
        default:
            ts->putback(t);
            return expression_bitwise();
    }
}

double Calculator::declaration() {
    const Token t = ts->get();
    if (t.kind != NAME) throw runtime_error("name expected in declaration");
    const string var_name = t.name;

    if (const Token t2 = ts->get(); t2.kind != '=') throw runtime_error("= missing in declaration of " + var_name);

    const double d = expression_bitwise();
    st.define_name(var_name, d);
    return d;
}

double Calculator::expression_bitwise() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    Token t = ts->get(); // check for unary ~
    if (t.kind == '~')
        return ~static_cast<int>(expression());
    ts->putback(t);

    double left = expression();
    t = ts->get();

    while (true) {
        switch (t.kind) {
            case '&':
            case '|':
            case '^': {
                int temp = static_cast<int>(left);
                switch (t.kind) {
                    case '&':
                        temp &= static_cast<int>(expression());
                        break;
                    case '|':
                        temp |= static_cast<int>(expression());
                        break;
                    case '^':
                        temp ^= static_cast<int>(expression());
                        break;
                    default:
                        // no default
                        break;
                }
                left = temp;
                t = ts->get();
            }
            break;
            default:
                ts->putback(t);
                return left;
        }
    }
}

double Calculator::expression() { // NOLINT: Clang-Tidy: Function 'expression' is within a recursive call chain
    double left = term(); // read and evaluate a term
    Token t = ts->get(); // get next token from Token_stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term(); // evaluate term and add
                t = ts->get();
                break;
            case '-':
                left -= term(); // evaluate term and subtract
                t = ts->get();
                break;
            default:
                ts->putback(t); // put t back into the token stream
                return left;
        }
    }
}

double Calculator::term() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    double left = secondary();
    Token t = ts->get(); // get next token from Token_stream

    while (true) {
        switch (t.kind) {
            case '*':
                left *= secondary();
                t = ts->get();
                break;
            case '/': {
                double d = secondary();
                if (d == 0) throw runtime_error("divide by zero");
                left /= d;
                t = ts->get();
                break;
            }
            case '%': {
                double d = secondary();
                if (d == 0) throw runtime_error("%: divide by zero");
                left = fmod(left, d);
                t = ts->get();
                break;
            }
            default:
                ts->putback(t); // put t back into the Token_stream
                return left;
        }
    }
}

double Calculator::secondary() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    double left = primary();
    Token t = ts->get();

    while (true) {
        switch (t.kind) {
            case '!':
                if (left == 0) return 1;
                for (int i = static_cast<int>(left) - 1; i > 0; --i) left *= i;
                t = ts->get();
                break;
            default:
                ts->putback(t);
                return left;
        }
    }
}

double Calculator::primary() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    switch (Token t = ts->get(); t.kind) {
        // handle '(' expression ')'
        case '(': {
            const double d = expression_bitwise();
            t = ts->get();
            if (t.kind != ')') throw runtime_error("')' expected");
            return d;
        }
        case '{': {
            const double d = expression_bitwise();
            t = ts->get();
            if (t.kind != '}') throw runtime_error("'}' expected");
            return d;
        }
        case NUMBER:
            return t.value; // return the number's value
        case NAME:
            return handle_variable(t);
        case '-':
            return -primary();
        case '+':
            return primary();
        case SQ_ROOT:
            return calc_sqrt();
        case EXPONENT:
            return calc_pow();
        case C_SIN:
            return calc_sin();
        case C_COS:
            return calc_cos();
        default:
            throw runtime_error("primary expected");
    }
}

double Calculator::calc_sqrt() { // NOLINT: Clang-Tidy: Function 'calc_sqrt' is within a recursive call chain
    char ch;
    if (ts -> iss.get(ch) && ch != '(') throw runtime_error("'(' expected");
    ts -> iss.putback(ch);
    const double d = expression();
    if (d < 0) throw runtime_error("sqrt: negative val is imaginary");
    return sqrt(d);
}

double Calculator::calc_pow() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    Token t = ts->get();
    if (t.kind != '(') throw runtime_error("'(' expected");
    double base = expression_bitwise();
    t = ts->get();
    if (t.kind != ',') throw runtime_error("',' expected");
    const int power = narrow_cast<int>(expression_bitwise());
    t = ts->get();
    if (t.kind != ')') throw runtime_error("')' expected");
    return pow(base, power);
}

double Calculator::calc_sin() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    char ch;
    if (ts -> iss.get(ch) && ch != '(') throw runtime_error("'(' expected");
    ts->iss.putback(ch);
    const double d = expression();
    if (d == 0 || d == 180) return 0; // return true zero
    return sin(d * 3.1415926535 / 180);
}

double Calculator::calc_cos() { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    char ch;
    if (ts->iss.get(ch) && ch != '(') throw runtime_error("'(' expected");
    ts->iss.putback(ch);
    double d = expression();
    if (d == 90 || d == 270) return 0; // return 0 instead of 8.766e-11
    return cos(d * 3.1415926535 / 180);
}

double Calculator::handle_variable(Token &t) { // NOLINT: Clang-Tidy: Function 'calc_pow' is within a recursive call chain
    if (const Token t2 = ts->get(); t2.kind == '=')
        return st.set_value(t.name, expression());
    else {
        ts->putback(t2);
        return st.get_value(t.name); // missing in text!
    }
}
