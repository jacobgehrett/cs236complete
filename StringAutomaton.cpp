#include <iostream>
#include <cctype>

using namespace std;

#include "StringAutomaton.h"

StringAutomaton::StringAutomaton(TokenType tokenType) : Automaton(tokenType) {
    this->toMatch = toMatch;
}

int StringAutomaton::Read(const string& input) {
    int errorInd = 0;
    int inputRead = 0;
    long unsigned int i = 0;
    int arbitrary = 0;
    if (input.at(i) == '\'') {
        ++inputRead;
        ++i;
        if (input.size() == i) {
            //cout << "exiting5" << endl;
            return -1;
        }
        
        while (arbitrary == 0) {
            //cout << "do i die" << endl;
            
            if (input.at(i) == '\'') {
                ++inputRead;
                ++i;
                if (input.size() == i) {
                    //cout << "exiting5" << endl;
                    break;
                }
                //cout << "could die here" << endl;
                if (input.at(i) != '\'') {
                    //cout << "but maybe here" << endl;
                    //++inputRead;
                    //++i
                    break;
                    
                }
                
                else {
                    ++inputRead;
                    ++i;
                }
            }
            else {
                ++inputRead;
                ++i;
            }
            if (i == (input.size() - 1)) {
                        
                errorInd = -1;
                //cout << "exiting1" << endl;      
                return errorInd;
            }
            
            //cout << "or live" << endl;
        }
    }
    //cout << "exiting" << endl;
    return inputRead;
}