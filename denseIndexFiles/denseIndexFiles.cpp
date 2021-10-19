#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;
int numberValues = 90;
int numberInBlock = 10;

void inputKey() {
	cout << "Input the data you want to add " << endl;
	string data;
	cin >> data;
}
void deleteKey() {
	cout << "Input the key you want to delete" << endl;
	string data;
	cin >> data;

}
void findKey() {
	cout << "Input the key you want to find" << endl;
	string data;
	cin >> data;

}
void printFiles() {
	ifstream inFile1("index.txt");
	ifstream inFile2("main.txt");
	ifstream inFile3("overflow.txt");
	string temp;
	cout << "-----------------------Main area:-----------------------" << endl;
	while (inFile1 >> temp) {
		cout << temp << endl;
	}
	inFile1.close();
	cout << "-----------------------Index area:-----------------------" << endl;
	while (inFile2 >> temp) {
		cout << temp << endl;
	}
	inFile2.close();
	cout << "-----------------------Overflow area:-----------------------" << endl;
	while (inFile3 >> temp) {
		cout << temp << endl;
	}
	inFile3.close();

}
void createMainFile(int number) {
	ofstream outFile("main.txt");
	for (int i = 0; i < number; i++) {
		string value = "";
		for (int j = 0; j < 10; j++) {
			value += char(65 + rand() % 25);
		}
		outFile << i << "," << value << "," << 1 << endl;
	}
	outFile.close();
}
void indexFile() {
	ofstream clearFile("index.txt");
	clearFile.close();
	ifstream inFile("main.txt");
	string temp;
	int number = 0;
	vector<vector<string>> blocks(10);
	vector<string> overflow;
	while (inFile >> temp) {
		int posComa = temp.find(',');
		int key = stoi(temp.substr(0,posComa));
		temp.erase(0, posComa+1);
		posComa = temp.find(',');
		string value = temp.substr(0, posComa);
		temp.erase(0, posComa + 1);
		bool isNotDeleted = stoi(temp);
		string tempNameFile = to_string(key) + ".txt";
		int blockToPaste = number % 10;
		if (blocks[blockToPaste].size() < numberInBlock) {
			blocks[blockToPaste].push_back(to_string(key) + ',' + to_string(number));
		}
		else {
			overflow.push_back(to_string(key) + ',' + to_string(number));
		}
		number++;
	}
	inFile.close();
	ofstream outFile("index.txt", ofstream::app);
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < blocks[i].size(); j++) {
			outFile << blocks[i][j] << endl;
		}
		outFile << "-" << endl;
	}
	outFile.close();
	ofstream outFileOver("overflow.txt");
	for (int i = 0; i < overflow.size();i++) {
		outFileOver << overflow[i] << endl;
	}
	outFileOver.close();
}
int main()
{
	createMainFile(numberValues);
	indexFile();
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
	}
	

}

