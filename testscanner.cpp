/*
Author: Grant Hughes
Created: March 2, 2025

testscanner.cpp:
    - iteratively call scanner() and print token
    - until scanner returns EOFTk
*/

#include <iostream>
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
        Token token = scanner(readingFile, file, currentLine); // creating a token to access id, actual token, and line using scanner
        // printing information about token
        cout << token.tokenID << token.tokenInstance << token.lineNumber << endl;

        // ending the infinte while loop
        if (token.tokenID == EOFTk)
        {
            break;
        }
        currentLine++; // move to next line
    }
    readingFile.close();
}