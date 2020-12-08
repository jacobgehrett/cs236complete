#include <iostream>
#include <cctype>

using namespace std;

#include "Ident.h"

Ident::Ident(TokenType tokenType) : Automaton(tokenType) {
    this->toMatch = toMatch;
}

int Ident::Read(const string& input) {

    int inputRead = 0;
    if (isalpha(input.at(0))) {
        ++inputRead;
        unsigned int i = 1;
        while (isalpha(input.at(i)) || isdigit(input.at(i))) {
            ++i;
            ++inputRead;
        }
    }
    return inputRead;
}