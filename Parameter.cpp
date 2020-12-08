#include <iostream>
#include <vector>

using namespace std;

#include "Parameter.h"

Parameter::Parameter() {
    paraString = "";
}
Parameter::~Parameter() {}
string Parameter::toString() {
    
    return paraString;
}