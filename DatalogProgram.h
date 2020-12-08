#pragma once

#include <iostream>
#include <vector>
#include <set>

using namespace std;

#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

class DatalogProgram {
private:
    set<string> domain;
    
    int numElements;
    string dataString;

public:
    DatalogProgram();
    ~DatalogProgram();
    string toString();
    int numSchemes;
    int numFacts;
    int numRules;
    int numQueries;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
};