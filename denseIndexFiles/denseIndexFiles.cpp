#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

void createMainFile(int number) {
	ofstream outFile("main.csv");
	for (int i = 0; i < number; i++) {
		string value = "";
		for (int j = 0; j < 10; j++) {
			cout << 25 + rand() % 65 << endl;
			value += char(65 + rand() % 25);
		}
		outFile << i << "," << value << 0 << endl;
	}
	outFile.close();
}

int main()
{
	srand(time(NULL));
	createMainFile(10);
}

