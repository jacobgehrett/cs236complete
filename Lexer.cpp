#include <iostream>
#include <vector>

using namespace std;

#include "Lexer.h"

Lexer::Lexer() {
    machines.clear();
    
    machines.push_back(new MatcherAutomaton(",", COMMA));
    machines.push_back(new MatcherAutomaton(".", PERIOD));
    machines.push_back(new MatcherAutomaton("?", Q_MARK));
    machines.push_back(new MatcherAutomaton("(", LEFT_PAREN));
    machines.push_back(new MatcherAutomaton(")", RIGHT_PAREN));
    
    machines.push_back(new MatcherAutomaton(":-", COLON_DASH));
    machines.push_back(new MatcherAutomaton(":", COLON));
    machines.push_back(new MatcherAutomaton("*", MULTIPLY));
    machines.push_back(new MatcherAutomaton("+", ADD));
    machines.push_back(new MatcherAutomaton("Schemes", SCHEMES));
    machines.push_back(new MatcherAutomaton("Facts", FACTS));
    machines.push_back(new MatcherAutomaton("Rules", RULES));
    machines.push_back(new MatcherAutomaton("Queries", QUERIES));
    machines.push_back(new Ident(ID));
    machines.push_back(new StringAutomaton(STRING));
    machines.push_back(new CommentAutomaton(COMMENT));
    machines.push_back(new UndefinedAutomaton(UNDEFINED));
    machines.push_back(new EOFAutomaton(EOFT));
}

Lexer::~Lexer() {}

vector<Token*> Lexer::Run(string input) {
    
    
    // NOTE: Lexer class needs a collection of machines and
    // an ordered collection to store the tokens generated
    
    int lineNumber = 1; //
    while (isspace(input.at(0))) {
        ++lineNumber;
        input.erase(0, 1);
        
    }
    while (input.size() > 0) {
        //cout << input.size() << input << "try again" << endl;
        int maxRead = 0; //
        
        Automaton* maxMachine = machines.at(0);
        int maxNewLines = 0;
        int val = 0;
        string inp = "";
        int errorCheck = 0;
        for (long unsigned int i = 0; i < machines.size(); ++i) {
            
            //cout << machines.at(0)->newLines;
            //cout << " do i get here" << endl;
            int inputRead = machines.at(i)->Read(input);
            //cout << "or here" << endl;
            if (inputRead == -1) {
                
                maxMachine = machines.at(16);

                Token* newToken = maxMachine->CreateToken(input, lineNumber);
                tokens.push_back(newToken);
                errorCheck = -1;

                int newLineNumber = 0;
                for (long unsigned int j = 0; j < input.size(); ++j) {
                    /*if (input.at(j) == '\t') {
                        inp.push_back(' ');
                    }
                    else {*/
                        inp.push_back(input.at(j));
                    //}
                    if (input.at(j) == '\n') {
                        ++newLineNumber;
                    }
                }
                lineNumber = lineNumber + newLineNumber;

                break;
            }
            /*if (inputRead == -2) {
                
                maxMachine = machines.at(17);
                Token* newToken = maxMachine->CreateToken("", lineNumber);
                tokens.push_back(newToken);
                return tokens;
            }*/
            //cout << inputRead;
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxMachine = machines.at(i);
                maxNewLines = machines.at(i)->NewLinesRead();
                val = inputRead;
                break;
            }
           
        }
        if (errorCheck == -1) {
            break;
        }
        
        int newLineNumber = 0;
        for (int j = 0; j < val; ++j) {
            
            inp.push_back(input.at(j));
            
            if (input.at(j) == '\n') {
                ++newLineNumber;
            }
        }
        
        if (maxRead > 0) {
            string workPlz;
            //if (inp.size() > 0) {
                workPlz = inp;
            //}
            //else {
            //    workPlz = maxMachine->toMatch;
            //}
            //cout << "Do we make it here?" << endl;
            if (maxMachine != machines.at(15)) {
                Token* newToken = maxMachine->CreateToken(workPlz, lineNumber);
                tokens.push_back(newToken); // add newToken to collection of all tokens
            }
            
            //cout << newToken->tS();
            lineNumber = lineNumber + maxNewLines;
            
        }
        else { // No machine accepted the input, so it is invalid
            maxMachine = machines.at(16); //Undefined machine, last in machines vector
            maxRead = 1; // 1 gives comma?
            char invalid = input.at(0);
            string s = "";
            s.push_back(invalid);
            Token* newToken = maxMachine->CreateToken(s, lineNumber); //new invalid Token(with first character of input)
            tokens.push_back(newToken); // add newToken to collection of all tokens
        }
        
        input.erase(0, maxRead);
        //cout << "and here" << endl;
        int newLines = 0;
        for (long unsigned int i = 0; i < input.size(); ++i) {
            if (input.at(i) == '\n') {
                ++newLines;

            }
            else {
                break;
            }
        }
        
        if (newLines > 0) {
            lineNumber = lineNumber + newLines; //Add newLines to that count, add it to the token
            
            input.erase(0, newLines);
        }
        lineNumber = lineNumber + newLineNumber;
        //cout << input.size() << endl;
        if (input.size() > 0) {     

            while (isspace(input.at(0))) {
                if (input.at(0) == '\n') {
                    ++lineNumber;
                }
                input.erase(0, 1);
                //cout << input.size() << endl;
                if (input.size() == 0) {
                    maxMachine = machines.at(17);
                    
                    break;
                }
            }
        }
        //cout << input.size() << endl;
        if (input.size() > 0) {         
            while (input.at(0) == '\n') {
                ++lineNumber;
                input.erase(0, 1);
                if (input.size() == 0) {
                    maxMachine = machines.at(17);
                    
                    break;
                }
            }
        }
    
    }
    Automaton* EOFToken = new EOFAutomaton(EOFT);
    Token* newToken = EOFToken->CreateToken("", lineNumber);
    tokens.push_back(newToken);
    
    return tokens;
}