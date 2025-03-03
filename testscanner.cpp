/*
Author: Grant Hughes
Created: March 2, 2025

testscanner.cpp:
    - iteratively call scanner() and print token
    - until scanner returns EOFTk
*/

#include <iostream>
#include <vector>
#include <fstream>

#include "token.hpp"
#include "scanner.hpp"

using namespace std;

void testScanner(const string &file)
{
    // making sure file can be opened
    ifstream readingFile(file);
    if (!readingFile)
    {
        cout << "Couldn't open " << file << endl;
    }

    int currentLine = 0; // creating variable to track current line

    while (true)
    {
        vector<Token> tokens = scanner(readingFile, file, currentLine);  // Get all tokens for the current line

        // print information about all tokens in the vector
        for (const Token &token : tokens)
        {
            cout << token.getTokenAsString() << "\t" << token.tokenInstance << "\t" << token.lineNumber << endl;
        }

        // End the loop when the EOF token is found
        if (!tokens.empty() && tokens.back().tokenID == EOFTk)
        {
            break;
        }

        currentLine++;  // move to the next line
    }
    readingFile.close();
}