//must use a set data type to hold the tuples, contains a set of Tuples associated with a name and Header
//relational operations (select, project, and rename) must be implemented as functions
    //select:  parameters are index and value (relation column and value to select)
    //select:  parameters are index and index (relation columns to select on same values)
    //project:  parameter is list of indices (the columns to keep)
    //rename:  parameter is list of attributes (defines the new header)
//relational operators must not produce relations with duplicate tuples or duplicate names in the header

#pragma once

#include <iostream>
#include <set>
#include <vector>

using namespace std;

#include "Tuple.h"
#include "Header.h"

class Relation {
private:
    
public:
    Relation(string name, Header header);
    ~Relation();
    Relation* select(int index, string value, Relation* r);
    Relation* iSelect(int index1, int index2, Relation* r);
    Relation* project(vector<int> keepColumns, Relation* r);
    Relation* rename(vector<string> attributes, Relation* r);
    void addTuple(Tuple tuple);
    string toString();
    set<Tuple> tuples;
    Header header;
    string name;
    Relation* Join(Relation* r1, Relation* r2);
    Header combineHeaders(Header h1, Header h2, vector<int>& v1, vector<int>& v2);
    bool isJoinable(const Tuple& t1, const Tuple& t2, vector<int>& v1, vector<int>& v2);
    Tuple combineTuples(const Tuple& t1, const Tuple& t2, vector<int>& v1, vector<int>& v2);
    Relation* unite(Relation& r1, Relation* r2, bool &inserted);
    bool inserted;
};