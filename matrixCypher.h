// File Name: matrixCypher.h
//
// This uses the matrix:
//
//  E = | 1   4|
//      |-1  -3|
//
// to encode and decode a message.
//
// Author: Mr. Dagler

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class MatrixCypher {
public:
	MatrixCypher();
	void incodeMessage(string messageFileName, string cypherFileName);
	void decodeMessage(string cypherFileName, string messageFileName);

private:
	void loadCharMap();
	int charToInt(char ch);

	static const int NUM_OF_CHARS = 93;

	vector<int> messageRow1;
	vector<int> messageRow2;
	vector<int> cypherRow1;
	vector<int> cypherRow2;

	char chars[NUM_OF_CHARS];
	int charVals[NUM_OF_CHARS];
};

MatrixCypher::MatrixCypher() {
	loadCharMap();
}

void MatrixCypher::incodeMessage(string messageFileName, string cypherFileName){
	int totalNumOfChars=0, numOfCols, n=1;
	vector<string> words;
	string word;

	ifstream inFile(messageFileName.c_str());
	if(!inFile.is_open())
	{
		cerr << "I can not find \"" << messageFileName << "\"!!" << endl;
		exit(1);
	}

	while(inFile >> word){
		words.push_back(word);
		totalNumOfChars += word.size();
	}
	//Counting the white spaces
	totalNumOfChars += words.size()-1;

	if(totalNumOfChars%2==0)
		numOfCols = totalNumOfChars/2;
	else
		numOfCols = totalNumOfChars/2+1;

	for(int i=0;i<words.size()-1;i++){
		for(int j=0; j<words.at(i).size(); j++){
			if(n<numOfCols)
				messageRow1.push_back(charToInt(words.at(i)[j]));
			else
				messageRow2.push_back(charToInt(words.at(i)[j]));
			n++;
		}
		//Adding a space between words.
		n<numOfCols ? messageRow1.push_back(0) : messageRow2.push_back(0);

		cout << words.at(i) << "_";
	}
	//Adding the last word.
	for(int i=0; i<words.at(words.size()-1).size(); i++)
		messageRow2.push_back(charToInt(words.at(words.size()-1)[i]));

	cout << words.at(words.size()-1) << endl << endl;

	cout << totalNumOfChars << ": " << numOfCols << endl << endl;

	for(int i=0; i<messageRow1.size(); i++)
		cout << messageRow1.at(i) << " ";
	cout << endl;
	for(int i=0; i<messageRow2.size(); i++)
		cout << messageRow2.at(i) << " ";
	cout << endl << endl;

}


void MatrixCypher::decodeMessage(string cypherFileName, string messageFileName){

}

void MatrixCypher::loadCharMap() {
	ifstream charFile("char_map.txt");
	if(!charFile.is_open())
	{
		cerr << "Error: I can not find 'char_map.txt'." << endl;
		exit(1);
	}

	for(int i=0; i<NUM_OF_CHARS; i++)
		charFile >> chars[i] >> charVals[i];
}

int MatrixCypher::charToInt(char ch){
	for(int i=0; i<NUM_OF_CHARS; i++)
		if(ch == chars[i])
			return charVals[i];

	return 0;
}
