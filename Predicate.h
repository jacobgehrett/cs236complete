#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "Token.h"
#include "Parameter.h"
//#include "Rule.h"

class Parameter;

class Predicate {
private:
    
    string predString;
public:
    Predicate();
    ~Predicate();
    vector<Parameter> paraList;
    string toString();
    string name;
};