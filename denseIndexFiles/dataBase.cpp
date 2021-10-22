#include "dataBase.h"

//-----------------------------GET INFO FROM FILES-----------------------------------------------

void dataBase::getIndex()
{
	vector<vector<string>> vec(blocks);
	ifstream inFile("index.txt");
	string temp;
	int block = 0;
	while (inFile >> temp) {
		if (temp == "-") {
			block++;
		}
		else {
			vec[block].push_back(temp);
		}
	}
	inFile.close();
	index = vec;
}

void dataBase::getMain()
{
	vector<string> vec;
	ifstream inFile("main.txt");
	string temp;
	while (inFile >> temp) {
		vec.push_back(temp);
	}
	inFile.close();
	main = vec;
}

void dataBase::getOverflow()
{
	vector<string> vec;
	ifstream inFile("overflow.txt");
	string temp;
	while (inFile >> temp) {
		vec.push_back(temp);
	}
	inFile.close();
	overflow = vec;
}

//-----------------------------INITIALIZE DB-----------------------------------------------

void dataBase::createMainFile()
{
	srand(time(0));
	ofstream outFile("main.txt");
	for (int i = 0; i < numberValues; i++) {
		string value = "";
		for (int j = 0; j < 10; j++) {
			value += char(65 + rand() % 25);
		}
		outFile << i << "," << value << "," << 1 << endl;
	}
	outFile.close();
}

void dataBase::indexFile()
{
	string temp;
	vector<vector<string>> tempIndex(blocks);
	for(int i =0;i<main.size();i++){
		temp = main[i];
		int posComa = temp.find(',');
		int key = stoi(temp.substr(0, posComa));
		temp.erase(0, posComa + 1);
		posComa = temp.find(',');
		string value = temp.substr(0, posComa);
		temp.erase(0, posComa + 1);
		bool isNotDeleted = stoi(temp);
		int blockToPaste = key % 10;
		if (tempIndex[blockToPaste].size() < numberInBlock) {
			tempIndex[blockToPaste].push_back(to_string(key) + ',' + to_string(i));
		}
		else {
			overflow.push_back(to_string(key) + ',' + to_string(i));
		}
	}
	index = tempIndex;
	indexUpdate();
	overflowUpdate();
}
//-----------------------------UPDATES-----------------------------------------------

void dataBase::mainUpdate() {
	ofstream mainFile("main.txt");
	for (int i = 0; i < main.size(); i++) {
		mainFile << main[i] << endl;
	}
	mainFile.close();
}
void dataBase::indexUpdate()
{
	ofstream outFile("index.txt");
	for (int i = 0; i < index.size(); i++) {
		for (int j = 0; j < index[i].size(); j++) {
			outFile << index[i][j] << endl;
		}
		outFile << "-" << endl;
	}
	outFile.close();
}
void dataBase::overflowUpdate()
{
	ofstream outFileOver("overflow.txt");
	for (int i = 0; i < overflow.size(); i++) {
		outFileOver << overflow[i] << endl;
	}
	outFileOver.close();
}

//-----------------------------MAIN ACTIONS WITH KEYS-----------------------------------------------

double logbase(double a, double base)
{
	return log(a) / log(base);
}
int getKey(string temp) {
	int comaPos = temp.find(",");
	int key = stoi(temp.substr(0, comaPos + 1));
	return key;
}
int getMainIndex(string temp) {
	int comaPos = temp.find(",");
	int index = stoi(temp.substr(comaPos + 1, temp.length() - comaPos));
	return index;
}

void dataBase::inputKey() {
	cout << "Input the data you want to add " << endl;
	string data;
	cin >> data;
	if (index[currentElements % 10].size() < numberInBlock) {
		index[currentElements % 10].push_back(to_string(currentElements) + ',' + to_string(main.size()));
		indexUpdate();
	}
	else {
		overflow.push_back(to_string(currentElements) + ',' + to_string(main.size()));
		ofstream fileOverflow("overflow.txt", ofstream::app);
		fileOverflow << to_string(currentElements) + ',' + to_string(main.size()) << endl;
		fileOverflow.close();
	}
	
	ofstream outFile("main.txt", ofstream::app);
	outFile << to_string(currentElements) << "," << data << "," << "1" << endl;
	outFile.close();
	main.push_back(to_string(currentElements) + "," + data + "," + "1");
	currentElements++;
}

