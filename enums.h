//
// Created by Chiradip Mandal on 4/12/25.
//
#pragma once
#include <unordered_set>
#ifndef ENUMS_H
#define ENUMS_H
enum CharEnum {
    NUMBER = '8',
    QUIT = 'q',
    PRINT = ';',
    NAME = 'a',
    LET = 'L', // declaration token
    HELP = '?',
    C_SIN = 's',
    C_COS = 'c',
    DOT = '.',
    NEW_LINE = '\n',
    SLASH_N = NEW_LINE,
    SQ_ROOT = '@',
    EXPONENT = '#',
};

const unordered_set keywords = {LET, SQ_ROOT, EXPONENT, C_SIN, C_COS, QUIT, HELP};

#endif //ENUMS_H
