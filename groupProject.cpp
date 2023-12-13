#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream> 
#include <fstream>
#include <iomanip> 
#include <sstream>
#include <string>

using namespace std;

// Color
void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void yellow() { printf("\033[1;33m"); }
void blue() { printf("\033[1;34m"); }
void purple() { printf("\033[1;35m"); }
void cyan() { printf("\033[1;36m"); }
void teal() { printf("\033[0;36m"); }
void white() { printf("\033[1;37m"); }
void reset() { printf("\033[1;0m"); }


// global varibles, mostly to know size of arrays
int foodIndex = 0;
int cardCount = 0;
char menuReturn;
char userValidator;
int menuOption;
string checkID = "64337";

// #### New Classes ####
class CheckMetaData {
private:
	string server;
	string manager;
	string time;
	string phone;
	string date;
	int table;
	int guests;
public:

	CheckMetaData(string _server, string _manager, string _time, string _date, int _table, int _guests) {
		this->server = _server;
		this->manager = _manager;
		this->time = _time;
		this->date = _date;
		this->table = _table;
		this->guests = _guests;
	}
	void print() {
		cout << "Server: " << server << "Manager: " << manager << "Time " << time << "Date " << date << "Table " << table << "Guests " << guests;
	}
	string getManagerLine() { return "General Manager: " + manager; }
	string getSeveLine() { return "Proudly served by : " + server; }
	string getTime() { return time; }
	string tableLine(){	return "Table " + to_string(table);}
	string guestLine() { return "Guests " + to_string(guests); }	   
	string getDate() { return date; }
	string getServer(){return server;}
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
	// getters functions or functoin that are used to print things correctly
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
		string getLeft() { return to_string(count) + " " + name; }  // ned for correct printing, it is wrongish but it is what it is

};


// ### New Functions ###
string* substringArr(string, char, int);
FoodItem selectFoodLine(string, string, int);
CardPayment selectCardLine(string, string, int);
CheckMetaData createMeta();
void printPrice(float);
void printHeader(CheckMetaData);


// ### menu function
void mainMenu();
void printOne(FoodItem*, float, CheckMetaData);
void printTwo(CardPayment, float, CheckMetaData);
void saveOne(FoodItem*, float, CheckMetaData);
void saveTwo(CardPayment, float, CheckMetaData);
void userInput();
void printData();
void printFooter(CheckMetaData);


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
	try {
		FoodItem foodItem = FoodItem(foodName, foodPrice, foodCount);
		return foodItem;
	}
	catch (int e) {
		FoodItem foodItem = FoodItem("", 0, -1);
		return foodItem;
	}
}

// creates credit card object from string
CardPayment selectCardLine(string chechId, string line, int delimeterCount) {
	CardPayment cardPayment;
	string* arrItems = substringArr(line, '-', delimeterCount);
	// valid card, found all items, arraay of string is correct size
	if (arrItems[0] != "-1" && arrItems[-1] != checkID) {
		try {
			CardPayment newCard = CardPayment(arrItems[0], stoi(arrItems[1]), stof(arrItems[2]), arrItems[3], arrItems[4], arrItems[5], arrItems[6], arrItems[7], arrItems[8]);
			cardPayment = newCard; // assign new items to empty card object
			return cardPayment;
		}
		catch (int e) {
			cout << "can't process card info";
			exit(1);
		}
	}
	else {
		cout << "can't process card info";
		exit(1);
	}

}
CheckMetaData createMeta() {
	ifstream myfile;
	myfile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\metadata.txt", ios::in);
	string line;
	getline(myfile, line);
	myfile.close();

	string* arrData = substringArr(line, '-', 6);
	if (arrData[6] == checkID && arrData[0] != "-1") {	
		try {
			return CheckMetaData(arrData[0], arrData[1], arrData[2], arrData[3], stoi(arrData[4]), stoi(arrData[5]));
		} 
		catch (string line) {
			return CheckMetaData("", "", "", "", 0, 0);
		}
	}
	else {
		return CheckMetaData("", "", "", "", 0, 0);
	}
	
}


