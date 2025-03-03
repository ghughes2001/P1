/*
Author: Grant Hughes
Created: February 23, 2025

scanner.cpp:
    - Scans and returns validated tokens
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h> // isalnum
#include <cctype> // isalpha, isdigit
#include <sstream> // istringstream

#include "token.hpp"
#include "scanner.hpp"

using namespace std;

// checking if file is empty
// https://solvepro.co/check-if-a-file-is-empty-in-c/
bool isFileEmpty(const string &filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

// function to remove comments
string removeComments(string str)
{
    size_t startOfComment = str.find('*');

    while (startOfComment != string::npos) // if another '*' is found
    {
        size_t endOfComment = str.find('*', startOfComment + 1);
        if (endOfComment == string::npos) // there is no other '*'
            break;
        return str.substr(0, startOfComment) + str.substr(endOfComment + 1); // removing the comment and everything inbetween
    }
    return str;
}

// checking if token 1
// ! “ # $ % & ‘ ( ) 
bool tokenOneCheck(string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str[i];

        if (c == '!' || c == '"' || c == '#' || c == '$' || c == '%' || c == '&' 
            || c == '(' || c == ')' || c == '\'' )
            continue;
        if (isspace(c))
            continue;
        
        return false; //invalid
    }
    return true; // valid
}

bool tokenTwoCheck(string str)
{
    if (str.empty())
        return false;
    // checking first char to be a plus
    if (str[0] != '+')
        return false;
    // going through given string but from the 2nd character
    for (size_t i = 1; i < str.length(); i++)
    {
        if (!isdigit(str[i])) // checking if the rest are digits
            return false;
    }
    return true;
}

bool tokenThreeCheck(string str)
{
    if (str.empty())
        return false;
    // checking if 1st character is a letter not a digit
    if (!isalpha(str[0]))
        return false;

    // going through given string but from the 2nd character
    for (size_t i = 1; i < str.length(); i++)
    {
        if (!isdigit(str[i])) // checking if the rest are digits
            return false;
    }
    return true;
}

vector<Token> scanner(ifstream &inputFile, const string &filename, int line)
{
    // variables
    vector<Token> tokens; //hold all tokens
    string lineContent;
    string word;

    // checking if there is contents in file
    if (isFileEmpty(filename))
    {
        cout << "Error: File missing data" << endl;
        exit(1);
    }
    if (inputFile.is_open())
    {
        while (getline(inputFile, lineContent))
        {
            line++; // keep track of current line
            lineContent = removeComments(lineContent); // removing comments
            istringstream strDiv(lineContent); // accessing each string that is separated by white-space separators

            while (strDiv >> word) // accessing word
            {
                Token t(EOFTk, "EOF", line); // track current token
                // checking if token1
                if (word.length() == 1)
                {
                    if (!tokenOneCheck(word)) // invalid
                    {
                        cout << "SCANNER ERROR: " << word << ", " << line << endl;
                        exit(1);
                    }
                    t = Token(t1_tk, word, line); // return valid token1
                }
                // checking if token2
                if (word[0] == '+' && word.length() > 1)
                {
                    if (!tokenTwoCheck(word)) // invalid
                    {
                        cout << "SCANNER ERROR: " << word << ", " << line << endl;
                        exit(1);
                    }
                    t = Token(t2_tk, word, line); // return valid token2
                }
                // checking if token3
                if (isalpha(word[0]) && word.length() > 1)
                {
                    if (!tokenThreeCheck(word)) // invalid
                    {
                        cout << "SCANNER ERROR: " << word << ", " << line << endl;
                        exit(1);
                    }
                    t = Token(t3_tk, word, line); // return valid token3
                }
                if (t.tokenID != EOFTk)  // Only adding tk1, tk2, tk3
                {
                    tokens.push_back(t); // add to vector
                }
            }
            // checking if EOF is reached
            if (inputFile.eof())
            {
                tokens.push_back(Token(EOFTk, "EOF", line)); // add EOF to list now
                break;
            }
        }
        inputFile.clear(); // Clear any EOF flag after reading the file
        inputFile.seekg(0, ios::beg); // Go back to the beginning of the file
        inputFile.close();
    }
    else
    {
        cout << filename << " couldn't open" << endl;
        exit(1);
    }
    return tokens;
}
