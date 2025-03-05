#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> // isalnum, isalpha, isdigit
#include <sstream> // istringstream

#include "token.hpp"
#include "scanner.hpp"

using namespace std;

// checking if file is empty
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
        return str.substr(0, startOfComment) + str.substr(endOfComment + 1); // removing the comment and everything in-between
    }
    return str;
}

// checking if token1
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
        return false; // invalid
    }
    return true; // valid
}

// checking if token2 (numbers starting with a +)
bool tokenTwoCheck(string str)
{
    if (str.empty() || str[0] != '+')
        return false;
    for (size_t i = 1; i < str.length(); i++)
    {
        if (!isdigit(str[i])) // checking if the rest are digits
            return false;
    }
    return true;
}

// checking if token3 (letters followed by digits)
bool tokenThreeCheck(string str)
{
    if (str.empty() || !isalpha(str[0]))
        return false;
    for (size_t i = 1; i < str.length(); i++)
    {
        if (!isdigit(str[i])) // checking if the rest are digits
            return false;
    }
    return true;
}

// Function that splits merged tokens/checks token
vector<string> splitTokens(string str) {
    vector<string> tokens;
    string token;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];

        // Case 1: Alphanumeric characters or '+' (if followed by digits)
        if (isalnum(c) || (c == '+' && i + 1 < str.length() && isdigit(str[i + 1]))) {
            token += c;  // Append to the current token
        }
        // Case 2: Transition from a number (with a '+' sign) to a letter or vice versa
        else if ((isdigit(c) && !token.empty() && isalpha(token.back())) || 
                 (isalpha(c) && !token.empty() && isdigit(token.back())) ||
                 (c == '+' && isdigit(str[i+1]) && !token.empty() && isalpha(token.back()))) {
            tokens.push_back(token);  // Add the current token
            token = c;  // Start a new token with the current character
        }
        // Case 3: Special characters treated as separate tokens
        else if (!isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);  // Add the current token to the list
                token.clear();  // Clear the current token
            }
            tokens.push_back(string(1, c));  // Add special character as a separate token
        }
        // Case 4: Whitespace - finalize the current token if any
        else if (isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);  // Add the current token
                token.clear();  // Clear for next token
            }
        }
    }

    // Add any remaining token at the end
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<Token> scanner(ifstream &inputFile, const string &filename, int line)
{
    // variables
    vector<Token> tokens; // hold all tokens
    string lineContent;

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
            vector<string> words = splitTokens(lineContent);

            for (size_t i = 0; i < words.size(); i++) // accessing word
            {
                string word = words[i];
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
