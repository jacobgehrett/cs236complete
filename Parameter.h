#pragma once

#include <iostream>
#include <vector>

using namespace std;

#include "Token.h"
#include "Predicate.h"
//#include "Rule.h"

class Parameter {
private:
    
public:
    string paraString;
    Parameter();
    ~Parameter();
    string toString();
    bool isConstant;
};