#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;

struct dataBase
{
	vector<vector<string>> index;
	vector<string> overflow;
	vector<string> main;
	int numberValues = 90;
	int numberInBlock = 10;
	int blocks = 10;
	int currentElements = 0;
	void getIndex();
	void getMain();
	void getOverflow();
	void createMainFile();
	void indexFile();
	void inputKey();
	void deleteKey();
	void findKey();
	void redoKey();
	void mainUpdate();
	void indexUpdate();
	void overflowUpdate();
	void UI();
	dataBase() {
		getIndex();
		getMain();
		getOverflow();
		currentElements = main.size();
		UI();
	}
	dataBase(int values) {
		numberValues = values;
		createMainFile();
		getMain();
		currentElements = main.size();
		indexFile();
		getOverflow();
		getIndex();
		UI();
	}
};

