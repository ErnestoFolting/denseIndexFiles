#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

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
	ifstream inFile("main.txt");
	string temp;
	int number = 0;
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
		ofstream outFile(tempNameFile);
		outFile << key << "," << number << endl;
		number++;
	}
	inFile.close();
}
int main()
{
	srand(time(NULL));
	createMainFile(10);
	indexFile();
}

