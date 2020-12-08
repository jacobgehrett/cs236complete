#pragma once
#include <iostream>

using namespace std;

#include "Automaton.h"

class UndefinedAutomaton :
    public Automaton
{
private:
    
    
public:
    UndefinedAutomaton(TokenType tokenType);
    string toMatch;
    int Read(const string& input);
};