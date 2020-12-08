#pragma once
#include <iostream>

using namespace std;

#include "Automaton.h"

class StringAutomaton :
    public Automaton
{
private:
    
    
public:
    StringAutomaton(TokenType tokenType);
    string toMatch;
    int Read(const string& input);
};