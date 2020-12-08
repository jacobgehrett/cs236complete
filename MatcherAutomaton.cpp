#include <iostream>

using namespace std;

#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(string toMatch, TokenType tokenType) : Automaton(tokenType) {
    this->toMatch = toMatch;
}

int MatcherAutomaton::Read(const string& input) {
    //cout << input << endl;
    bool isMatch = true;
    int inputRead = 0;
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        
        if (input[i] != toMatch[i]) {
            
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = toMatch.size();
        if (toMatch == "Facts" || toMatch == "Rules" || toMatch == "Schemes" || toMatch == "Queries") {
            if (isdigit(input.at(toMatch.size())) || isalpha(input.at(toMatch.size()))) {
                isMatch = false;
                inputRead = 0;
            }
        }
        
    }
    //cout << inputRead;
    return inputRead;
}