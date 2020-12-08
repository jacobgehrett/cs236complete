#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

#include "Token.h"
#include "Lexer.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "Ident.h"
#include "CommentAutomaton.h"
#include "StringAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "Database.h"
#include "Header.h"
#include "Relation.h"
#include "Tuple.h"
#include "Interpreter.h"

int main(int argc, char* argv[]) {

    string fileName = argv[1];
    string contents = "";

    ifstream ifs (fileName);

    char c = ifs.get();
    
    while (ifs.good()) {
        contents.push_back(c);
        c = ifs.get();
    }

    ifs.close();
    

    Lexer myLexer;
    vector<Token*> finTokens;

    if (contents.size() > 0) {
        finTokens = myLexer.Run(contents);
    }
    else {
        
        Automaton* EOFToken = new EOFAutomaton(EOFT);
        Token* newToken = EOFToken->CreateToken("", 1);
        finTokens.push_back(newToken);
        
    }
    Parser myParser(finTokens);
    DatalogProgram myDLP = myParser.parse();
    /*if (myParser.fail == false) {
        cout << myDLP.toString();
    }*/
    
    // = new Interpreter(myDLP);
    Interpreter myInterpreter(myDLP);
    cout << "Rule Evaluation" << endl;
    myInterpreter.evalRules();
    cout << "Query Evaluation" << endl;
    //cout << myDLP.queries.at(0).toString() << endl;
    myInterpreter.evalQueries();
    
    return 0;
}