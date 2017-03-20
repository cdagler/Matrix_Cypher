// File Name: main.cpp
//
// This uses the matrix:
//
//  E = | 1   4|
//      |-1  -3|
//
// to encode and decode a message.
//
// Author: Mr. Dagler

#include "matrixCypher.h"

int main() {
	MatrixCypher matrixCypher;
	int option;
	string plainFileName, cyphterFileName;

	cout << "What is the task: " << endl;
	cout << "  1: Encode a message." << endl;
	cout << "  2: Decode a message." << endl;
	cin >> option;

	if(option == 1){
		cout << "Enter the name of the file that has the message to incode:" << endl;
		cin >> plainFileName;
		cout << "Enter the name of the file that will hold the encrypted message:" << endl;
		cin >> cyphterFileName;

		matrixCypher.incodeMessage(plainFileName, cyphterFileName);
	}
	else if(option == 2){
		cout << "Enter the name of the file that has the encrypted message:" << endl;
		cin >> cyphterFileName;
		cout << "Enter the name of the file that will hold the decrypted message:" << endl;
		cin >> plainFileName;

		matrixCypher.decodeMessage(cyphterFileName, plainFileName);
	}
	else
		cout << "What???" << endl << endl;

	return 0;
}
