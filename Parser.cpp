#include <iostream>
#include <vector>

using namespace std;

#include "Parser.h"

Parser::Parser(vector<Token*> myTokens) {
    miTokers = myTokens;
    isRule = false;
    numPreds = 0;
    expression = "";
}
Parser::~Parser() {}
DatalogProgram Parser::parse() {
    try {
        
        parseDatalogProgram();
        //cout << "Success!" << endl;
        
    } catch (Token* error) {
        cout << "Failure!" << endl;
        cout << "  " << error->tS();
        fail = true;
    }
    return myDLP;
    
}
void Parser::parseDatalogProgram() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "SCHEMES") {
        
        miTokers.erase(miTokers.begin());
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COLON") {
            miTokers.erase(miTokers.begin());
            parseScheme();
            parseSchemeList();
           
            if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "FACTS") {
                miTokers.erase(miTokers.begin());
                
                if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COLON") {
                    miTokers.erase(miTokers.begin());
                    
                    parseFactList();
     
                    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "RULES") {
                        miTokers.erase(miTokers.begin());
           
                        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COLON") {
                            miTokers.erase(miTokers.begin());
                            parseRuleList();
                            if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "QUERIES") {
                            miTokers.erase(miTokers.begin());
                            isRule = false;
                                if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COLON") {
                                    miTokers.erase(miTokers.begin());
                
                                    parseQuery();
                                    parseQueryList();
              
                                    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "EOF") {
                                        
                                    }
                                   
                                    else {
                                        throw (miTokers.at(0));
                                    }
                                    
                                }
                                else {
                                    throw (miTokers.at(0));
                                }
                            }
                            else {
                                throw (miTokers.at(0));
                            }
                        }
                        else {
                            throw (miTokers.at(0));
                        }
                    }
                    else {
                        throw (miTokers.at(0));
                    }

                }
                else {
                    throw (miTokers.at(0));
                }
            }
            else {
                throw (miTokers.at(0));
            }
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parseSchemeList() {
    
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        ++myDLP.numSchemes;
        parseScheme();
        parseSchemeList();
    }
    else {
        return;
    }

}
void Parser::parseFactList() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        ++myDLP.numFacts;
        parseFact();
        parseFactList();
    }
    else {
        
        return;
    }
}
void Parser::parseRuleList() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        ++myDLP.numRules;
        //ruleTmp.preds.clear();
        parseRule();

        parseRuleList();
    }
    else {
        return;
    }
}
void Parser::parseQueryList() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        ++myDLP.numQueries;
        parseQuery();
        parseQueryList();
          //cout << "here" << endl;
    }
    else {
        return;
    }
}
void Parser::parseScheme() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        predTmp.paraList.clear();
        predTmp.name = miTokers.at(0)->value;
        miTokers.erase(miTokers.begin());
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "LEFT_PAREN") {
            miTokers.erase(miTokers.begin());
            
            if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
                paraTmp.paraString = miTokers.at(0)->value;
                paraTmp.isConstant = false;
                predTmp.paraList.push_back(paraTmp);
                miTokers.erase(miTokers.begin());
                
                parseIdList();
                if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "RIGHT_PAREN") {
                    miTokers.erase(miTokers.begin());
                    myDLP.schemes.push_back(predTmp);
                }
                else {
                    throw (miTokers.at(0));
                }
            }
            else {
                throw (miTokers.at(0));
            }
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parseFact() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        predTmp.paraList.clear();
        predTmp.name = miTokers.at(0)->value;
        miTokers.erase(miTokers.begin());
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "LEFT_PAREN") {
            miTokers.erase(miTokers.begin());
            
            if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "STRING") {
                paraTmp.paraString = miTokers.at(0)->value;
                paraTmp.isConstant = true;
                predTmp.paraList.push_back(paraTmp);
                miTokers.erase(miTokers.begin());
                parseStringList();
                if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "RIGHT_PAREN") {
                    miTokers.erase(miTokers.begin());
                    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "PERIOD") {
                        miTokers.erase(miTokers.begin());
                        myDLP.facts.push_back(predTmp);
                    }
                    else {
                        throw (miTokers.at(0));
                    }
                }
                else {
                    throw (miTokers.at(0));
                }
            }
            else {
                throw (miTokers.at(0));
            }
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parseRule() {
    ruleTmp.preds.clear();
    predTmp.paraList.clear();
    
    parseHeadPredicate();
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COLON_DASH") {
        miTokers.erase(miTokers.begin());
        //cout << miTokers.at(0)->tS() << endl;
        parsePredicate();
        ruleTmp.preds.push_back(predTmp);
        predTmp.paraList.clear();
        ++numPreds;
        parsePredicateList();
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "PERIOD") {
            miTokers.erase(miTokers.begin());
            //cout << ruleTmp.ruleString;
            myDLP.rules.push_back(ruleTmp);
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parseQuery() {
    predTmp.paraList.clear();
    parsePredicate();
   
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "Q_MARK") {
        miTokers.erase(miTokers.begin());
        myDLP.queries.push_back(predTmp);

    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parseHeadPredicate() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        
        ruleTmp.ruleString = miTokers.at(0)->value;
        
        miTokers.erase(miTokers.begin());

        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "LEFT_PAREN") {
            miTokers.erase(miTokers.begin());
            if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
                ruleTmp.headP.clear();
                ruleTmp.headP.push_back(miTokers.at(0)->value);
                
                miTokers.erase(miTokers.begin());
                isRule = true;
                parseIdList();
                
                if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "RIGHT_PAREN") {
                    miTokers.erase(miTokers.begin());
                    
                }
                else {
                    throw (miTokers.at(0));
                }
            }
            else {
                throw (miTokers.at(0));
            }
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parsePredicate() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        tmpV.clear();
        tmpV.push_back(miTokers.at(0)->value);
        /*if (isRule == true) {
            
        }
        else {*/
            //cout << miTokers.at(0)->value << endl;
            predTmp.name = miTokers.at(0)->value;
            //ruleTmp.preds.push_back(tmpV);
        //}
        miTokers.erase(miTokers.begin());
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "LEFT_PAREN") {
            miTokers.erase(miTokers.begin());
            parseParameter();
            /*if (isRule == true) {
                ruleTmp.preds.at(ruleTmp.preds.size() - 1).push_back(expression);
            }
            else {*/
            paraTmp.paraString = expression;
            if (expression.at(0) == '\'') {
                paraTmp.isConstant = true;

            }
            else {
                paraTmp.isConstant = false;
            }
            predTmp.paraList.push_back(paraTmp);
            //ruleTmp.preds.push_back(predTmp);
            //}
            expression = "";
            parseParameterList();
            if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "RIGHT_PAREN") {
                miTokers.erase(miTokers.begin());
            }
            else {
                throw (miTokers.at(0));
            }
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parsePredicateList() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COMMA") {
        miTokers.erase(miTokers.begin());
        parsePredicate();
        if (isRule == true) {
            ruleTmp.preds.push_back(predTmp);
            predTmp.paraList.clear();
        }
        ++numPreds;
        parsePredicateList();
    }
    else {
        return;
    }
}
void Parser::parseParameterList() {

    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COMMA") {
        miTokers.erase(miTokers.begin());
        parseParameter();
        /*if (isRule == true) {
            ruleTmp.preds.at(ruleTmp.preds.size() - 1).push_back(expression);
        }
        else {*/
        paraTmp.paraString = expression;
        predTmp.paraList.push_back(paraTmp);
        //}
        expression = "";
        parseParameterList();
    }
    else {
        return;
    }
}
void Parser::parseStringList() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COMMA") {
        miTokers.erase(miTokers.begin());
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "STRING") {
            paraTmp.paraString = miTokers.at(0)->value;
            predTmp.paraList.push_back(paraTmp);
            miTokers.erase(miTokers.begin());
            parseStringList();
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        return;
    }
}
void Parser::parseIdList() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "COMMA") {
        miTokers.erase(miTokers.begin());
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
            if (isRule == false) {
                paraTmp.paraString = miTokers.at(0)->value;
                predTmp.paraList.push_back(paraTmp);
            }
            else {
                ruleTmp.headP.push_back(miTokers.at(0)->value);
            }
            miTokers.erase(miTokers.begin());
            parseIdList();
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        return;
    }
}
void Parser::parseParameter() {
    //expression = "";
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "STRING") {
        expression = expression + miTokers.at(0)->value;
        
        miTokers.erase(miTokers.begin());
    }
    else if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ID") {
        expression = expression + miTokers.at(0)->value;
        miTokers.erase(miTokers.begin());
    }
    else {
        parseExpression();

    }
    
}
void Parser::parseExpression() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "LEFT_PAREN") {
        miTokers.erase(miTokers.begin());
        expression = expression + "(";
        parseParameter();
        parseOperator();
        parseParameter();
        expression = expression + ")";
        if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "RIGHT_PAREN") {
            miTokers.erase(miTokers.begin());
        }
        else {
            throw (miTokers.at(0));
        }
    }
    else {
        throw (miTokers.at(0));
    }
}
void Parser::parseOperator() {
    if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "ADD") {
        expression = expression + miTokers.at(0)->value;
        miTokers.erase(miTokers.begin());
    }
    else if ((miTokers.at(0)->typeToString(miTokers.at(0)->type)) == "MULTIPLY") {
        expression = expression + miTokers.at(0)->value;
        miTokers.erase(miTokers.begin());
    }
    else {
        throw (miTokers.at(0));
    }
}