#include <iostream>
#include <cctype>

using namespace std;

#include "UndefinedAutomaton.h"

UndefinedAutomaton::UndefinedAutomaton(TokenType tokenType) : Automaton(tokenType) {
    this->toMatch = toMatch;
}

int UndefinedAutomaton::Read(const string& input) {
    
    int inputRead = 0;
    
    return inputRead;
}