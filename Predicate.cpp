#include <iostream>
#include <vector>

using namespace std;

#include "Predicate.h"

Predicate::Predicate() {
    predString = "";
    name = "";
}
Predicate::~Predicate() {}
string Predicate::toString() {
    predString = /*"  " +*/ name + "(";
    for (unsigned int i = 0; i < (paraList.size() - 1); ++i) {
        predString = predString + paraList.at(i).toString() + ",";
        
    }
    predString = predString + paraList.at(paraList.size() - 1).toString() + ")";
    return predString;
}
