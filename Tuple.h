//contains vector of values (string)

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Tuple {
private:
public:
    Tuple();
    ~Tuple();
    bool operator< (const Tuple & other) const;
    vector<string> values;
};