int Sharr(vector<string> blockToFind, int data, int& comparison) {
	if (blockToFind.size() == 0) {
		return -1;
	}
	else {
		int N = blockToFind.size();
		int k = (int)logbase(N, 2);
		int i = pow(2, k) - 1;
		if (data == getKey(blockToFind[i])) {
			return i;
		}
		else if (data < getKey(blockToFind[i])) {
			int b = pow(2, k - 1);
			comparison++;
			do {
				comparison++;
				if (data < getKey(blockToFind[i])) {
					i -= ((int)(b / 2) + 1);
					b = b / 2;
				}
				else if (data > getKey(blockToFind[i])) {
					i += ((int)(b / 2) + 1);
					b = b / 2;
				}
				if (i >= N || i < 0 || comparison > N + 1)return-1;
			} while (data != getKey(blockToFind[i]));
			return i;
		}
		else if (data > getKey(blockToFind[i])) {
			if (N <= pow(2, k))return-1;
			int l = (int)logbase(N - pow(2, k) + 1, 2);
			i = N + 1 - pow(2, l) - 1;
			int b = pow(2, l - 1);
			comparison++;
			do {
				comparison++;
				if (data < getKey(blockToFind[i])) {
					i -= ((int)(b / 2) + 1);
					b = b / 2;
				}
				else if (data > getKey(blockToFind[i])) {
					i += ((int)(b / 2) + 1);
					b = b / 2;
				}
				if (i >= N || i < 0 || comparison > N + 1)return-1;
			} while (data != getKey(blockToFind[i]));
			return i;
		}
	}
}
void dataBase::deleteKey() {
	cout << "Input the key you want to delete" << endl;
	int data;
	cin >> data;
	if (data < 0) {
		cout << "Unfortunately, this database do not have this element" << endl;;
	}
	else {
		vector<string> blockToFind = index[data % 10];
		int indComparison = 0;
		int overComparison = 0;
		int indexInBlock = Sharr(blockToFind, data, indComparison);
		if (indexInBlock == -1) {
			int indexInBlock = Sharr(overflow, data, overComparison);
			if (indexInBlock == -1) {
				cout << "Probably the element was deleted earlier(" << endl;
			}
			else {
				string temp = main[getMainIndex(overflow[indexInBlock])];
				temp[temp.length() - 1] = '0';
				main[getMainIndex(overflow[indexInBlock])] = temp;
				mainUpdate();
				vector<string> newOverflow;
				for (int i = 0; i < overflow.size(); i++) {
					if (getKey(overflow[i]) != data) {
						newOverflow.push_back(overflow[i]);
					}
				}
				overflow = newOverflow;
				overflowUpdate();
				cout << "We have deleted the element in overflow area " << endl;
			}
		}
		else {
			vector<vector<string>> newIndex(blocks);
			for (int i = 0; i < index.size(); i++) {
				for (int j = 0; j < index[i].size(); j++) {
					if (getKey(index[i][j]) != data) {
						newIndex[i].push_back(index[i][j]);
					}
				}
			}
			index = newIndex;
			indexUpdate();
			string temp = main[getMainIndex(blockToFind[indexInBlock])];
			temp[temp.length() - 1] = '0';
			main[getMainIndex(blockToFind[indexInBlock])] = temp;
			mainUpdate();
			cout << "We have deleted the element in index area" << endl;
		}

	}
}
void dataBase::findKey() {
	cout << "Input the key you want to find" << endl;
	int data;
	cin >> data;
	if (data < 0) {
		cout << "Unfortunately, this database do not have this element" << endl;;
	}
	else {
		vector<string> blockToFind = index[data % 10];
		int indComparison = 0;
		int overComparison = 0;
		int indexInBlock = Sharr(blockToFind, data, indComparison);
		if( indexInBlock == -1){
			int indexInBlock = Sharr(overflow, data, overComparison);
			if (indexInBlock == -1) {
				cout << "Probably the element was deleted(" << endl;
			}
			else {
				cout << "We have found the element in overflow area, the data is: \n" << main[getMainIndex(overflow[indexInBlock])] << endl;
				cout << "The number of comparisons: " << indComparison + overComparison << endl;
			}
		}
		else {
			cout << "We have found the element in index area, the data is: \n" << main[getMainIndex(blockToFind[indexInBlock])] << endl;
			cout << "The number of comparisons: " << indComparison + overComparison << endl;
		}
	}
}
void dataBase::redoKey()
{
	cout << "Input the key you want to redo" << endl;
	int key;
	cin >> key;
	cout << "Input the data you want to past" << endl;
	string data = "";
	cin >> data;
	if (key < 0) {
		cout << "Unfortunately, this database do not have this element" << endl;;
	}
	else {
		vector<string> blockToFind = index[key % 10];
		int indComparison = 0;
		int overComparison = 0;
		int indexInBlock = Sharr(blockToFind, key, indComparison);
		if (indexInBlock == -1) {
			int indexInBlock = Sharr(overflow, key, overComparison);
			if (indexInBlock == -1) {
				cout << "Probably the element was deleted(" << endl;
			}
			else {
				string newStr = to_string(getMainIndex(overflow[indexInBlock])) +"," + data + ","  +"1";
				main[getMainIndex(overflow[indexInBlock])] = newStr;
				mainUpdate();
				cout << "We have changed the data of element" << endl;
			}
		}
		else {
			string newStr = to_string(getMainIndex(blockToFind[indexInBlock])) + "," + data + "," + "1";
			main[getMainIndex(blockToFind[indexInBlock])] = newStr;
			mainUpdate();
			cout << "We have changed the data of element" << endl;
		}
	}
	
}

void dataBase::UI()
{
	int res;
	int outRes = 1;
	while (outRes != 0) {
		cout << "Whad do you want to do? \n 1 - input key\n 2 - delete key \n 3 - find key \n 4 - redo key" << endl;
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
		case 4:
			redoKey();
			break;
		default:
			cout << "Unknown" << endl;
		}
		cout << "Do you want to continue? \n 1 - yes \n 0 - no" << endl;
		cin >> outRes;
	}
}
