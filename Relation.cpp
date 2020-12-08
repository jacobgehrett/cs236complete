#include <iostream>
#include <vector>

using namespace std;

#include "Relation.h"

Relation::Relation(string name, Header header) {
    this->name = name;
    this->header = header;
    tuples.clear();
    
}
Relation::~Relation() {}
Relation* Relation::select(int index, string value, Relation* r) { //take constant and select on certain index
    //cout << column << endl;
    //cout << value << endl;
    Relation* newR = new Relation(r->name, r->header);
    
    for (const Tuple& t : r->tuples) { 
        if (t.values.at(index) == value) {
            newR->addTuple(t);
        }
        
    }
    //cout << newR-> toString();
    return newR;
}
Relation* Relation::iSelect(int index1, int index2, Relation* r) { //needs to check and make sure the values are the same
    Relation* newR = new Relation(r->name, r->header);
    
    for (const Tuple& t : r->tuples) { 
        if (t.values.at(index1) == t.values.at(index2)) {
            newR->addTuple(t);
        }
    }

    return newR;
}
Relation* Relation::project(vector<int> keepColumns, Relation* r) { //only keep certain columns of each tuple
    Header headr;
    Relation* newR = new Relation(r->name, headr);
    //cout << "here" << endl;
    
    for (long unsigned int i = 0; i < keepColumns.size(); ++i) {
        //cout << keepColumns.at(i) << endl;
        //cout << i << endl;
        //cout << r->header.attributes.size() << endl;
        newR->header.attributes.push_back(r->header.attributes.at(keepColumns.at(i)));
        //cout << "not sure about this guy" << endl;
    }
    //cout << "or here" << endl;
    for (const Tuple& t : r->tuples) {
        Tuple tt;
        for (long unsigned int i = 0; i < keepColumns.size(); ++i) {
           //cout << i << endl;
            tt.values.push_back(t.values.at(keepColumns.at(i)));
                //cout << r->tuples.size();
        }
        newR->addTuple(tt);
    }
    //cout << "here?" << endl;
    //cout << newR->tuples.size();
    return newR;
}
Relation* Relation::rename(vector<string> attributes, Relation* r) {
    Header headr;
    Relation* newR = new Relation(r->name, headr);
    //cout << headr.attributes.size();
    for (long unsigned int i = 0; i < attributes.size(); ++i) {
        //cout << attributes.at(i);
        newR->header.attributes.push_back(attributes.at(i));
        //cout << headr.attributes.at(i);
    }
    
    for (const Tuple& t : r->tuples) {
        
        newR->addTuple(t);
    
    }
    //cout << newR->header.attributes.size();
    return newR;
}
void Relation::addTuple(Tuple tuple) {
    tuples.insert(tuple);
}
string Relation::toString() {
    //cout << "here" << endl;
    string myString = "";
    //cout << "here2" << endl;
    if (tuples.size() > 0) {
        ///cout << header.attributes.at(0) << endl;
        //cout << "need more options" << endl;
        myString = myString + "Yes(" + to_string(tuples.size()) + ")\n";
        for (const Tuple& t : tuples) {
            //cout << header.attributes.size() - 1 << endl;
            if (header.attributes.size() > 0) {
                myString = myString + "  ";
                for (long unsigned int i = 0; i < header.attributes.size() - 1; ++i) {
                //  cout << header.attributes.size() << endl;;
                    myString = myString + header.attributes.at(i) + "=" + t.values.at(i) + ", ";
                    
                }
                //cout << "breuh" << endl;
                
                if (header.attributes.size() == 1) {
                //  cout << "option1" << endl;
                    myString = myString + header.attributes.at(header.attributes.size() - 1) + "=" + t.values.at(t.values.size() - 1) + "\n";
                    //cout << "onefer" << endl;
                }
                else {
                    //cout << "option2" << endl;
                    myString = myString + header.attributes.at(header.attributes.size() - 1) + "=" + t.values.at(t.values.size() - 1) + "\n";
                    //cout << "twofer" << endl;
                }
            }
        }
       
    }
    else {
        myString = myString + "No\n";
    }
    //cout << "here" << endl;
    return myString;
}
Relation* Relation::Join(Relation* r1, Relation* r2) {
    //cout << "see" << endl;
    vector<int> v1;
    vector<int> v2;
    Header h = combineHeaders(r1->header, r2->header, v1, v2);//make the header h for the result relation
	    //(combine r1's header with r2's header)
    //cout << "bruh" << endl;
	Relation* newR = new Relation(r1->name, h);//make a new empty relation r using header h
    //cout << "gimme a hint here" << endl;
    for (const Tuple& t : r1->tuples) {
        for (const Tuple& tt : r2->tuples) {
            if (isJoinable(t, tt, v1, v2)) {
                const Tuple& joinedT = combineTuples(t, tt, v1, v2);
                newR->addTuple(joinedT);
            }
        }
    }  
    /*  for each tuple t1 in r1
	    for each tuple t2 in r2

		if t1 and t2 can join
		    join t1 and t2 to make tuple t
		    add tuple t to relation r
		end if

	    end for
	end for*/
   
    //cout << "what" << endl;
    return newR;
}
Header Relation::combineHeaders(Header h1, Header h2, vector<int>& v1, vector<int>& v2) {
    Header hC = h1;
    for (long unsigned int i = 0; i < h2.attributes.size(); ++i) {
        bool exists = false;
        for (long unsigned int j = 0; j < h1.attributes.size(); ++j) {
            if (h2.attributes.at(i) == h1.attributes.at(j)) {
                exists = true;
                v1.push_back(j);
                v2.push_back(i);
                break;
            }
        }
        if (exists == false) {
            hC.attributes.push_back(h2.attributes.at(i));
        }
    }
    return hC;
}
bool Relation::isJoinable(const Tuple& t1, const Tuple& t2, vector<int>& v1, vector<int>& v2) {
    for (long unsigned int i = 0; i < v1.size(); ++i) {
        if (t1.values.at(v1.at(i)) != t2.values.at(v2.at(i))) {
            return false;
        }
    }
    return true;
}
Tuple Relation::combineTuples(const Tuple& t1, const Tuple& t2, vector<int>& v1, vector<int>& v2) {
    Tuple ttt;
    for (long unsigned int i = 0; i < t1.values.size(); ++i) {
        ttt.values.push_back(t1.values.at(i));
    }
    for (long unsigned int i = 0; i < t2.values.size(); ++i) {
        bool works = true;
        for (long unsigned int j = 0; j < v2.size(); ++j) {
            long unsigned int converted = v2.at(j);
            if (i == converted) {
                works = false;
            }
        }
        if (works == true) {
            ttt.values.push_back(t2.values.at(i));
        }

    }
    
    return ttt;
}
Relation* Relation::unite(Relation& r1, Relation* r2, bool &inserted) {
    Relation* improvedR = new Relation(r1);
    Relation* outPutR = new Relation(r2->name, r2->header);
    //cout << r2->tuples.size();
    for (const Tuple& t : r2->tuples) {
        //cout << "here" << endl;
        if (improvedR->tuples.insert(t).second) {
            inserted = true;
            outPutR->addTuple(t);
        
        }
        else {
            inserted = false;
        }
    }
    //cout << outPutR->tuples.size() << " " << inserted;
    if (outPutR->tuples.size() > 0) {
        inserted = true;
        string fixOptions = outPutR->toString();
        int parenInt = 0;
        for (long unsigned int j = 0; j < fixOptions.size(); ++j) {
            if (fixOptions.at(j) == ')') {
                parenInt = j + 2;
            }
        }
        if (fixOptions.at(0) == 'Y') {
            fixOptions.erase(0, parenInt);
        }
        else {
            fixOptions.erase(0, 3);
        }
        cout << fixOptions;
    }
    //inserted = false;
    //cout << inserted << endl;
    return improvedR;
}