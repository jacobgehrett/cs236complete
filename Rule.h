#pragma once

#include <iostream>
#include <vector>

using namespace std;

//#include "Token.h"
#include "Predicate.h"
//#include "Parameter.h"

class Rule {
private:
    
    string poorBoy;
    
public:
    Rule();
    ~Rule();
    string ruleString;
    string toString();
    
    vector<Predicate> preds;
    vector<string> headP;
    
};