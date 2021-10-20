#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
#include "dataBase.h"
using namespace std;



//void deleteKey() {
//	cout << "Input the key you want to delete" << endl;
//	string data;
//	cin >> data;
//
//}
//void findKey() {
//	cout << "Input the key you want to find" << endl;
//	string data;
//	cin >> data;
//
//}
//void printFiles() {
//	ifstream inFile1("main.txt");
//	ifstream inFile2("index.txt");
//	ifstream inFile3("overflow.txt");
//	string temp;
//	cout << "-----------------------Main area:-----------------------" << endl;
//	while (inFile1 >> temp) {
//		currentElements++;
//		cout << temp << endl;
//	}
//	inFile1.close();
//	cout << "-----------------------Index area:-----------------------" << endl;
//	while (inFile2 >> temp) {
//		cout << temp << endl;
//	}
//	inFile2.close();
//	cout << "-----------------------Overflow area:-----------------------" << endl;
//	while (inFile3 >> temp) {
//		cout << temp << endl;
//	}
//	inFile3.close();
//
//}

int main()
{
	dataBase db;
	/*
	printFiles();
	int res;
	int outRes = 1;
	while (outRes != 0) {
		cout << "Whad do you want to do? \n 1 - input key\n 2 - delete key \n 3 - find key" << endl;
		cin >> res;
		switch (res) {
		case 1:
			inputKey();
			break;
		case 2:
			deleteKey();
			break;
		case 3:
			findKey();
			break;
		default:
			cout << "Unknown" << endl;
		}
		cout << "Do you want to continue? \n 1 - yes \n 0 - no" << endl;
		cin >> outRes;
	}*/
}