int main()
{
	// ### CREATING INITIAL OBJECTS, ARRAYS, AND DOIND PARSING BEFORE GO INSIDE MENU ### \\

	// GETTING ALL VALID FOOD ITEMS
	// will have an array of all food items
	FoodItem foodArray[20];
	ifstream foodFile;
	string line;	
	float price = 0;
	foodFile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\food.txt", ios::in);
	if (foodFile.fail()) {
		cout << "Wrong file can't open food \n";
	} else {		
		while (getline(foodFile, line)) {			
			FoodItem foodItem = selectFoodLine("64337", line, 2);
			if (foodItem.getCount() != -1) { //get only valid food items
				foodArray[foodIndex] = foodItem;
				price += foodItem.getPrice() * foodItem.getCount();
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
	CheckMetaData metaData = createMeta();

	cout << endl;
	menuReturn == 'Y';
	do {
		mainMenu();
		if (menuOption == 1) {
			cout << system("cls");
			cout << endl;
			printData();
			userInput();
		}
		else if (menuOption == 2) {
			cout << system("cls");
			cout << endl;
			printOne(foodArray, price, metaData);
			userInput();
		}
		else if (menuOption == 3) {
			cout << system("cls");
			cout << endl;
			printTwo(cardPayment, price, metaData);
			userInput();
		}
		else if (menuOption == 4) {
			cout << system("cls");
			cout << endl;
			saveOne(foodArray, price, metaData);
			userInput();
		}
		else if (menuOption == 5) {
			cout << system("cls");
			cout << endl;
			saveTwo(cardPayment, price, metaData);
			userInput();

		}
		else if (menuOption == 8) {
			cout << system("cls");
			red();
			cout << "-----------> THANKS <-----------" << endl;
			exit(0);
			userInput();
		}
		else {
			cout << "Invalid input, try again" << endl;
			userInput();
		}

	} while (menuReturn == 'Y');
	return 0;
}


// ######## Menu functions will go here
void mainMenu(){
	cyan();
	cout << "*******************************************************" << endl;
	white();
	cout << " << Main Menu >> " << endl;
	cyan();
	cout << "*********************************************************" << endl;
	white();
	cout << "[Options]" << endl;
	white();
	cout << "[1] READ & DISPLAY INPUT DATA - ORDER" << endl;
	white();
	cout << "[2] PAYMENT-PROCESS DISPLAY THE RECEIPT PAYMENT-1" << endl;
	white();
	cout << "[3] PAYMENT-PROCESS DISPLAY THE RECEIPT PAYMENT-2" << endl;
	white();
	cout << "[4] DISPLAY OUTPUT DATA THE RECEIPT PAYMENT-1" << endl;
	white();
	cout << "[5] DISPLAY OUTPUT DATA THE RECEIPT PAYMENT-2" << endl;
	white();
	cout << "[6] DISPLAY THE CLASS DEVELOPEMENT " << endl;
	white();
	cout << "[7] DISPLAY POLYMORPHISM DEVELOPEMENT" << endl;
	white();
	cout << "[8] EXIT" << endl;
	cyan();
	cout << "*********************************************************" << endl;
	cout << "[ENTER] ";
	cin >> menuOption;

};
// print first check

void printOne(FoodItem* foodItems, float price, CheckMetaData metadata){
	
	printHeader(metadata);
	cout << endl;
	// printing food items
	for (int i = 0; i < foodIndex; i++) {		
		cout <<  left << setfill(' ') << setw(40) << foodItems[i].getLeft() << right << setfill(' ') << setw(26) << foodItems[i].getPrice() << endl;
	}
	cout << endl;
	printPrice(price);
	cout << endl;
	printFooter(metadata);

};

//save first check
void saveOne(FoodItem* foodItems, float price, CheckMetaData metaData){
	ofstream myfile;
	myfile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\output1.txt", ios::in);
	// header
	myfile << right << setfill(' ') << setw(40) << "321 Main St, City   " << endl;
	myfile << right << setfill(' ') << setw(40) << "609 420 123       " << endl;
	myfile << right << setfill(' ') << setw(40) << "* * * * Dine In * * * *" << endl;
	myfile << metaData.getManagerLine() << endl;
	myfile << metaData.getSeveLine() << endl;
	// food items
	for (int i = 0; i < foodIndex; i++) {
		myfile << left << setfill(' ') << setw(40) << foodItems[i].getLeft() << right << setfill(' ') << setw(26) << foodItems[i].getPrice() << endl;
	}
	myfile << endl;

	// price section
	myfile.width(60); myfile << right << "Subtotal " << price << endl; // enter location from subtotal
	myfile.width(56); myfile << right << "Sales tax " << price * 0.18 << endl; // enter location from sales tax
	myfile.width(66); myfile << right << "Please pay this amount" << endl;
	myfile.width(59); myfile << right << "Total " << price + price * 0.18 << endl; // enter location from Total
	myfile << "------------------------------------------------------------------\n";
	myfile << "Gratuity Not Included. Suggested amounts are\n";
	myfile << "provided for your convenience.\n";
	myfile << "------------------------------------------------------------------\n";
	myfile << left << setfill(' ') << setw(40) << "Suggested gratuity is 22% -- $" << right << setfill(' ') << setw(26) << price * 0.22 << endl;
	myfile << left << setfill(' ') << setw(40) << "Suggested gratuity is 20% -- $" << right << setfill(' ') << setw(26) << price * 0.20 << endl;
	myfile << left << setfill(' ') << setw(40) << "Suggested gratuity is 18% -- $" << right << setfill(' ') << setw(26) << price * 0.18 << endl;
	myfile << endl;
	// footer section
	myfile << "------------------------------------------------------------------ \n";
	myfile << "THANKS FOR VISITING US TODAY!\n";
	myfile << "------------------------------------------------------------------ \n";
	myfile << left << setfill(' ') << setw(40) << "OG#1482" << right << setfill(' ') << setw(26) << metaData.guestLine() << endl;
	myfile << left << setfill(' ') << setw(40) << "Check# " + checkID << right << setfill(' ') << setw(26) <<" " + metaData.getTime() << endl;
	myfile << left << setfill(' ') << setw(40) << "Table " + metaData.tableLine() << right << setfill(' ') << setw(26) << " " + metaData.getDate() << endl;
	myfile.close();

	cout << left <<"OUTPUT FILE:" << endl;
	ifstream file;
	file.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\output2.txt", ios::in);
	string line2;
	while (!file.fail() && !file.eof()) {
		getline(file, line2);
		cout << line2 << endl;
	}
	file.close();

};

// print second check
void printTwo(CardPayment cardPayment, float price, CheckMetaData metaData){
	cout << right << setfill(' ') << setw(40) << "321 Main St, City   " << endl;
	cout << right << setfill(' ') << setw(40) << "609 420 123       " << endl;
	cout << right << setfill(' ') << setw(40) << "* * * * Dine In * * * *" << endl;

	cout << right << setw(66) << "Check#" + checkID << endl;
	cout << metaData.tableLine();
	cout << metaData.getServer() << endl;
	cout << left << setfill(' ') << setw(40) << metaData.getDate() + " " + metaData.getTime() << right << setfill(' ') << setw(26) << metaData.guestLine() << endl;

	
	cout << cardPayment.printHeader();
	cout << left << setfill('-') << setw(66) << ' ' << endl;
	cout << left << setfill(' ') << setw(40) << "Card Number" << right << setfill(' ') << setw(26) << "Auth Code" << endl;
	cout << left << setfill(' ') << setw(40) << cardPayment.printCardNumber() << right << setfill(' ') << setw(26) <<  cardPayment.printChipAuth() << endl << endl;
	cout << left << setfill(' ') << setw(40) << "Check Amount" << right << setfill(' ') << setw(26) << cardPayment.printAmout() << endl;
	cout << "------------------------------------------------------------------\n";
	cout << "Gratuity Not Included. Suggested amounts are\n";
	cout << "provided for your convenience.\n";
	cout << "------------------------------------------------------------------\n";
	cout << left << setfill(' ') << setw(40) << "Suggested gratuity is 22% -- $" << right << setfill(' ') << setw(26) << price * 0.22 << endl;
	cout << left << setfill(' ') << setw(40) << "Suggested gratuity is 20% -- $" << right << setfill(' ') << setw(26) << price * 0.20 << endl;
	cout << left << setfill(' ') << setw(40) << "Suggested gratuity is 18% -- $" << right << setfill(' ') << setw(26) << price * 0.18 << endl;
	cout << endl;
	cout << left << setfill(' ') << setw(40) << "Gratuity..." << right << setfill(' ') << setw(26) << "___________" << endl;
	cout << left << setfill(' ') << setw(40) << "Total...   " << right << setfill(' ') << setw(26) << "___________";
	cout << endl << endl;
	cout << "X";
	cout << left << setfill('_') << setw(65) << "" << endl;
	cout << left << setw(65) << "Cardmember agrees to pay total in accordance \nwith agreement governing use of such card.\n";
	cout << right << setfill(' ') << setw(40) << "Guest Copy" << endl;

};

// save second check
void saveTwo(CardPayment cardPayment, float price, CheckMetaData metaData){ 
	ofstream myfile;
	myfile.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\output2.txt", ios::in);
	myfile << right << setfill(' ') << setw(40) << "321 Main St, City   " << endl;
	myfile << right << setfill(' ') << setw(40) << "609 420 123       " << endl;
	myfile << right << setfill(' ') << setw(40) << "* * * * Dine In * * * *" << endl;
	myfile << metaData.getManagerLine() << endl;
	myfile << metaData.getSeveLine() << endl;
	myfile << "------------------------------------------------------------------ \n";

	myfile << right << setw(66) << "Check#" + checkID << endl;
	myfile << metaData.tableLine();
	myfile << metaData.getServer() << endl;
	myfile << left << setfill(' ') << setw(40) << metaData.getDate() + " " + metaData.getTime() << right << setfill(' ') << setw(26) << metaData.guestLine() << endl;

	// card payment 
	myfile << cardPayment.printHeader();
	myfile << left << setfill('-') << setw(66) << ' ' << endl;
	myfile << left << setfill(' ') << setw(40) << "Card Number" << right << setfill(' ') << setw(26) << "Auth Code" << endl;
	myfile << left << setfill(' ') << setw(40) << cardPayment.printCardNumber() << right << setfill(' ') << setw(26) << cardPayment.printChipAuth() << endl << endl;
	myfile << left << setfill(' ') << setw(40) << "Check Amount" << right << setfill(' ') << setw(26) << cardPayment.printAmout() << endl;
	myfile << "------------------------------------------------------------------\n";
	printPrice(price);

	// gratuity
	float totalAndTax = (price * 0.18 + price);
	float tax = price * 0.18;
	myfile << "------------------------------------------------------------------\n";
	myfile << "Gratuity Not Included. Suggested amounts are\n";
	myfile << "provided for your convenience.\n";
	myfile << "------------------------------------------------------------------\n";
	myfile << left << setfill(' ') << setw(40) << "Suggested gratuity is 22% -- $" << right << setfill(' ') << setw(26) << price * 0.22 << endl;
	myfile << left << setfill(' ') << setw(40) << "Suggested gratuity is 20% -- $" << right << setfill(' ') << setw(26) << price * 0.20 << endl;
	myfile << left << setfill(' ') << setw(40) << "Suggested gratuity is 18% -- $" << right << setfill(' ') << setw(26) << price * 0.18 << endl;

	myfile << endl;
	myfile << left << setfill(' ') << setw(40) << "Gratuity..." << right << setfill(' ') << setw(26) << "___________" << endl;
	myfile << left << setfill(' ') << setw(40) << "Total...   " << right << setfill(' ') << setw(26) << "___________";
	myfile << endl << endl;
	myfile << "X";
	myfile << left << setfill('_') << setw(65) << "" << endl;
	myfile << left << setw(65) << "Cardmember agrees to pay total in accordance \nwith agreement governing use of such card.\n";
	myfile << right << setfill(' ') << setw(40) << "Guest Copy" << endl;





	myfile.close();

	ifstream file;
	string line2;
	file.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\output2.txt", ios::in);
	while (!file.fail() && !file.eof()) {
		getline(file, line2);
		cout << line2 << endl;
	}
	file.close();
};

void printPrice(float price) {
	float totalAndTax = (price + (price * 0.18));
	float tax = price * 0.18;
	cout.width(60); cout << right << "Subtotal " << price << endl; // enter location from subtotal
	cout.width(60); cout << right << "Sales tax "<< price *0.18 << endl; // enter location from sales tax
	cout.width(66); cout << right << "Please pay this amount" << endl;
	cout.width(59); cout << right << "Total " << totalAndTax << endl; // enter location from Total
	cout << "------------------------------------------------------------------\n";
	cout << "Gratuity Not Included. Suggested amounts are\n";
	cout << "provided for your convenience.\n";
	cout << "------------------------------------------------------------------\n";
	cout << left << setfill(' ') << setw(40) << "Suggested gratuity is 22% -- $" << right << setfill(' ') << setw(26) << price * 0.22 << endl;
	cout << left << setfill(' ') << setw(40) << "Suggested gratuity is 20% -- $" << right << setfill(' ') << setw(26) << price * 0.20 << endl;
	cout << left << setfill(' ') << setw(40) << "Suggested gratuity is 18% -- $" << right << setfill(' ') << setw(26) << price * 0.18 << endl;
}



void printHeader(CheckMetaData metaData) {
	string test;
	cout << right << setfill(' ') << setw(40) << "321 Main St, City   " << endl;
	cout << right << setfill(' ') << setw(40) << "609 420 123       " << endl;
	cout << right << setfill(' ') << setw(40) << "* * * * Dine In * * * *" << endl;
	cout << metaData.getManagerLine() << endl;
	cout << metaData.getSeveLine() << endl;
	cout << "------------------------------------------------------------------ \n";
}
void printFooter(CheckMetaData metadata) {
	cout << "------------------------------------------------------------------ \n";
	cout << "THANKS FOR VISITING US TODAY!\n";
	cout << "------------------------------------------------------------------ \n";
	cout << left << setfill(' ') << setw(40) << "OG#1482" << right << setfill(' ') << setw(26) << metadata.guestLine() << endl;
	cout << left << setfill(' ') << setw(40) << "Check Number " + checkID << right << setfill(' ') << setw(26) << metadata.getTime() << endl;
	cout << left << setfill(' ') << setw(40) << "Table " + metadata.tableLine()  << right << setfill(' ') << setw(26) << metadata.getDate() << endl;
	cout << endl;

}

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
void printData() {
	ifstream file;
	string line;
	file.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\food.txt", ios::in); \
	cout << "Food files \n";
	while (!file.fail() && !file.eof()) {
		file >> line;
		cout << line<< endl;
	}	
	file.close();
	cout << endl;

	file.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\food_table.txt", ios::in); \
		cout << "Food look up table \n";
	while (!file.fail() && !file.eof()) {
		getline(file,line);
		cout << line << endl;
	}
	file.close();
	cout << endl;

	file.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\visa_payment.txt", ios::in); \
		cout << "Credit card payment \n";
	while (!file.fail() && !file.eof()) {
		getline(file, line);
		cout << line;

	}
	file.close();
	cout << endl;

	file.open("C:\\Users\\cooke\\Desktop\\school\\c_plus_plus\\groupProject\\groupProject\\payments.txt", ios::in); 
	cout << "Gift Cards \n";
	while (!file.eof()) {
		getline(file, line);
		cout << line;
	}
	file.close();

}

