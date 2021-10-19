#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;
int numberValues = 11;
int numberInBlock = 1;
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
		cout << temp << endl;
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
		outFile << endl;
	}
	outFile.close();
	ofstream outFileOver("overflow.txt", ofstream::app);
	for (int i = 0; i < overflow.size();i++) {
		outFileOver << overflow[i] << endl;
	}
	outFileOver.close();
}
int main()
{
	srand(time(NULL));
	createMainFile(numberValues);
	indexFile();
}

