//
//  main.cpp
//  Programmin Assign 2
//
//  Created by Eric Palma on 2/15/18.
//  Copyright © 2018 Eric Palma. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <fstream>
#include <ctime>
#include "WordList.hpp"
#include "QuadTable.hpp"
#include "SeparateChainTable.hpp"


using namespace std;

/****************************
 *      function prototypes *
 ***************************/
int calcKeyPolynomial(string thisString);
vector<string> getStringList(string );
void printKeyPolynomial(string n);
void cleanWord(string &);
void readPoliticalFiles(int,int, SeparateChainTable &table);
void readReligionFiles(int,int, SeparateChainTable &table);
int classifyFiles(int ,int , double , SeparateChainTable &table);
bool isDiscriminator(string, double, SeparateChainTable &table);
int coinToss();
void displayCorrectness(int fileNumber, int, int&);

/****************************
 *********  MAIN  ***********
 ****************************/
int main(int argc, const char * argv[]) {
    
    /*Variables*/
    char Y_N;                   //variable to hold user's option to continue or not
    int userSelection;
    string userString;
    vector<string> userList;
    int tableSize;
    clock_t elapsedTime;        //used to calculate elapsed time
    srand(time(0));
    /*End Of Variables*/
    
    /*while loop that runs as long as user chooses y/Y*/
    do {
        /*display options*/
        cout << "Option 1: Input a string and return it's key polynomial" << endl;
        cout << "\nOption 2: Input a size for an initially empty separate-chaning hash table," << endl;
        cout << "   along with a list of words to insert into the table. Program returns a vertical" << endl ;
        cout << "   representation of the table." << endl;
        cout << "\nOption 3: Input a prime-number size for an initially empty quadratic-probing hash table," << endl;
        cout << "   along with a list of words to insert into the table. Program returns a horizontal" << endl;
        cout << "   representation of the table" << endl;
        cout << "\nOption 4: Input the name of a file to clean" << endl;
        cout << "\nOption 5: Input name of file, select data structure, print word frequencies, and elapsed times." << endl;
        cout << "\nOption 6: Extra credit." << endl;
        cout << "\nOption 7: Extra credit 2." << endl;
        cout << "\nYour choice: ";
        cin >> userSelection;
        
        /*Choice 1*/
        if (userSelection==1) {
            cout << "Input string: ";
            cin >> userString;
            cout << "The Key Polynomial of the string is: " << calcKeyPolynomial(userString) << endl;
        }
        
        /*Choice 2*/
        if (userSelection==2) {     //run option 2
            cin.get();
            cout << "Enter size of table: ";
            cin >> tableSize;
            cout << "Enter a list of words: ";
            cin.get();
            getline(cin, userString);
            //convert to list
            userList = getStringList(userString);
            //create hash table
            SeparateChainTable hashTable(tableSize);            ///changed from Hash
            //input strings into hash table
            for (int i = 0; i < userList.size(); i++) {
                hashTable.addItem(userList[i]);
            }
            cout << "displaying hash table" << endl;
            hashTable.displayTable();
        }
        
        /*Choice 3 */
        if (userSelection==3) {
            cout << "Enter a prime number: ";
            cin >> tableSize;
            //get list of words
            cout << "Enter a list of words: ";
            cin.get();
            getline(cin,userString);
            //convert string of words to list
            userList = getStringList(userString);
            //create quadratic probing hash table
            //////Quad_Probe_HashTable quadHashTable(tableSize);
            QuadTable quadHashTable(tableSize);
            //input names into hash table
            for (int i=0 ; i < userList.size(); i++) {
                //add names
                quadHashTable.addItem(userList[i]);
            }
            //display table
            quadHashTable.displayTable();
        }
        
        /* Choice 4 */
        if (userSelection==4) {
            /* Variables */
            string fileName;
            ifstream textFile;                  //create a variable to read file in
            vector<string> file; string word;   //vector file holds strings passed in from word string
            cout << "File Name: " ;
            cin >> fileName;
            textFile.open(fileName);      //open the file
            //open the file
            if(textFile.is_open()){             //check that file opened
                while(!textFile.eof()){
                    textFile>>word;             //read string into word variable
                    cleanWord(word);             //clean word
                    file.push_back(word);       //push back to vector
                }
                textFile.close();               //close the file when finished
                
                //print vector
                for (int i = 0; i<file.size(); i++) {
                    cout << file[i] << " " ;
                }
                cout << endl;
            }else{
                cout <<"Error opening file" << endl;
            }
            
        }
        
        /*Choice 5*/
        if(userSelection == 5){
            /* Variables */
            string fileName;
            ifstream textFile;
            int dataStruct;
            vector<string> file; string word;       //vector holds each word passed to it
            /*End of Variables*/
            
            //prompt user to input name of file
            cout << "File Name: ";
            cin >> fileName; cin.get();             //may need to get rid of the get()****
            
            //prompt user to select the type of data structure (ie:list,separate chaining table, or quadratic probing
            cout << "Select Data Structure" << endl;
            cout << "1) List  2)  Separate Chaining Table  3)  Quadratic Probing Table" << endl;
            cout << "Your choice: ";
            cin >> dataStruct;
            
            /* Run selected data structure*/
            
            //If user selects to use a List data structure
            if (dataStruct ==1) {
                elapsedTime = clock();
                WordList wordList;
                
                textFile.open(fileName);            //open the file
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        wordList.addWord(word);     //add word to list
                    }
                }
                textFile.close();
                wordList.displayWordCount();        //display word count
                elapsedTime = clock() - elapsedTime;
                cout << "elapsed time: " << elapsedTime/CLOCKS_PER_SEC << " seconds" << endl;
            }
            //If user selects to use a separate chaining
            if (dataStruct==2) {
                elapsedTime = clock();
                SeparateChainTable hashTable(100);
                textFile.open(fileName);            //open the file
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        hashTable.addItem(word);
                    }
                    textFile.close();
                }
                //textFile.close();
                hashTable.displayCount();       //change to display count
                elapsedTime = elapsedTime - clock();
                cout << "elapsed time: " << elapsedTime*1.0/CLOCKS_PER_SEC << " milliseconds" << endl;
            }
            //If user selects to use quadratic probing
            if (dataStruct==3) {
                //create quad probing object
                elapsedTime = clock();
                QuadTable quadHashTable(541);
                
                textFile.open(fileName);
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        quadHashTable.addItem(word);
                    }
                }
                textFile.close();
                quadHashTable.displayCount();
                elapsedTime = elapsedTime - clock();
                cout << "elapsed time: " << elapsedTime*1.0/CLOCKS_PER_SEC << " milliseconds" << endl;
            }
        }
        /*End of choice 5*/
        
        /* Choice 6 Extra Credit*/
        if (userSelection==6) {
            string fileName;
            ifstream textFile;
            string word;
            SeparateChainTable hashTable(300000);
            
            readPoliticalFiles(176845, 178604, hashTable);      //read half the files in talks.politics.miscalleneous folder
            readReligionFiles(82757, 83876, hashTable);         //read half the files in talks.religion.miscallaneous folder
            cout << "Training set was created" << endl;
            cout << "press Enter to count Political files each word in training set appears in" << endl;
            cin.get(); cin.get();
            
            //cycle through each word in hashTable and track number of Political files each word appears in
            int fileNumber = 1;                     //used to check if word already appeared in file
            for (int i=176845; i<=178604; i++) {
                fileName = to_string(i);
                textFile.open(fileName);
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        if (hashTable.find(word) && hashTable.getPFcount(word)<fileNumber) {
                            hashTable.incPFcount(word);
                        }
                    }
                    textFile.close();
                }
                fileNumber++;
            }
            cout << "Done counting how many Political files eaach word in training set appears in" << endl;
            cout << "Press enter to count how many Religion files each word in training set appears in" << endl;
            cin.get();
            //cycle through each word in hashTable and track number of Religion files each word appears in
            fileNumber = 1;
            for (int i=82757; i<=83876; i++) {
                fileName = to_string(i);
                textFile.open(fileName);
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        if (hashTable.find(word) && hashTable.getRFcount(word)<fileNumber) {
                            hashTable.incRFcount(word);
                        }
                    }
                    textFile.close();
                }
                fileNumber++;
            }
            cout << "Done counting how many Religion files eaach word in training set appears in" << endl;
            cout << "Press enter to calculate Political correlation factor of each word in training set" << endl;
            cin.get();
            hashTable.setPFcorrelationFactor();
            cout << "Done setting Political file correlation factors" << endl;
            cout << "Press enter to calculate Religion correlation factor of each word" << endl;
            cin.get();
            hashTable.setRFcorrelationFactor();
            cout << "Done setting Religion correlation factors" << endl;
            cout << "Press enter to print words in decreasing order based on Political correlation facotor" << endl;
            cin.get();
            hashTable.displayPFCorrelationFactor();
            cout << "Press enter to print words in decreasing order based on Religion correlation factor" << endl;
            cin.get();
            for (int x =0; x <1000; x++) {
                cout << "\n-------------------------------------------------------------------------------------------------------";
            }
            hashTable.displayRFCorrelationFactor();
        }
        /*End of option 6*/
        
        /* Choice 7 extra credit*/
        if (userSelection==7) {
            //create training set D
            int correctCount=0;
            string fileName;
            ifstream textFile;
            string word;
            double threshold;
            SeparateChainTable hashTable(300000);               //training set
            
            cout << "Correlation Coefficient Threshold: " << endl;
            cin >> threshold;
            
            readPoliticalFiles(176845, 178604, hashTable);      //read half the files in talks.politics.miscalleneous folder
            readReligionFiles(82757, 83876, hashTable);         //read half the files in talks.religion.miscallaneous folder
            
            //cycle through each word in hashTable and track number of Political files each word appears in
            int fileNumber = 1;                     //used to check if word already appeared in file
            for (int i=176845; i<=178604; i++) {
                fileName = to_string(i);
                textFile.open(fileName);
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        if (hashTable.find(word) && hashTable.getPFcount(word)<fileNumber) {
                            hashTable.incPFcount(word);
                        }
                    }
                    textFile.close();
                }
                fileNumber++;
            }
            //cycle through each word in hashTable and track number of Religion files each word appears in
            fileNumber = 1;
            for (int i=82757; i<=83876; i++) {
                fileName = to_string(i);
                textFile.open(fileName);
                if (textFile.is_open()) {
                    while (!textFile.eof()) {
                        textFile >> word;
                        cleanWord(word);
                        if (hashTable.find(word) && hashTable.getRFcount(word)<fileNumber) {
                            hashTable.incRFcount(word);
                        }
                    }
                    textFile.close();
                }
                fileNumber++;
            }
            
            hashTable.setPFcorrelationFactor();         //set Political file correlation factor for words in training set
            hashTable.setRFcorrelationFactor();         //set Religion file correlation factor for words in training set
            
            //Read other half of files and use discriminators to categorize words
            correctCount += classifyFiles(178605, 179116, threshold, hashTable);
            correctCount += classifyFiles(83877, 84570, threshold, hashTable);
            cout << endl;
            cout << "Classified correctly = " << correctCount << endl;
        }
        /*End of option 7*/
        
        cout << "would you like to continue (y/n)? ";
        cin >> Y_N;
    } while (_toupper(Y_N) == 'Y' );
    /*End of While Loop*/
    
    return 0;
}
/****************************
 *      END OF MAIN         *
 ***************************/



