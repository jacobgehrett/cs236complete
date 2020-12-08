#pragma once
#include <iostream>

using namespace std;

#include "Automaton.h"

class Ident :
    public Automaton
{
private:
    
    
public:
    Ident(TokenType tokenType);
    string toMatch;
    int Read(const string& input);
};