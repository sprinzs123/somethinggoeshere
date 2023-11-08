//#include <iostream>
//#include <fstream>
//#include <streambuf>
//#include <sstream> 
//#include <windows.data.json.h>
//using namespace std;
//string* substringArr(string, string);
//void getValue(string, ofstream);
//
////void getValue(string search, ofstream file) {
////	string line;
////	if (file.is_open()) {
////		while (getline(file, line)) {
////			cout << line << "\n";
////		}
////	}
////	file.close();
////}
//
//
//// splitting string into array. Similar to .substring() in python, C++ doesn't has is... :(
//string* substringArr(string fullString, string delimeter) {
//	// getting all indexes where delimeter would be
//	int indexi[20];
//	string* strBrokenUp = new string[10];
//	int arrIndex = 0;
//	for (int i = 0; i < fullString.length(); i++) {
//		if (fullString[i] == '@') {
//			indexi[arrIndex] = i;
//			arrIndex++;
//		}
//	}
//
//	// making array of substring that is going to return
//	int insertIndex = 0;  // index at where going to inset string into array
//	int prevDelimiter = 0;
//	for (int i = 0; i < 3; i++) {
//		int temp = indexi[i];
//		//cout << "start: " << prevDelimiter << " end: " << temp << endl;
//		string substring =  fullString.substr(prevDelimiter, temp - prevDelimiter); // getting substring
//		strBrokenUp[insertIndex] = substring;
//		insertIndex++;
//		prevDelimiter = temp + 1;  // reseting start of string
//	}
//	return strBrokenUp;
//}
//
//
//int* demo() //return type- address of integer array
//{
//	static int a[5]; //array declared as static
//	for (int i = 0; i < 5; i++)
//	{
//		a[i] = i; //array initialisation
//	}
//
//	return a; //address of a returned
//}
//
//int main()
//{
//	string contents;
//	ifstream file;
//	file.open("C:\\Users\\cooke\\Desktop\\school\\p_data.txt", ios::in);
//	if (file.fail()) {
//		cout << "WROOOOOONDFFF";
//	}
//	//getValue("tete", file);
//
//
//
//	stringstream strStream;
//	strStream << file.rdbuf(); //read the file
//	string strText = strStream.str(); //str holds the content of the file
//	cout << "File content:" << strText << endl;
//	string test = "one@two@tree@@@";
//
//	string* arrString;
//	arrString = substringArr(test, "@");
//
//	for (int i = 0; i < 3; i++) {
//		cout << arrString[i] << endl;
//		cout << "-----------" << endl;
//	}
//
//	return 0;
//
//}