/****************************
 *      calcKeyPolynomial   *
 ****************************/
int calcKeyPolynomial(string thisString){
    int sum = 0;
    int x = 37;
    
    //Horner's algorithim
    for (int i = 0; i<thisString.length(); i++) {
        sum = sum * x + thisString[i];
    }
    
    return sum;
}

/************************
 *  getStringList()     *
 ***********************/
vector<string> getStringList(string thisString){
    vector<string> thisList;
    string tempString;      //holds each word
    stringstream ss(thisString);    //convert string into fstream object
    
    while (getline(ss,thisString,',')){
        thisList.push_back(thisString);
        }
    
    
    
    return thisList;
}

/********************
 *     cleanWord()  *
 ******************/
void cleanWord(string &theString){
    char puntucations[12] = {',','.',';','!','?','(',')',':','/','"','\'','-'}; //holds all types of punctuations
    //check if the string contains any of the punctuations
    for (int i=0; i < 12; i++) {
        if(theString.find(puntucations[i])!= -1){       //puctuation found in string
            __SIZE_TYPE__ pos = theString.find(puntucations[i]);
            theString.erase(pos,1);
            i--;
        }
    }
    //lower all letters
    for (int i =0; i<theString.length(); i++) {
        theString[i]=tolower(theString[i]);
    }
}

