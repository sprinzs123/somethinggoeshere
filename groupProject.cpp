#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream> 
#include <windows.data.json.h>
using namespace std;
string* substringArr(string, string);
void getValue(string, ofstream);

//void getValue(string search, ofstream file) {
//	string line;
//	if (file.is_open()) {
//		while (getline(file, line)) {
//			cout << line << "\n";
//		}
//	}
//	file.close();
//}


// splitting string into array. Similar to .substring() in python, C++ doesn't has is... :(
string* substringArr(string fullString, string delimeter) {
	// getting all indexes where delimeter would be
	int indexi[20];
	string* strBrokenUp = new string[10];
	int arrIndex = 0;
	for (int i = 0; i < fullString.length(); i++) {
		if (fullString[i] == '@') {
			indexi[arrIndex] = i;
			arrIndex++;
		}
	}
	cout << arrIndex;
	//cout << "making substrings from: " << fullString << endl;
	// making array of substring that is going to return
	int insertIndex = 0;  // index at where going to inset string into array
	int prevDelimiter = 0;
	for (int i = 0; i < 3; i++) {
		int temp = indexi[i];
		//cout << "start: " << prevDelimiter << " end: " << temp << endl;
		string substring =  fullString.substr(prevDelimiter, temp - prevDelimiter); // getting substring
		cout << substring << endl;
		strBrokenUp[insertIndex] = substring;
		insertIndex++;
		prevDelimiter = temp + 1;  // reseting start of string
	}
	return strBrokenUp;
}


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

class OneFood {
public:
	string name;
	float price;
	int count;	
};

class FullCheck {
	int pk;
	CheckMetaData metadata;
	OneFood foodItems[20];
	Payment payment[20];
};


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
	string test = "one@two@tree";

	//string* arrString;
	//arrString = substringArr(test, "@");


	ifstream foodFile;
	string line;	
	foodFile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\food.txt", ios::in);
	if (foodFile.fail()) {
		cout << "Wrong file can't oppen \n";
	}
	else {
		while (getline(foodFile, line)) {
			string* temp = substringArr(line, "@");
			cout << "Item: " << temp[0] << " amount: " << temp[1] << " price: " << temp[2] << endl;
			cout << line << "\n";
		}
		foodFile.close();
	}
	
	//if (foodFile.is_open()) {

	//}


	file.close();

	return 0;

}
