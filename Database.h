//contains a map from name (string) to Relation

#pragma once

#include <iostream>
#include <map>

using namespace std;

#include "Relation.h"

class Database {
private:
    
public:
    Database();
    ~Database();
    map<string, Relation> nameRelation;
};