/********************************************
 *          readPoliticalFiles              *
 * Reads politial files starting at first   *
 * parameter and ending at the second       *
 *******************************************/
void readPoliticalFiles(int beginning, int end, SeparateChainTable& table){
    string fileName;
    ifstream textFile;
    string word;
    for (int i=beginning; i<=end; i++) {                //read half the files in talks.politics.miscalleneous folder
        fileName = to_string(i);
        textFile.open(fileName);
        if (textFile.is_open()) {
            while (!textFile.eof()) {
                textFile >> word;
                cleanWord(word);
                table.addItem(word);
            }
            textFile.close();
        }
    }
}

/********************************************
 *          readReligionFiles               *
 * Reads regligion files starting at first  *
 * parameter and ending at the second       *
 ******************************************/
void readReligionFiles(int beginning, int end, SeparateChainTable& table){
    string fileName;
    ifstream textFile;
    string word;
    for (int i=beginning; i<=end; i++) {                //read half the files in talks.politics.miscalleneous folder
        fileName = to_string(i);
        textFile.open(fileName);
        if (textFile.is_open()) {
            while (!textFile.eof()) {
                textFile >> word;
                cleanWord(word);
                table.addItem(word);
            }
            textFile.close();
        }
    }
}

/************************************************
 *          classifyFiles()                     *
 * reads the files specified and classifies     *
 * them as either Political or Religious.       *
 ************************************************/
