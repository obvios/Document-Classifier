//
//  WordList.hpp
//  Programmin Assign 2
//
//  Created by Eric Palma on 3/2/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#ifndef WordList_hpp
#define WordList_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <list>
using namespace std;

class WordList {
    struct Word{
        string word;
        int count = 1;
    };
    list<Word> wordList;
public:
    WordList();
    void addWord(string);
    void displayWordCount();
    static bool compare(Word , Word );
    //void bubbleSort(list<Word>&);
    
};

#endif /* WordList_hpp */
