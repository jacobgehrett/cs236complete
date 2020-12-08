#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "Token.h"
#include "DatalogProgram.h"

class Parser {
private:
    vector<Token*> miTokers;
public:
    Parser (vector<Token*> tokers);
    ~Parser ();
    DatalogProgram myDLP;
    DatalogProgram parse();
    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();
    void parseExpression();
    void parseOperator();
    Predicate predTmp;
    Parameter paraTmp;
    Rule ruleTmp;
    bool isRule;
    int numPreds;
    vector<string> tmpV;
    string expression;
    bool fail = false;
};