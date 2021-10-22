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

void dataBase::deleteKey() {
	cout << "Input the key you want to delete" << endl;
	int data;
	cin >> data;
	if (data < 0 || data >= currentElements) {
		cout << "Unfortunately, this database do not have this element";
	}
	else {
		vector<string> blockToDelete = index[data % 10];
		 
	}
}
int Sharr(vector<string> blockToFind, int data) {
	int k = (int)logbase(blockToFind.size(), 2);
	int i = pow(2, k);
	if (data < getKey(blockToFind[i])) {
		int iterator = 1;
		int b = pow(2, k - iterator);
		while (data != getKey(blockToFind[i])) {
			iterator++;
			if (data < getKey(blockToFind[i])) {
				i = i - ((int)(b / 2) + 1);
				b = pow(2, k - iterator);
			}
			else if (data > getKey(blockToFind[i])) {
				i += (int)(b / 2) + 1;
				b = pow(2, k - iterator);
			}
			if (iterator >= blockToFind.size()) {
				return -1;
				break;
			}
		}
		if (data == getKey(blockToFind[i])) {
			return i;
		}
	}
	else if (data == getKey(blockToFind[i])) {
		return i;
	}
	else {
		if (blockToFind.size() > pow(2, k)) {
			int l = (int)logbase(blockToFind.size() - pow(2, k) + 1, 2);
			i = blockToFind.size() + l - pow(2, l);
			int iterator = 1;
			int b = pow(2, l - iterator);
			while (b != 0) {
				iterator++;
				if (data > getKey(blockToFind[i])) {
					i += ((int)(b / 2) + 1);
					b = pow(2, l - iterator);
				}
				else if (data < getKey(blockToFind[i])) {
					i -= ((int)(b / 2) + 1);
					b = pow(2, l - iterator);
				}
				if (data == getKey(blockToFind[i])) {
					return i;
					break;
				}
			}
		}
	}
}
void dataBase::findKey() {
	cout << "Input the key you want to find" << endl;
	int data;
	cin >> data;
	if (data < 0 || data >= currentElements) {
		cout << "Unfortunately, this database do not have this element" << endl;;
	}
	else {
		vector<string> blockToFind = index[data % 10];
		int indexInBlock = Sharr(blockToFind, data);
		if( indexInBlock!= -1){
			cout << "We have found element, the position is: " << endl << indexInBlock << endl;
		}
	}
}
void dataBase::redoKey()
{
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
