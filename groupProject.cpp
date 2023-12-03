#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream> 
#include <fstream>
#include <iomanip> 
using namespace std;

// global varibles, mostly to know size of arrays
int foodIndex = 0;
int cardCount = 0;
char menuReturn;
char userValidator;
int menuOption;

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

// glass for holding card payments
// will need to add toString() and getters 
class CardPayment {
private:
	string AID;
	string TC;
	string label;
	string source;
	string authCode;
	string cardNumber;
	string verification;
	int transactionNum;
	float amount;
public:
	CardPayment(string _cardNumber, int _transactionNum, float _amount, string _AID, string _TC, string _label, string _source, string _authCode,  string _verification) {
		AID = _AID;
		TC = _TC;
		label = _label;
		source = _source;
		authCode = _authCode;
		cardNumber = _cardNumber;
		verification = _verification;
		transactionNum = _transactionNum;
		amount = _amount;
	}
	CardPayment() {
		amount = 0;
	}
	void setAID(string _AID) {AID = _AID;}
	void setTC(string _AID) {AID = _AID;}
	void setLabel(string _label) { label = _label; }
	void setSource(string _source) { source = _source; }
	void setAuthCode(string _authCode) { authCode = _authCode; }
	void setCardNum(string _cardNum) { cardNumber = _cardNum; }
	void setVerification(string _verification) { verification = _verification; }
	void setTransactionNum(int _num) { transactionNum= _num; }
	void setAmount(float _amount) { amount = _amount; }

	void print() {
		cout << "AID: " << AID << " TC: " << TC << " label: " << label << " source: " << source << "authCode: " << authCode << " cardNum: " << cardNumber << " verification " << verification << " transactionNum: " << transactionNum << " amount " << amount << endl;
	}
	string printAID() {	return "AID: " + AID;}
	string printTC() { return "TC: " + TC; }
	string printLabel() { return "App Name/Label: " + label; }
	string printVerification() { return "Card Verification: Fail " + verification; }
	string printTransaction() { return "Transaction #: " + to_string(transactionNum); }
	string printCardNumber() { return "xxxxxxxxxxxx" + cardNumber; }
	string printChipAuth() { return authCode; }
	string printSource() { return "Tran DataSource: " + source; }
	string printAmout() { return to_string(amount); }
	float getAmount() { return amount; }
	string printHeader() { return printTransaction() + "\n" + "\n" +  printAID() + "\n" + printTC() + "\n" + printLabel() + "\n" + printVerification() + "\n" + printSource() + "\n"; }
	//string printHeader() { return printTransaction(); }

};

class FoodItem {	
	private:
		string name;
		float price;
		int count;

	public:
		FoodItem(string _name, float _price, int _count) {
			name = _name;
			price = _price;
			count = _count;
		}	

		FoodItem() {
			name = "-1";
		}

		void printString() {cout << "Name: " << name << " price: " << price << " count: " << count << endl;}
		float getPrice() {return price;}
		int getCount() {return count;}
		string getName() { return name; }
		string getLeft() { return to_string(count) + " " + name; }

};


// ### New Functions ###
string* substringArr(string, char, int);
FoodItem selectFoodLine(string, string, int);
CardPayment selectCardLine(string, string, int);

// ### menu function
void mainMenu();
void printOne(FoodItem*);
void printTwo(CardPayment);
void saveOne(FoodItem*);
void saveTwo(CardPayment);
void userInput();


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
// find food items name and price from look up table


// pases lines from food file correctly at matches to needed id
// use look up table to find food name and price from look up table
FoodItem selectFoodLine(string chechId, string line, int delimeterCount) {	
	string foodName;
	float foodPrice = -1;
	int foodCount = -1;
	if (line.length() > 7 && line.substr(0, 5) == chechId) {
		string id = line.substr(0, 5);
		string* arrItems = substringArr(line, '-', delimeterCount);
		if (arrItems[0] == "-1") {
			//cout << "invalid object" << endl;		
		}
		else {
			//cout << "valid object " << endl;
			foodCount = stoi(arrItems[2]);
			string checkFoodId = arrItems[0]; // check id from input line
			string foodOrderCode = arrItems[1];
			//cout << checkFoodId << endl;
			if (chechId == checkFoodId){     
				//cout << "Getting from look up table" << endl;
				ifstream foodTable;
				string line;
				foodTable.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\food_table.txt", ios::in);
				if (foodTable.fail()) {
					//cout << "Wrong file can't open food look up table \n";
				}
				else {
					bool searching = true;
					while (getline(foodTable, line) && searching) {
						string* foodItem = substringArr(line, '-', 2);
						string foodCode = foodItem[0];
						// checking if food code from look up table matches food code for the item
						if (foodCode == foodOrderCode) {
							foodPrice = stof(foodItem[1]);
							foodName = foodItem[2];
							searching = false;
							foodTable.close();
						}
					}
				}
			}
		}		
	}	

	FoodItem foodItem = FoodItem(foodName, foodPrice, foodCount);
	return foodItem;
}

