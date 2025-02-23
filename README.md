# P1

P1: Scanner (100 points)
Due March 7 at 11:59pm
Objectives:
• Implement the first piece of your compiler: the scanner
• Use a deterministic finite state automaton (FSA) to define a regular language
• Develop skills for the use of lookup tables by converting the FSA into a lookup table that efficiently
recognizes tokens of the language
• Develop skills in string manipulations and the use of ASCII values
• Improve programming architecture and style
• Improve prompt engineering skills, ability to debug and dissect AI-generated code, and ability to
communicate clear and informative comments
Requirements:
• Implement scanner for the provided lexical definitions (see below)
• The scanner is embedded and thus it will return one token every time it is called by a parser
o Since the parser is not available yet, we will use a tester program
• Implement the scanner in a separate file with basename "scanner" (scanner.cpp, scanner.h)
• For testing purposes, the scanner will be tested using a testing driver implemented in file with
basename "testScanner".
o You need to implement your own tester and include as a part of the project.
o The tester will ask for one token at a time and display the token to the screen one per line,
including the token class, the specific token instance, and the line number in the input file.
• Invocation:
P1 [file]
o As in Project P0, a filename may be specified or the information can be read from stdin
o Wrong invocations may not be graded
o Program must compile and run on hellbender
• Additional requirements:
o Types, including token type, must be defined in token.h
 Don’t forget EOFtk token
o You must implement scanner in scanner.c (.cpp) and scanner.h
o Your FSA table must be used to generate tokens and it must have row and column ordering as
specified in class and as included in the project P1 module on Canvas
o You must implement the tester in another file testScanner.c (.cpp) and testScanner.h
o Your main function processes the command-line arguments (as done for P0) then calls
testScanner() function with interface and preparation as needed
main.cpp
- Process arguments
- call testScanner()
scanner.cpp
- scan in and return one
token
testScanner.cpp
- iteratively call scanner()
and print token
- until scanner returns EOFTk
token.h
- define types
scanner.h
- scanner();
testScanner.h
- testScanner();
Note that testScanner will be replaced by parser in project P2.
Lexical Definitions
• Case sensitive
• Comments start with * and end with *
• Alphabet:
o All upper- and lower-case English letters, digits, plus the extra characters as shown below, plus
white space
o No other characters are allowed and they must generate errors
o Each scanner error must display "SCANNER ERROR:" followed by input string and line number
• Token type t1
o ! “ # $ % & ‘ ( ) // these characters correspond to ascii numbers 33 to 41
• Token type t2
o Begin with a single +
o followed by one or more digits (0-9)
 e.g. +0, +1000, are all valid; while +, +3+, 10, ++1 are all invalid tokens
• Token type t3
o Begin with single letter, (a-z, A-Z)
o Followed by one or more digits (0-9)
 e.g. b0, Z421, x1000, Y00 are all valid and z, b&3, 10, cd1, a+95 are all invalid tokens
P1 Suggestions
• Implement token as a triplet {tokenID, tokenInstance, line#}
o TokenID can be enumeration (better) or symbolic constant (worse) (see below)
o tokenInstance can be a string or can be some reference to a string table
o The triplet can be a struct
• Suggestions:
o File can be opened and lookahead character can be set explicitly before the first call to the
scanner for the first token
o Have the scanner read from a filter, not directly from the file
 The filter would count lines, skip over spaces and comments, construct string of
characters for the current token, and return the column number in the table
corresponding to the character
o Suggest an array of strings describing the tokens, listed in the same order as the tokenID
enumeration, to print tokens. For example:
enum tokenID {t1_tk, t2_tk, t3_tk};
string tokenNames[] ={"t1 token", "t2 token", “t3 token”};
struct token {tokenID, string, int}; // string is comprised of the characters in the specific token, int is the line #
Then printing tokenNames[tokenID] will print the token description, etc.
Testing
This section is a sample subset of testing of P1
1. Create test files:
1. P1_test1.txt containing just one token (with standard line return at the end):
+4
Try changing the +4 to valid and invalid characters and retest each.
2. P1_test2.txt containing a list with one or more of each of the token types, all separated by a
space or new line:
x16 +53 !
% S228
//etc
Try changing characters to make strings that are invalid and test each for correct error message.
3. Combine tokens w/o WS
Revise the previous test cases by removing white spaces.
4. Test also with comments and/or blank lines added, be sure these do not change the outputs
2. Run the invocations and check against predictions
1. ./P1 P1_test
Program error file not found
2. ./P1 P1_test1.txt
t2 token +4 1
EOFTk
3. ./P1 P1_test2.txt
t3 token x16 1
t2 token +53 1
t1 token ! 1
t1 token % 2
t3 token S228 2
EOFTk
4. ./P1 P1_test3.txt (merged tokens without white space separations)
Should output the tokens you have in the file, properly splitting merged tokens
Submission:
1. All source and header files
2. Makefile
3. Academic Integrity Statement
4. Readme (optional)
5. Do NOT include executable or .o files!
6. Tar and zip files prior to submission (Academic Integrity Statement can be included in zipped package, uploaded
separately, or a hard copy can be submitted in class)
Rubric:
• Meaningful and concise comments throughout source code • Programming architecture and style (using selected department standards) • Properly handles merged tokens (with no white space) • Prints correct line numbers in output • Correct output (disregarding line number and merged token errors) o Includes proper printout of one token per line
E.g.: t3 token x16 1
t2 token +53 1
o Includes printing EOFTk
30 pts.
5 pts.
10 pts.
5 pts.
50 pts.
Programs that fail to comply with stated requirements, are missing a working makefile, fail to compile on hellbender,
or fail to produce an executable named P1 will not be graded. Academic Integrity Statement is required to receive a
grade.
