/*
Author: Grant Hughes
Created: February 23, 2025

Main.cpp:
    - Defines what a token is
    - Token type t1
        - ! “ # $ % & ‘ ( ) // these characters correspond to ascii numbers 33 to 41
    - Token type t2
        - Begin with a single +
        - followed by one or more digits (0-9) 
            - e.g. +0, +1000, are all valid; while +, +3+, 10, ++1 are all invalid tokens
    - oken type t3
        - Begin with single letter, (a-z, A-Z)
        - Followed by one or more digits (0-9)
            - e.g. b0, Z421, x1000, Y00 are all valid and z, b&3, 10, cd1, a+95 are all invalid tokens
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

    // constructor
    Token(TokenID id, const std::string &instance, int line): tokenID(id), tokenInstance(instance), lineNumber(line) {}
};

#endif