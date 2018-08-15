//
//  SeparateChainTable.hpp
//  SeparateChainTable
//
//  Created by Eric Palma on 3/12/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#ifndef SeparateChainTable_hpp
#define SeparateChainTable_hpp

#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

class SeparateChainTable {
    //structure
    struct item{
        string word;
        int count;
        int PFcount;
        int RFcount;
        double PFCorrelationFactor;
        double RFCorrelationFactor;
        item* next;
    };
    
    int tableSize ;
    item** table;
    double numItems;
    
public:
    SeparateChainTable(int size);
    int hashFunction(string n);
    void addItem(string n);
    void displayTable();
    void displayCount();
    static bool compare(item*,item*);
    static bool comparePFcorrelation(item*,item*);
    static bool compareRFcorrelation(item*,item*);
    void adjustTableSize();     
    bool find(string);
    void incPFcount(string);
    void incRFcount(string);
    int getPFcount(string);
    int getRFcount(string);
    void setPFcorrelationFactor();
    void setRFcorrelationFactor();
    double getPFcorrelationFactor(string);
    double getRFcorrelationFactor(string);
    static double calcCorrelationFactor(int,int);
    void displayPFCorrelationFactor();
    void displayRFCorrelationFactor();
    void displayPFCount();                          //for testing
    void displayRFCount();                          //for testing
    
    ~SeparateChainTable(){
        for (int i=0; i<tableSize; i++) {
            if(table[i]!=NULL){
                item* cur = table[i];
                while (cur!=NULL) {
                    item* tempCur = cur;
                    cur=cur->next;
                    delete tempCur;
                }
            }
        }
        delete [] table;
    }
    
};

#endif /* SeparateChainTable_hpp */

