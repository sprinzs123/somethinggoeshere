#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream> 
using namespace std;

// #### New Classes ####
class CheckMetaData {
public:
	string server;
	string manager;
	string time;
	string phone;
	string date;
	int table;
	int guests;
	// migh not need it since everythin is public scope
	void setServer(string server) {
		this->server = server;
	}
	void setManager(string manager) {
		this->manager = manager;
	}
	void setTime(string time) {
		this->time = time;
	}
	void setPhone(string phone) {
		this->phone = phone;
	}
	void setDate(string date) {
		this->date = date;
	}
	void setTable(int table) {
		this->table = table;
	}
	void setGuests(int guests) {
		this->guests = guests;
	}
};

class Payment {
public:
	string Type;
	float amount;
	string id;
};

class FoodItem {
public:
	string name;
	float price;
	int count;
	string code;

	void printString() {
		cout << "Name: " << name << " price: " << price << " count: " << count << endl;
	}
};

class FullCheck {
	int pk;
	CheckMetaData metadata;
	Payment payment[20];
};

// ### New Functions ###
string* substringArr(string, char, int);
FoodItem selectFoodLine(string, string, int);

// splitting string into array. Similar to .substring() in python, C++ doesn't has is... :(
string* substringArr(string fullString, char delimeter, int delimeterCount) {
	// getting all indexes where delimeter would be
	int indexi[20];
	string* strBrokenUp = new string[10];
	int arrIndex = 0;
	for (int i = 0; i < fullString.length(); i++) {
		if (fullString[i] == delimeter) {
			indexi[arrIndex] = i;
			arrIndex++;
		}
	}
	//cout <<"Delimiters found: " << arrIndex << endl;
	if (arrIndex != delimeterCount) {
		//cout << "Can't parse" << endl;
		strBrokenUp[0] = "-1";
		return strBrokenUp;
	}

	//making array of substring that is going to return
	//cout << "making substrings from: " << fullString << endl;
	int insertIndex = 0;  // index at where going to inset string into array
	int prevDelimiter = 0;
	for (int i = 0; i < delimeterCount+1; i++) {
		int temp = indexi[i];
		//cout << "start: " << prevDelimiter << " end: " << temp << endl;
		string substring =  fullString.substr(prevDelimiter, temp - prevDelimiter); // getting substring	
		//cout << "new substrung: " << substring << endl;
		strBrokenUp[insertIndex] = substring;
		insertIndex++;
		prevDelimiter = temp + 1;  // reseting start of string
	}
	return strBrokenUp;
}

// pases lines from food file correctly at matches to needed id
FoodItem selectFoodLine(string chechId, string line, int delimeterCount) {
	FoodItem foodItem;
	if (line.length() > 10 && line.substr(0, 5) == chechId) {
		string id = line.substr(0, 5);
		string* arrItems = substringArr(line, '-', delimeterCount);
		if (arrItems[0] == "-1") {
			cout << "invalid object" << endl;
		
		}
		else {
			cout << "valid object " << endl;
			foodItem.name = arrItems[4];
			foodItem.price = stof(arrItems[2]);
			foodItem.count = stoi(arrItems[3]);
			return foodItem;
		}		
	}	
}







int main()
{
	string contents;
	ifstream file;
	file.open("C:\\Users\\cooke\\Desktop\\school\\p_data.txt", ios::in);
	if (file.fail()) {
		cout << "WROOOOOONDFFF";
	}
	//getValue("tete", file);



	stringstream strStream;
	strStream << file.rdbuf(); //read the file
	string strText = strStream.str(); //str holds the content of the file
	//cout << "File content:" << strText << endl;
	string test = "one@two@";

	string* arrString;
	//arrString = substringArr(test, "@");
	//cout << arrString[0] << endl;


	ifstream foodFile;
	string line;
	foodFile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\food.txt", ios::in);
	if (foodFile.fail()) {
		cout << "Wrong file can't open food \n";
	} else {
		while (getline(foodFile, line)) {			
			FoodItem foodItem = selectFoodLine("64337", line, 4);
			foodItem.printString();
			
		}
	}
	 

	//ifstream metadataFile;
	//string line2;
	//metadataFile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\metadata.txt", ios::in);
	//if (metadataFile.fail()) {
	//	cout << "Wrong file can't open metadata \n";
	//} else {		
	//	while (getline(metadataFile, line2)) {
	//		string* tempMeta = substringArr(line2, "@");
	//		cout << "Key: " << tempMeta[0] << " Value: " << tempMeta[1] << endl;			
	//	}
	//	metadataFile.close();
	//}
	


	file.close();

	return 0;

}
