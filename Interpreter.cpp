/*constants are DatalogSTRINGs and variables are DatalogIDs:*/
//Relation* Interpreter::evaluatePredicate(const Predicate p) //strongly encouraged/suggested by Project 3 guide to use pointer here

#include <iostream>
#include <map>

using namespace std;

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram dP) {
    
    this->dP = dP;
    for (int i = 0; i < dP.numSchemes; ++i) {
   
        string rName = dP.schemes.at(i).name;
        
        Header headr;
      
        for (unsigned int j = 0; j < dP.schemes.at(i).paraList.size(); ++j) {
            
            headr.attributes.push_back(dP.schemes.at(i).paraList.at(j).toString());
            
        }
        Relation* r = new Relation(rName, headr);
        
        dB.nameRelation.insert({rName, *r});
        
    }
    
    for (int i = 0; i < dP.numFacts; ++i) {
        Tuple t;
        for (long unsigned int j = 0; j < dP.facts.at(i).paraList.size(); ++j) {
            t.values.push_back(dP.facts.at(i).paraList.at(j).toString());
        }
        dB.nameRelation.at(dP.facts.at(i).name).addTuple(t); //make a tuple ‘t’ using the values from ‘f’
                                                             //add ‘t’ to relation with the same name as ‘f’
        
    }
}

Interpreter::~Interpreter() {}

Relation* Interpreter::evaluatePredicate(const Predicate p, Relation* r) {
    map<string, int> checkDoubles;
    vector<string> stringDoubles;
    vector<int> intDoubles;
    //cout << r->tuples.size();
    //cout << r->toString();
    //for (const Tuple& t : r->tuples) {
        for (long unsigned int j = 0; j < p.paraList.size(); ++j) {
            //cout << p.paraList.at(j).paraString << endl;
            if (p.paraList.at(j).paraString.at(0) == '\'') {
                //cout << p.paraList.at(j).paraString << endl;
                //cout << "no here" << endl;
                r = r->select(j, p.paraList.at(j).paraString, r);
                
                //cout << "here" << endl;;
            }
            else if (checkDoubles.find(p.paraList.at(j).paraString) == checkDoubles.end()) {
              //  cout << "maybe here huh" << endl;
                //cout << t.values.at(j);
                //cout << p.paraList.at(j).paraString << endl;
                checkDoubles[p.paraList.at(j).paraString] = j;
                stringDoubles.push_back(p.paraList.at(j).paraString);
                //cout << stringDoubles.size();
                intDoubles.push_back(j);
            }
            else /*if (checkDoubles.find(p.paraList.at(j).paraString) != checkDoubles.end())*/ {
            //    cout << " cout totes ha" << endl;
                int twice = checkDoubles.at(p.paraList.at(j).paraString);
                r = r->iSelect(twice, j, r);
          //      cout << "probs here tho" << endl;
            }
            
        //    cout << "how did we get here" << endl;
        }
      //  cout << "yooooo " << endl;
    //}
    //cout << "do we get this far?" << endl;
    r = r->project(intDoubles, r);
    //cout << "but which one " << endl;
    r = r->rename(stringDoubles, r);
    //cout << "wait" << endl;
    return r;
}

void Interpreter::evalQueries() {
    /*for each query ‘q’
        get the relation ‘r’ with the same name as the query ‘q’
        select for each constant in the query ‘q’
        select for each pair of matching variables in ‘q’
        project using the positions of the variables in ‘q’
        rename to match the names of variables in ‘q’
        print the resulting relation
    }*/
    
    for (int i = 0; i < dP.numQueries; ++i) {
        //cout << numQueries << endl;
        Relation* r = new Relation(dB.nameRelation.at(dP.queries.at(i).name));
        //cout << "this far?" << endl;
        //cout << dP.queries.at(i).toString() << endl;
        //cout << dB.nameRelation.at(dP.queries.at(i).name).header.attributes.size() << endl;
        //cout << r->toString();
        r = evaluatePredicate(dP.queries.at(i), r);
        std::cout << dP.queries.at(i).toString() << "? ";
        //cout << "mystery" << endl;
        std::cout << r->toString();
        
    }
    
}

void Interpreter::evalRules() {
    while (keepGoing == true) {
    //for (int l = 0; l < 3; ++l) {
        keepGoing = false;
        for (int i = 0; i < dP.numRules; ++i) {
            
            vector<Relation*> rS;
            
            for (long unsigned int j = 0; j < dP.rules.at(i).preds.size(); ++j) {
                Relation* z = new Relation(dB.nameRelation.at(dP.rules.at(i).preds.at(j).name));
                
                rS.push_back(evaluatePredicate(dP.rules.at(i).preds.at(j), z));

            }
            
            Relation* r = rS.at(0);
            //cout << r->header.attributes.at(0) << endl;
            //cout << "here" << endl;
            for (long unsigned int j = 1; j < rS.size(); ++j) {
                r = r->Join(r, rS.at(j));
            }
            //cout << "binary work" << endl;
            //cout << r->toString();
            //cout << r->header.attributes.at(0) << endl;
            //cout << dP.rules.at(i).headP.at(0);
            vector<int> keeps;
            
            for (long unsigned int k = 0; k < dP.rules.at(i).headP.size(); ++k) {
                for (long unsigned int j = 0; j < r->header.attributes.size(); ++j) {
                
                    if (r->header.attributes.at(j) == dP.rules.at(i).headP.at(k)) {
                        keeps.push_back(j);
                    }
                }
            }
            //cout << keeps.at(1) << endl;
            r = r->project(keeps, r);
            //cout << r->toString() << endl;
            //cout << r->name << endl;
            r->name = dP.rules.at(i).ruleString;
            //cout << r->name << endl;
            for (long unsigned int j = 0; j < dB.nameRelation.at(r->name).header.attributes.size(); ++j) {
                r->header.attributes.at(j) = dB.nameRelation.at(r->name).header.attributes.at(j);
            }
            std::cout << dP.rules.at(i).toString() << endl;
            dB.nameRelation.at(r->name) = *r->unite(dB.nameRelation.at(r->name), r, inserted);
            
            if (inserted == true) {
                keepGoing = true;
            }
            
        }
        ++n;
        //cout << inserted << endl;
    }
    //cout << changedRules.size();
    //for (unsigned int i = 0; i < changedRules.size(); ++i) {
    //    cout << changedRules.at(i) << endl;
    //}
    std::cout << "\nSchemes populated after " << n << " passes through the Rules.\n" << endl;
}