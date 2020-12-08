#include <iostream>

using namespace std;

#include "Token.h"

Token::Token(TokenType typ, string input, int lineNumber) {
    type = typ;
    value = input;
    lineNum = lineNumber;
}

Token::~Token() {}

string Token::typeToString(TokenType tokenType) {
    switch (tokenType) {
        case COMMA: return "COMMA"; break;
        case PERIOD: return "PERIOD"; break;
        case Q_MARK: return "Q_MARK"; break;
        case LEFT_PAREN: return "LEFT_PAREN"; break;
        case RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case COLON: return "COLON"; break;
        case COLON_DASH: return "COLON_DASH"; break; 
        case MULTIPLY: return "MULTIPLY"; break;
        case ADD: return "ADD"; break;
        case SCHEMES: return "SCHEMES"; break;
        case FACTS: return "FACTS"; break;
        case RULES: return "RULES"; break;
        case QUERIES: return "QUERIES"; break;
        case ID: return "ID"; break;
        case STRING: return "STRING"; break;
        case COMMENT: return "COMMENT"; break;
        case UNDEFINED: return "UNDEFINED"; break;
        case EOFT: return "EOF"; break;
    }
    return "ERROR";
}
string Token::tS() {
        
        string hstring = typeToString(type);

        string fstring = "";
        fstring = "(" + hstring + ",\"" + value + "\"," + to_string(lineNum) + ")\n";
    return fstring;
}