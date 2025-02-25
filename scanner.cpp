/*
Author: Grant Hughes
Created: February 23, 2025

Main.cpp:
    - Scans and returns tokens
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h> // isalnum
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

// checking if token 1
// ! “ # $ % & ‘ ( ) 
bool tokenOneCheck(string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str[i];

        if (isalnum(c))
            continue;
        if (c == '!' || c == '"' || c == '#' || c == '$' || c == '%' || c == '&' 
            || c == '(' || c == ')')
            continue;
        if (isspace(c))
            continue;
        
        return false; //invalid
    }
    return true; // valid
}

bool tokenTwoCheck(string str)
{
}

bool tokenThreeCheck(string str)
{
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
            // accessing each string that is seperated by white-space separators
            istringstream strDiv(line);

            while (strDiv >> word) // accessing word
            {
                if (!tokenOneCheck(word))
                {
                    cout << "Error: Invalid character or word " << endl;
                    exit(1); 
                }
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
