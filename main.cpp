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

int main()
{
	MatrixCypher matrixCypher;
	int option;

	cout << "What is the task: " << endl;
	cout << "  1: Encode a message." << endl;
	cout << "  2: Decode a message." << endl;
	cin >> option;

	if(option == 1)
		matrixCypher.incodeMessage("plain.txt", "cypher.txt");
	else if(option == 2)
		matrixCypher.decodeMessage("cypher.txt", "plain.txt");
	else
		cout << "What???" << endl << endl;

	return 0;
}
