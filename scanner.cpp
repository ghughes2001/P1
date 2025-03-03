/*
Author: Grant Hughes
Created: February 23, 2025

scanner.cpp:
    - Scans and returns validated tokens
*/

#include <iostream>
#include <fstream>
#include <string>
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

Token scanner(ifstream &inputFile, const string &filename, int line)
{
    // variables
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
            istringstream strDiv(lineContent); // accessing each string that is seperated by white-space separators

            while (strDiv >> word) // accessing word
            {
                // checking if token1
                if (word.length() == 1)
                {
                    if (!tokenOneCheck(word)) // invalid
                    {
                        cout << "SCANNER ERROR: " << word << ", " << line << endl;
                        exit(1); 
                    }
                    return Token(t1_tk, word, line); // return valid token1
                }
                // checking if token2
                if (word[0] == '+' && word.length() > 1)
                {
                    if (!tokenTwoCheck(word)) // invalid
                    {
                        cout << "SCANNER ERROR: " << word << ", " << line << endl;
                        exit(1); 
                    }
                    return Token(t2_tk, word, line); // return valid token2
                }
                // checking if token3
                if (isalpha(word[0]) && word.length() > 1)
                {
                    if (!tokenThreeCheck(word)) // invalid
                    {
                        cout << "SCANNER ERROR: " << word << ", " << line << endl;
                        exit(1); 
                    }
                    return Token(t3_tk, word, line); // return valid token3
                }
            }
            // checking if EOF is reached
            if (inputFile.eof())
            {
                return Token(EOFTk, "EOF", line);
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
}
