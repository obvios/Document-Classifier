//
//  SeparateChainTable.cpp
//  SeparateChainTable
//
//  Created by Eric Palma on 3/12/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#include "SeparateChainTable.hpp"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <cmath>
using namespace std;

//Constructor
SeparateChainTable::SeparateChainTable(int size){
    tableSize = size;
    table = new item* [tableSize];
    for (int i=0; i<tableSize; i++) {
        table[i] = NULL;
    }
}

//hashFunction
int SeparateChainTable::hashFunction(string theWord){
    unsigned long int sum = 0;
    int x = 37;
    
    //Horner's algorithim
    for (int i = 0; i<theWord.length(); i++) {
        sum = (sum* x) + theWord[i];
    }
    
    return (sum%tableSize);
}

//addItem
void SeparateChainTable::addItem(string theWord){
    int index = hashFunction(theWord);
    
    if (table[index]==NULL ){//index is available
        
        item* newItem = new item;
        newItem->word = theWord;
        newItem->count = 1;
        newItem->PFcount = 0;
        newItem->RFcount = 0;
        newItem->next = NULL;
        table[index] = newItem;
        numItems++;
        
    }else{                                         //index is occupied
        item* cur = table[index];
        bool flag = false;                                  //indicates if a dublicate was found in list
        while (cur->next!=NULL || cur->word== theWord) {
            if (cur->word==theWord) {                       //dublicate found
                cur->count++;
                flag = true;
                break;
            }
            cur = cur->next;
        }
        if (!flag) {                                //add item to end of chain
            item* newItem = new item;
            newItem->word = theWord;
            newItem->count = 1;
            newItem->PFcount = 0;
            newItem->RFcount = 0;
            newItem->next = NULL;
            cur->next = newItem;
            numItems++;
        }
    }
    if (numItems/this->tableSize > 1.0) {           //check load factor
        adjustTableSize();
    }
}



//adjust table size
void SeparateChainTable::adjustTableSize(){
    int oldTableSize = this->tableSize;
    int newTableSize = this->tableSize*2;
    this->tableSize = newTableSize;
    item** newTable = new item* [newTableSize];      //create new table
    
    for (int i=0; i<newTableSize; i++) {             //initialize new table
        newTable[i] = NULL;
    }
    
    for (int i=0; i<oldTableSize; i++) {             //hash items onto new table
        if(table[i]!=NULL){
            // this is the new code
            item* cur = table[i];                   //pointer to link
            while (cur!=NULL) {
                int index = hashFunction(cur->word);        //get current node's index
                if (newTable[index]==NULL) {
                    item* newItem= new item;
                    newItem->word = cur->word;
                    newItem->count = cur->count;
                    newItem->PFcount = cur->PFcount;
                    newItem->RFcount = cur->RFcount;
                    newItem->next = NULL;
                    newTable[index] = newItem;
                }else{
                    item* newCur = newTable[index];
                    while (newCur->next!=NULL) {
                        newCur = newCur->next;
                    }
                    item* newItem = new item;
                    newItem->word = cur->word;
                    newItem->count = cur->count;
                    newItem->PFcount = cur->PFcount;
                    newItem->RFcount = cur->RFcount;
                    newItem->next = NULL;
                    newCur->next = newItem;
                }
                cur = cur->next;
            }
        }
    }
    //delete all pointers in table here
    for (int i=0; i<oldTableSize; i++) {
        if(table[i]!=NULL){
            item* cur = table[i];
            while (cur!=NULL) {
                item* tempCur = cur;
                cur=cur->next;
                delete tempCur;
            }
        }
    }
    //end of deleting pointers
    delete [] table;
    table = newTable;
}

//find()
    bool SeparateChainTable::find(string theWord){
    int index = hashFunction(theWord);
    
    if (table[index]!=NULL) {
        item* cur = table[index];
        while (cur!=NULL) {
            if (cur->word==theWord) {
                return true;
            }
            cur=cur->next;
        }
    }
    return false;
}


//incPFcount()
void SeparateChainTable::incPFcount(string thisWord){
    int index = hashFunction(thisWord);
    item* cur = table[index];
    while (cur!=NULL) {
        if (cur->word==thisWord) {
            cur->PFcount++;
            return;
        }
        cur=cur->next;
    }
}

//incRFcount()
void SeparateChainTable::incRFcount(string thisWord){
    int index = hashFunction(thisWord);
    item* cur = table[index];
    while (cur!=NULL) {
        if (cur->word==thisWord) {
            cur->RFcount++;
            return;
        }
        cur=cur->next;
    }
}

//calcCorrelationFactor
double SeparateChainTable::calcCorrelationFactor(int a, int b){
    //used to calculate corr factor of first parameter. So a.
    double correlationFacotor;
    
    correlationFacotor = (a-b)/( (sqrt(static_cast<double>(a+b))) * (sqrt(static_cast<double>(1000-a-b)))  );
    
    return correlationFacotor;
}


