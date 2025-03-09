/*
Author: Grant Hughes
Created: February 23, 2025

Main.cpp:
    - Process arguments
    - Calls testSCanner()
*/

#include <iostream>
#include <cstdlib> // exit()
#include <fstream> // file handling
#include <string>

#include "testscanner.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // checking if there is more than 1 filename present
    // And printing erro message if so (must be only 1 file)
    if (argc >= 3)
    {
        cout << "Fatal: Imroper Usuage" << endl;
        cout << "Usuage: P0 [filename]" << endl;
        
        // Terminate program if this is encountered
        exit(1);
    }
    // if 1 file then ooen and read contents
    // And build tree (if possible)
    if (argc == 2)
    {
        // variables
        string file = argv[1];

        ifstream myFile(file);
        if (!myFile.is_open())
        {
            cout << "Error: File could not be found" << endl;
            exit(1);
        }
        myFile.close();

        testScanner(file); // calliing testScanner(const string &file) method
    }
    if (argc == 1)
    {
        // variables for user input
        string inputLine;
        string word;
        ofstream writeFile("output.txt", ios::app);

        if (!writeFile.is_open())
        {
            cout << "Error: Could not open file for writing" << endl;
            exit(1);
        }

        while (getline(cin, inputLine))
        {
            if (inputLine.empty())
                continue;
            writeFile << inputLine << endl;
        }
        writeFile.close();

        // seeing if file is openable
        ifstream userFile("output.txt");
        if (!userFile.is_open())
        {
            cout << "Error: User file not opened" << endl;
            exit(1);
        }
        userFile.close();
        
        cout << "Output: " << endl;
        testScanner("output.txt"); // calliing testScanner(const string &file) method

        // erasing contents of file so the next user dosn't have it
        ofstream fileToClear("output.txt", ios::out | ios::trunc);
        fileToClear.close();

    }
    return 0;
}