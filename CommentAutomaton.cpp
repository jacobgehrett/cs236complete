#include <iostream>
#include <cctype>

using namespace std;

#include "CommentAutomaton.h"

CommentAutomaton::CommentAutomaton(TokenType tokenType) : Automaton(tokenType) {
    this->toMatch = toMatch;
}

int CommentAutomaton::Read(const string& input) { //FIXME make sure it includes broken strings and comments as undefined behavior.
    int errorInd = 0;
    int inputRead = 0;
    int arbitrary = 0;
    
    if (input.at(0) == '#') {
        ++inputRead;
        if ((input.size() - 1) == 0) {
            return inputRead;
        }
        
        if (input.at(1) == '|') {
            ++inputRead;
            long unsigned int i = 2;
            if (input.at(i) == '|') {
                ++inputRead;
                ++i;
                if (input.at(i) == '#') {
                    ++inputRead;
                    return inputRead;
                }
            }
            else {
                while (arbitrary == 0) {
                    ++inputRead;
                    ++i;
                    
                    if (i == (input.size() - 1)) {
                        
                        errorInd = -1;
                        
                        return errorInd;
                    }
                    if (input.at(i) == '|') {
                        //cout << "hesssssy" << endl;
                        ++inputRead;
                        ++i;
                        //cout << input.at(i) << endl;
                        if (isspace(input.at(i))) {
                            ++inputRead;
                        }
                        else if (input.at(i) == '#') {
                            //cout << "heykgkgjgj" << endl;
                            ++inputRead;
                            break;
                        }
                    }
                    if (i == (input.size() - 1)) {
                        
                        errorInd = -1;
                        
                        return errorInd;
                    }
                }
            }   //cout << "hai" << endl;

        }
        
        else if ((input.at(1) != '\n') && (input.size() > 1)) {
            //cout << "Yep" << endl;
            ++inputRead;
            long unsigned int i = 2;
            while (input.at(i) != '\n') {
                //cout << "here" << endl;
                ++inputRead;
                ++i;
                if ((input.size() - 1) == i) {
                    //cout << "hmmm" << endl;
                    ++inputRead;
                    if (input.at(i) == '\n') {
                        inputRead = inputRead - 1;
                        
                    }   
                    break;
                }
                if (input.at(i) == '\n') {
                    //cout << "peen" << endl;
                    break;
                }
            }
            //cout << "yes" << endl;
        }
    }
    //cout << inputRead << endl;
    return inputRead;
}