//
//  QuadTable.hpp
//  QuadraticProbing
//
//  Created by Eric Palma on 3/9/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#ifndef QuadTable_hpp
#define QuadTable_hpp

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

class QuadTable {
    //structure
    struct item{
        string word;
        int count;
    };
    int tableSize ;
    item* table;
    double numItems;
    
public:
    QuadTable(int size);
    int hashFunction(string n);
    void addItem(string n);
    void displayTable();
    void displayCount();
    static bool compare(item,item);
    void adjustTableSize();     //used to resize if
    bool isPrime(long int );         //to check if table size is prime
    void probe(int,string);
    ~QuadTable(){
        delete [] table;
        cout << "destroying hash table" << endl;
    }
};



#endif /* QuadTable_hpp */
