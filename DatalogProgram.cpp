#include <iostream>
#include <vector>

using namespace std;

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {
    numSchemes = 1;
    numFacts = 0;
    numRules = 0;
    numQueries = 1;
    numElements = 0;
    dataString = "";
}
DatalogProgram::~DatalogProgram() {}

string DatalogProgram::toString() {
    dataString = "Schemes(" + to_string(numSchemes) + "):\n";
    for (long unsigned int i = 0; i < schemes.size(); ++i) {
        dataString = dataString + schemes.at(i).toString() + "\n";
    }
    dataString = dataString + "Facts(" + to_string(numFacts) + "):\n";
    for (long unsigned int i = 0; i < facts.size(); ++i) {
        dataString = dataString + facts.at(i).toString() + ".\n";
    }
    dataString = dataString + "Rules(" + to_string(numRules) + "):\n";
    for (long unsigned int i = 0; i < rules.size(); ++i) {
        //cout << rules.at(0).ruleString << endl;
        dataString = dataString + rules.at(i).toString() + "\n";
    }
    dataString = dataString + "Queries(" + to_string(numQueries) + "):\n";
    for (long unsigned int i = 0; i < queries.size(); ++i) {
        dataString = dataString + queries.at(i).toString() + "?\n";
    }
    for (unsigned int i = 0; i < facts.size(); ++i) {
        for (unsigned int j = 0; j < (facts.at(i)).paraList.size(); ++j) {
            domain.insert((facts.at(i)).paraList.at(j).toString());
            //++numElements;
        }
    }
    for (auto it=domain.cbegin(); it != domain.cend(); ++it) {
        ++numElements;
    }
    dataString = dataString + "Domain(" + to_string(numElements) + "):\n";
    for (auto it=domain.cbegin(); it != domain.cend(); ++it) {
        dataString = dataString + "  " + *it + "\n";
    }

    return dataString;
}