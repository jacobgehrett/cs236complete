#include <iostream>
#include <vector>

using namespace std;

#include "Rule.h"

Rule::Rule() {
    ruleString = "";
    
    poorBoy = "";
    
}
Rule::~Rule() {}
string Rule::toString() {
    poorBoy = /*"  " +*/ ruleString + "(";
    for (unsigned int i = 0; i < (headP.size() - 1); ++i) {
        poorBoy = poorBoy + headP.at(i) + ",";
        
    }
    poorBoy = poorBoy + headP.at(headP.size() - 1) + ") :- ";
    for (unsigned int i = 0; i < (preds.size()); ++i) {
        poorBoy = poorBoy + preds.at(i).name + "(";
        for (unsigned int j = 0; j < (preds.at(i).paraList.size() - 1); ++j) {
            poorBoy = poorBoy + preds.at(i).paraList.at(j).toString() + ",";
        
        }
        poorBoy = poorBoy + preds.at(i).paraList.at(preds.at(i).paraList.size() - 1).toString() + "),";
    }
    
    poorBoy.at(poorBoy.size() - 1) = '.';
    return poorBoy;
}