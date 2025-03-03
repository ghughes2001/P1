/*
Author: Grant Hughes
Created: February 23, 2025

scanner.hpp:
    - Creates scanner()
*/

#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include <fstream>
#include "token.hpp"

Token scanner(std::ifstream &inputFile, const std::string &filename, int line);

#endif