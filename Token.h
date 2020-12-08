#pragma once
#include <iostream>

using namespace std;

enum TokenType {UNDEFINED, COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, EOFT};

class Token {
private:
    int lineNum;
    
public:

    Token (TokenType typ, string input, int lineNumber);
    ~Token ();
    string value;
    
    string typeToString(TokenType type);
    string tS();
    TokenType type;
};