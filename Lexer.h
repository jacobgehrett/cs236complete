#pragma once
#include <iostream>
#include <vector>

using namespace std;

#include "Automaton.h"
#include "Token.h"
#include "MatcherAutomaton.h"
#include "Ident.h"
#include "CommentAutomaton.h"
#include "StringAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"

class Lexer {
private:
    vector<Token*> tokens;
public:
    Lexer ();
    ~Lexer ();
    vector<Token*> Run(string input);
    vector<Automaton*> machines;
    string identString;
};