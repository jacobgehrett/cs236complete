#pragma once
#include <iostream>

using namespace std;

#include "Automaton.h"

class CommentAutomaton :
    public Automaton
{
private:
    
    
public:
    CommentAutomaton(TokenType tokenType);
    string toMatch;
    int Read(const string& input);
};