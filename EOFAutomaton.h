#pragma once
#include <iostream>

using namespace std;

#include "Automaton.h"

class EOFAutomaton :
    public Automaton
{
private:
    
    
public:
    EOFAutomaton(TokenType tokenType);
    string toMatch;
    int Read(const string& input);
};