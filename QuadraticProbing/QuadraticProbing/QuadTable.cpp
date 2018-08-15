//
//  QuadTable.cpp
//  QuadraticProbing
//
//  Created by Eric Palma on 3/9/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#include "QuadTable.hpp"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

//Constructor
QuadTable::QuadTable(int size){
    tableSize = size;
    table = new item [tableSize];
    for (int i=0; i<size; i++) {
        table[i].word = "empty";
        table[i].count=0;
    }
}

//hashFunction
int QuadTable::hashFunction(string name){
    unsigned long int sum = 0;
    int x = 37;
    
    //Horner's algorithim
    for (int i = 0; i<name.length(); i++) {
        sum = (sum* x) + name[i];
    }
    
    return (sum%tableSize);
}


//addItem
void QuadTable::addItem(string name){
    int index = hashFunction(name);
    
    if (table[index].word=="empty" || table[index].word==name) {
        if (table[index].word==name) {
            table[index].count++;
        }else{
            //add to table
            table[index].word = name;
            table[index].count = 1;
            numItems++;
        }
    }else{                  //probe until empty index is found or a duplicate word is found
        probe(index, name);
        
    }
    //check load factor
    if (numItems/this->tableSize > .45) {
        //adjust table size
        adjustTableSize();
    }
    
}

//probe
void QuadTable::probe(int index, string word){
    unsigned long int i=1;
    bool flag = false;
    
    while (table[(index+i)% tableSize].word!="empty"|| table[(index+i)% tableSize].word==word) {            //changed to while does not == empty
        i++;
        i *=i;
        
        if (table[(index+i)% tableSize].word==word) {
            table[(index+i)%tableSize].count ++;
            flag = true; break;
        }
    }
    if (!flag) {
        table[(index+i)% tableSize].word= word;                 ///must be using null here
        table[(index+i)% tableSize].count = 1;
        numItems++;
    }
    
}

//adjust table size
void QuadTable::adjustTableSize(){
    int oldTableSize = this->tableSize;
    int newSize = this->tableSize*2;
    while (!isPrime(newSize)) {
        newSize++;
    }
    this->tableSize = newSize;
    //create new table
    item* newTable = new item[newSize];
    for (int i = 0; i < newSize; i++) {
        newTable[i].word = "empty";
        newTable[i].count=0;
    }
    //hash items onto new table
    for (int i = 0; i<oldTableSize; i++) {
       if(table[i].word!= "empty"){
        int index = hashFunction(table[i].word);
        if (newTable[index].word=="empty") {
            newTable[index].word = table[i].word;                             //pass over word
            newTable[index].count = table[i].count;                             //pass over count
        }else{
            unsigned long int x = 1;
            while (newTable[(index+ x)%newSize].word!= "empty") {              
                x++;
                x*=x;
            }
            newTable[(index+x)%newSize].word = table[i].word;         //pass over word
            newTable[(index+x)%newSize].count = table[i].count;         //pass over count
        }
      }
    }
    delete [] table;
    table = newTable;
}

//isPrime
bool QuadTable::isPrime(long int n){
    
    bool flag = true;
    for (int i =2; i < n/2; ++i) {
        if (n%i==0) {
            flag =false; break;
        }
    }
    
    return flag;
}

//display table
void QuadTable::displayTable(){
    for (int i =0; i<tableSize; i++) {
        //print elements
        cout << table[i].word << ", ";
    }
    cout << endl;
}

void QuadTable::displayCount(){             cout << "displaying count" << endl;
    list<item> theList;         //create the list
    for (int index =0; index<tableSize; index++) {      //iterate through table
        theList.push_back(table[index]);                //add item to list
    }
    
    theList.sort(compare);                              //sort the list
    //display list
    list<item>::iterator iterator = theList.begin();
    while (iterator!=theList.end()) {
        if(iterator->word!= "empty") cout << iterator->word << " - " << iterator->count << endl;
        iterator++;
    }
}

bool QuadTable::compare(item a, item b){
    return a.count > b.count;
}


