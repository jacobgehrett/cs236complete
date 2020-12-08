#pragma once
#include <iostream>

using namespace std;

#include "Automaton.h"

class MatcherAutomaton :
    public Automaton
{
private:
    
    
public:
    MatcherAutomaton(string toMatch, TokenType tokenType);
    string toMatch;
    int Read(const string& input);
};