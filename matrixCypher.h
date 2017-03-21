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
	int charToInt(char ch);
	char intToChar(int n);

	vector<int> messageRow1;
	vector<int> messageRow2;
	vector<int> cypherRow1;
	vector<int> cypherRow2;

	string chars;
};

MatrixCypher::MatrixCypher() {
	chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,./?;:[{]}|~!@#$%^&*()-_+=\n\t\\\'\"";
}

void MatrixCypher::incodeMessage(string messageFileName, string cypherFileName) {
	int numOfCols, n=1, currentNum;
	vector<char> message;
	char ch;

	//////////////////////////////////////////////////////////////////////////////
	//                        Reading in the File.                              //
	//////////////////////////////////////////////////////////////////////////////
	ifstream inFile(messageFileName.c_str());
	if(!inFile.is_open()) {
		cerr << "I can not find \"" << messageFileName << "\"!!" << endl;
		exit(1);
	}

	while(inFile.get(ch)) {
		message.push_back(ch);
	}

	inFile.close();

	if(message.size()%2==0)
		numOfCols = message.size()/2;
	else
		numOfCols = message.size()/2+1;

	//////////////////////////////////////////////////////////////////////////////
	//                   Converting the Chars to Integers.                      //
	//////////////////////////////////////////////////////////////////////////////

	for(int i=0; i<message.size(); i++) {
		if(n<=numOfCols)
			messageRow1.push_back(charToInt(message.at(i)));
		else
			messageRow2.push_back(charToInt(message.at(i)));
		n++;
	}

	//Adding a space if then is an odd number of chars.
	if(message.size()%2!=0)
		messageRow2.push_back(0);

	//////////////////////////////////////////////////////////////////////////////
	//                        Incoding the Message                              //
	//////////////////////////////////////////////////////////////////////////////

	for(int i=0; i<numOfCols; i++) {
		cypherRow1.push_back(1*messageRow1.at(i)+4*messageRow2.at(i));
		cypherRow2.push_back(-1*messageRow1.at(i)-3*messageRow2.at(i));
	}

	//////////////////////////////////////////////////////////////////////////////
	//                Writting the incoded message to a file                    //
	//////////////////////////////////////////////////////////////////////////////

	ofstream outFile(cypherFileName.c_str());
	if(!outFile.is_open()) {
		cerr << "I can not create \"" << cypherFileName << "\"!!" << endl;
		exit(1);
	}

	currentNum = 1;
	for(int i=0; i<numOfCols; i++) {
		outFile << cypherRow1.at(i);
		currentNum%10==0 ? outFile<<'\n' : outFile<<'\t';
		currentNum++;
	}
	for(int i=0; i<numOfCols-1; i++) {
		outFile << cypherRow2.at(i);
		currentNum%10==0 ? outFile<<'\n' : outFile<<'\t';
		currentNum++;
	}
	outFile << cypherRow2.at(numOfCols-1) << endl;

	cout << endl << endl;
	cout << "Incoded Message was written to \"" <<  cypherFileName << "\".";
	cout << endl << endl;

	outFile.close();
}

void MatrixCypher::decodeMessage(string cypherFileName, string messageFileName) {
	int totalNumOfChars=0, numOfCols, n=1, currentNum;
	vector<int> nums;

	//////////////////////////////////////////////////////////////////////////////
	//                        Reading in the File.                              //
	//////////////////////////////////////////////////////////////////////////////
	ifstream inFile(cypherFileName.c_str());
	if(!inFile.is_open()) {
		cerr << "I can not find \"" << cypherFileName << "\"!!" << endl;
		exit(1);
	}

	while(inFile >> currentNum) {
		nums.push_back(currentNum);
		totalNumOfChars ++;
	}

	inFile.close();

	if(totalNumOfChars%2==0)
		numOfCols = totalNumOfChars/2;
	else
		numOfCols = totalNumOfChars/2+1;

	//////////////////////////////////////////////////////////////////////////////
	//                      Adding the numbers to the matrix                    //
	//////////////////////////////////////////////////////////////////////////////

	for(int i=0; i<numOfCols; i++)
		cypherRow1.push_back(nums.at(i));
	for(int i=numOfCols; i<2*numOfCols; i++)
		cypherRow2.push_back(nums.at(i));

	//////////////////////////////////////////////////////////////////////////////
	//                        Decoding the Message                              //
	//////////////////////////////////////////////////////////////////////////////

	for(int i=0; i<numOfCols; i++) {
		messageRow1.push_back(-3*cypherRow1.at(i)-4*cypherRow2.at(i));
		messageRow2.push_back(1*cypherRow1.at(i)+1*cypherRow2.at(i));
	}

	//////////////////////////////////////////////////////////////////////////////
	//                Writting the decoded message to a file                    //
	//////////////////////////////////////////////////////////////////////////////

		ofstream outFile(messageFileName.c_str());
		if(!outFile.is_open()) {
			cerr << "I can not create \"" << messageFileName << "\"!!" << endl;
			exit(1);
		}

		for(int i=0; i<numOfCols; i++)
			outFile << intToChar(messageRow1.at(i));
		for(int i=0; i<numOfCols-1; i++)
			outFile << intToChar(messageRow2.at(i));

		if(messageRow2.at(numOfCols-1) != 0)
			outFile << intToChar(messageRow2.at(numOfCols-1));

		cout << endl << endl;
		cout << "Incoded Message was written to \"" <<  messageFileName << "\".";
		cout << endl << endl;

		outFile.close();
}

int MatrixCypher::charToInt(char ch) {
	for(int i=0; i<chars.length(); i++)
		if(ch == chars[i])
			return i;

	return 0;
}

char MatrixCypher::intToChar(int n) {
	for(int i=1; i<chars.length(); i++)
		if(n == i)
			return chars[i];

	return ' ';
}