//getPFcount()
int SeparateChainTable::getPFcount(string thisWord){
    int index = hashFunction(thisWord);
    item* cur = table[index];
    while (cur!=NULL) {
        if (cur->word==thisWord) {
            return cur->PFcount;
        }
        cur=cur->next;
    }
    return -1;
}

//getRFcount()
int SeparateChainTable::getRFcount(string thisWord){
    int index = hashFunction(thisWord);
    item* cur = table[index];
    while (cur!=NULL) {
        if (cur->word==thisWord) {
            return cur->RFcount;
        }
        cur=cur->next;
    }
    return -1;
}

//setPFCorrelationFactor
void SeparateChainTable::setPFcorrelationFactor(){
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                cur->PFCorrelationFactor = calcCorrelationFactor(cur->PFcount, cur->RFcount);        //setPFCorrelationFactor
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
}


//setRFCorrelationFactor
void SeparateChainTable::setRFcorrelationFactor(){
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                cur->RFCorrelationFactor = calcCorrelationFactor(cur->RFcount, cur->PFcount);        //setPFCorrelationFactor
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
}

//displayPFCorrelationFacotor()         political file correlation factor
void SeparateChainTable::displayPFCorrelationFactor(){
    list<item*> theList;
    
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                theList.push_back(cur);
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
    theList.sort(comparePFcorrelation);                          //sort list
    list<item*>::iterator iterator = theList.begin();
    while (iterator!=theList.end()) {               //display list
        cout << (*iterator)->word << " - " << (*iterator)->PFCorrelationFactor << endl;
        iterator++;
    }
}


//displayRFCorrelationFactor()      religion file correlation factor
void SeparateChainTable::displayRFCorrelationFactor(){
    list<item*> theList;
    
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                theList.push_back(cur);
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
    theList.sort(compareRFcorrelation);                          //sort list
    list<item*>::iterator iterator = theList.begin();
    while (iterator!=theList.end()) {               //display list
        cout << (*iterator)->word << " - " << (*iterator)->RFCorrelationFactor << endl;
        iterator++;
    }
}


//displayTable
void SeparateChainTable::displayTable(){
    
    for(int i=0;i<tableSize;i++){               //display each index
        cout << i;
        if (table[i]==NULL) {
            cout << "--> (empty)" << endl;
        }else{
            item* cur = table[i];
            while (cur != NULL) {                           //display all elements in the bucket
                cout << "-->" << cur->word;
                cur = cur->next;
            }
            cout << endl;
        }
    }
    
}

//displayCount
void SeparateChainTable::displayCount(){
    list<item*> theList;
    
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                theList.push_back(cur);
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
    theList.sort(compare);                          //sort list
    list<item*>::iterator iterator = theList.begin();
    while (iterator!=theList.end()) {               //display list
        cout << (*iterator)->word << " - " << (*iterator)->count << endl;
        iterator++;
    }
}

//compare
bool SeparateChainTable::compare(item* a, item* b){
    return (a->count > b->count);
}

//comparePFCorrelation
bool SeparateChainTable::comparePFcorrelation(item* a, item* b){
    return a->PFCorrelationFactor > b->PFCorrelationFactor;
}

//compareRFCorrelation
bool SeparateChainTable::compareRFcorrelation(item* a, item* b){
    return a->RFCorrelationFactor > b->RFCorrelationFactor;
}



//display PFcount
void SeparateChainTable::displayPFCount(){
    list<item*> theList;
    
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                theList.push_back(cur);
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
    list<item*>::iterator iterator = theList.begin();
    while (iterator!=theList.end()) {               //display list
        cout << (*iterator)->word << " - " << (*iterator)->PFcount << endl;
        iterator++;
    }

}

//display RFcount
void SeparateChainTable::displayRFCount(){
    list<item*> theList;
    
    for (int index =0; index<tableSize; index++) {  //start at first index and iterate through chained list
        if(table[index]!=NULL){
            item* cur = table[index];
            while (cur!= NULL) {                                //add all elements in bucket to list
                theList.push_back(cur);
                if (cur->next== NULL) {
                    break;
                }
                cur=cur->next;
            }
        }
    }
    list<item*>::iterator iterator = theList.begin();
    while (iterator!=theList.end()) {               //display list
        cout << (*iterator)->word << " - " << (*iterator)->RFcount << endl;
        iterator++;
    }
}

//getPFcorrelationFactor
double SeparateChainTable::getPFcorrelationFactor(string thisWord){
    int index = hashFunction(thisWord);
    item* cur = table[index];
    while (cur!=NULL) {
        if (cur->word==thisWord) {
            return cur->PFCorrelationFactor;
        }
        cur=cur->next;
    }
    return -1.0;
}

//getRFcorrelationFactor
double SeparateChainTable::getRFcorrelationFactor(string thisWord){
    int index = hashFunction(thisWord);
    item* cur = table[index];
    while (cur!=NULL) {
        if (cur->word==thisWord) {
            return cur->RFCorrelationFactor;
        }
        cur=cur->next;
    }
    return -1.0;
}





