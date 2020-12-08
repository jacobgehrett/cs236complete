//There should be no coupling between Datalog and Database classes.  Either the interpreter needs these two object at construction, 
//or pass them by pointer or reference to the method that will run the interpretation.

#pragma once

#include <iostream>

using namespace std;

#include "DatalogProgram.h"
#include "Database.h"
//#include "Relation.h"

class Interpreter {
private:
    DatalogProgram dP;
    Database dB;
    vector<string> changedRules;
    int n = 0;
public:
    Interpreter(DatalogProgram dP);
    ~Interpreter();
    Relation* evaluatePredicate(const Predicate p, Relation*);
    void evalQueries();
    void evalRules();
    bool inserted = false;
    bool keepGoing = true;
};