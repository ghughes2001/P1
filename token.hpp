/*
Author: Grant Hughes
Created: February 23, 2025

token.hpp:
    - header file for token
*/

#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>

enum TokenID {
    t1_tk,
    t2_tk,
    t3_tk,
    EOFTk
};

struct Token {
    TokenID tokenID;
    std::string tokenInstance;
    int lineNumber;

    Token(TokenID id, const std::string &instance, int line): tokenID(id), tokenInstance(instance), lineNumber(line) {}
};

#endif