#include <iostream>
#include <cctype>

using namespace std;

#include "EOFAutomaton.h"

EOFAutomaton::EOFAutomaton(TokenType tokenType) : Automaton(tokenType) {
    this->toMatch = toMatch;
}

int EOFAutomaton::Read(const string& input) {
    
    int inputRead = -2;
    
    return inputRead;
}