int classifyFiles(int beginning,int end , double thresh, SeparateChainTable &trainingSet){
    /*Variable declarations*/
    string fileName;
    ifstream textFile;
    string word;
    bool containsDisc = false;
    double PFvote =0;               //keep track of political file votes
    double RFvote =0;               //keep track of relgious file votes
    int correctCount = 0;
    bool fileOpened = false;
    /*End*/
    
    for (int i =beginning; i<end ; i++) {               //process a file
        PFvote = 0; RFvote = 0;
        containsDisc = false;
        fileOpened = false;
        fileName = to_string(i);
        textFile.open(fileName);
        if (textFile.is_open()) {
            fileOpened = true;
            while (!textFile.eof()) {                   //check file for discriminators
                textFile >> word;
                cleanWord(word);
                if (isDiscriminator(word, thresh, trainingSet)) {               //check if word is a discriminator
                    containsDisc = true;
                    if (trainingSet.getPFcorrelationFactor(word) >= thresh) {
                        PFvote += trainingSet.getPFcorrelationFactor(word);     //vote for PF
                    }else{
                        RFvote += trainingSet.getRFcorrelationFactor(word);     //vote for RF
                    }
                }
            }
            textFile.close();           //close file
            if (!containsDisc && !fileOpened) {                            //file contained no discriminators, toss coin to classify
                if (coinToss() == 1) {
                    cout << "File " << i << " is Political" ;
                    displayCorrectness(i, 1, correctCount);
                }else{
                    cout << "File " << i << " is Religious" ;
                    displayCorrectness(i, 2, correctCount);
                }
            }else if (fileOpened){                                          //file contained discriminators
                if(PFvote > RFvote){
                    cout << "File " << i << " is Politial" ;
                    displayCorrectness(i, 1, correctCount);
                }else if (PFvote < RFvote){
                cout << "File " << i << " is Religious" ;
                displayCorrectness(i, 2, correctCount);
                }
            }
        }
    }
    cout << endl;
    //cout << "Number of files classified correctly: " << correctCount << endl;
    return correctCount;
}

/********************************************
 *          isDiscriminator                 *
 *  checks if word is in training set and   *
 * is a discriminator. Helps classifyFiiles *
 ********************************************/
bool isDiscriminator(string theWord, double theThresh, SeparateChainTable &set){
    bool discriminator = false;
    
    if (set.find(theWord)) {
        if (set.getPFcorrelationFactor(theWord) >= theThresh || set.getRFcorrelationFactor(theWord) >= theThresh) {
            discriminator = true;
        }
    }
    
    return discriminator;
}

/*********************
 *  coinToss()       *
 ********************/
int coinToss(){
    int tossResult;
    tossResult = (rand() % 2) + 1;
    
    return tossResult;
}

void displayCorrectness(int fileNumber, int classification, int &corrCount){
    //classification: 1 = political, 2 == religious
    bool flag = false;
    if (classification==1 && (178605 <= fileNumber) && (fileNumber <= 179116)) {             //file got classified correctly
        cout << " -CORRECT" << endl;
        corrCount++;
        flag = true;
    }
    else if (classification==2 && (83877 <= fileNumber) && (fileNumber <= 84570)) {
        cout << " -CORRECT" << endl;
        corrCount++;
        flag = true;
    }
    
    if (!flag) {
        cout << "-INCORRECT" << endl;
    }
}

