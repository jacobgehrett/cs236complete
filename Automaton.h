#pragma once
#include <iostream>

using namespace std;

#include "Token.h"

class Automaton
{
protected:
    int newLines = 0;
    TokenType type;
public:
    Automaton(TokenType type) { this->type = type; }
    
    virtual int Read(const string& input) = 0;
    
    virtual Token* CreateToken(string input, int lineNumber) {
        
        return new Token(type, input, lineNumber); }
    
    virtual int NewLinesRead() const { return newLines; }
    string toMatch;
    
};