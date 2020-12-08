#include <iostream>

using namespace std;

#include "Tuple.h"

Tuple::Tuple() {}
Tuple::~Tuple() {}
bool Tuple::operator< (const Tuple & other) const {
    // compare this Tuple to other Tuple
    
    return (this->values < other.values);
}