CardPayment selectCardLine(string chechId, string line, int delimeterCount) {
	CardPayment cardPayment;
	string* arrItems = substringArr(line, '-', delimeterCount);
	// valid card, found all items, arraay of string is correct size
	if (arrItems[0] != "-1") {		
		CardPayment newCard = CardPayment(arrItems[0], stoi(arrItems[1]), stof(arrItems[2]), arrItems[3], arrItems[4], arrItems[5], arrItems[6], arrItems[7], arrItems[8] );
		cardPayment = newCard; // assign new items to empty card object
	}
	return cardPayment;

}


int main()
{
	// ### CREATING INITIAL OBJECTS, ARRAYS, AND DOIND PARSING BEFORE GO INSIDE MENU ### \\

	// GETTING ALL VALID FOOD ITEMS
	// will have an array of all food items
	FoodItem foodArray[20];
	ifstream foodFile;
	string line;	
	foodFile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\food.txt", ios::in);
	if (foodFile.fail()) {
		cout << "Wrong file can't open food \n";
	} else {		
		while (getline(foodFile, line)) {			
			FoodItem foodItem = selectFoodLine("64337", line, 2);
			if (foodItem.getCount() != -1) { //get only valid food items
				foodArray[foodIndex] = foodItem;
				foodIndex += 1;
			}	
		}
	foodFile.close();
	}
	
	// GET VALID CARD PAYMENTS
	ifstream cardItems;
	CardPayment cardPayment;
	cardItems.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\cards.txt", ios::in);
	if (cardItems.fail()) {
		cout << "Wrong file can't open card payments \n";
	}
	else {
		while (getline(cardItems, line)) {
			CardPayment cardPaymentTemp = selectCardLine("", line, 7);
			cardPayment = cardPaymentTemp;

		}
		cardItems.close();
	}

	// #### menu items ##############
	
	menuReturn == 'Y';
	do {
		mainMenu();
		if (menuOption == 1) {
			printOne(foodArray);
			userInput();
		}
		else if (menuOption == 2) {
			cout << system("cls");
			saveOne(foodArray);
			userInput();
		}
		else if (menuOption == 3) {
			cout << system("cls");
			userInput();

		}
		else if (menuOption == 4) {
			cout << system("cls");
			userInput();

		}
		else if (menuOption == 5) {
			cout << system("cls");
			cout << "-----------> THANKS <-----------" << endl;
			exit(0);
			userInput();

		}
		//else {
		//	cout << "Invalid input, try again" << endl;
		//	mainMenu();
		//	userInput();
		//}

	} while (menuReturn == 'Y');


	return 0;

}



// ######## Menu functions will go here
void mainMenu(){
	cout << "Menu Items" << endl;
	cout << "Choose 1: " << endl;
	cin >> menuOption;

};
void printOne(FoodItem* foodItems){
	// printing food items
	for (int i = 0; i < foodIndex; i++) {		
		cout << left << setfill(' ') << setw(40) << foodItems[i].getLeft() << right << setfill(' ') << setw(10) << foodItems[i].getPrice() << endl << endl;
	}
};

void saveOne(FoodItem* foodItems){
	ofstream myfile;
	myfile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\output2.txt", ios::in);
	for (int i = 0; i < foodIndex; i++) {
		myfile << left << setfill(' ') << setw(40) << foodItems[i].getLeft() << right << setfill(' ') << setw(10) << foodItems[i].getPrice() << endl << endl;
	}
	myfile.close();


};

void printTwo(CardPayment cardPayment){
	cout << cardPayment.printHeader();
	cout << "----------------------------------------" << endl;
	cout << left << setfill(' ') << setw(20) << "Card Number" << right << setfill(' ') << setw(20) << "Auth Code" << endl;
	cout << left << setfill(' ') << setw(20) << cardPayment.printCardNumber() << right << setfill(' ') << setw(20) <<  cardPayment.printChipAuth() << endl << endl;
	cout << left << setfill(' ') << setw(20) << "Check Amount" << right << setfill(' ') << setw(20) << cardPayment.printAmout() << endl;
	cout << "----------------------------------------" << endl;
};

void saveTwo(CardPayment cardPayment){
	ofstream myfile;
	myfile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\output2.txt", ios::in);
	myfile << cardPayment.printHeader();
	myfile << "----------------------------------------" << endl;
	myfile << left << setfill(' ') << setw(20) << "Card Number" << right << setfill(' ') << setw(20) << "Auth Code" << endl;
	myfile << left << setfill(' ') << setw(20) << cardPayment.printCardNumber() << right << setfill(' ') << setw(20) << cardPayment.printChipAuth() << endl << endl;
	myfile << left << setfill(' ') << setw(20) << "Check Amount" << right << setfill(' ') << setw(20) << cardPayment.printAmout() << endl;
	myfile << "----------------------------------------" << endl;
	myfile.close();
};


// make sure that user can only enter Y or N 
// outside of scope for this tests
void userInput() {
	cout << "Go to main menu [Y/N] => ";
	cin >> userValidator;
	cout << "Input: " << userValidator << endl;
	if ((userValidator == 'Y') || (userValidator == 'N')) {
		menuReturn = userValidator;
		cout << system("cls");
	}
	else {
		cout << "Incorect Input, only can do Y or N" << endl;
		userInput(); // recursevely call this menu untill correct input is provided
	}
}
