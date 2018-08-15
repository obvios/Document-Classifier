//
//  WordList.cpp
//  Programmin Assign 2
//
//  Created by Eric Palma on 3/2/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#include "WordList.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <list>

using namespace std;

WordList::WordList(){};

/*****************
     addWord()
 *****************/
void WordList::addWord(string theWord){
    //flag
    bool flag = false;
    list<Word>::iterator iterator = wordList.begin();
    //check if word is already in the wordList
    while (iterator!=wordList.end() && !flag) {
        if (iterator->word==theWord) {
            iterator->count++;
            flag = true;
        }
        iterator++;
    }//else, it is a new word
    if(!flag){
    Word newWord;
    newWord.word = theWord;
    wordList.push_back(newWord);
    }
}


void WordList::displayWordCount(){
    
    //sort the wordList
    wordList.sort(compare);
    
    list<Word>::iterator iterator = wordList.begin();
    while (iterator!=wordList.end()) {
        cout << iterator->word << " - " << iterator->count << endl;
        iterator++;
    }
}


//compare algorithm
bool WordList::compare(Word a, Word b){
    if (a.count > b.count) {
       return true;
    }else return false;
}

//add word from hash table
/*
 void WordList::addHashTable( string word, int count){
 
 }
 */


