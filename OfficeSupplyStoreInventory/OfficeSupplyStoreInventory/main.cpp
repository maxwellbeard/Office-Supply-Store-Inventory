// Final Project: Office Supply Store Inventory
// Max Beard

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Item
{
	int id,					// item ID number
		quantity;			// item quantity
	string name;			// item name
	double price;			// item price
};

void readFile(ifstream&, Item[]);			// reads input from file
string dollarFormat(double);				// converts to currency format
void displayInventory(Item[]);				// displays inventory in columns
void sortID(Item[]);						// sorts inventory by ID 
void sortPrice(Item[]);						// sorts inventory by price
void validateID(Item[], int*);				// validates ID for purchase
void validateQty(Item[], int, int);			// validates quantity of item

const int SIZE = 10;

int main()
{
	Item inventory[SIZE];					// array of items in inventory
	ifstream inputFile;						// input file
	char sortOption;						// sorting option
	int idNum,								// ID number
		qty;								// quantity of item

	// reading input from file and fills array
	readFile(inputFile, inventory);

	cout << "SDEV 2310 Final Project by Max Beard\n" << endl;
	// asking for the sort
	cout << "Do you want to see the inventory sorted by ID (d) or price (p)? ";
	cin >> sortOption;
	switch (sortOption) {
	case 'd':
		sortID(inventory);
		break;
	case 'p':
		sortPrice(inventory);
		break;
	default:
		break;
	}
	// displaying inventory
	displayInventory(inventory);

	// asking for item of purchase
	while (true) {
		cout << "\nWhat item do you want to purchase? (Enter Id, -1 to stop) ";
		cin >> idNum;
		if (idNum == -1)
			break;
		// validating ID number
		validateID(inventory, &idNum);
		for (int i = 0; i < SIZE; ++i) {
			if (idNum == inventory[i].id) {
				cout << "Item " << inventory[i].name << ": How many do you want? ";
				cin >> qty;
				// validating quantity of item
				validateQty(inventory, qty, i);
				break;
			}
		}
	}
	cout << "Thank you for your business." << endl;

	system("pause");
	return 0;
}

// reads input from file
void readFile(ifstream& inputFile, Item inventory[])
{
	inputFile.open("inventory.txt");
	for (int i = 0; i < SIZE; ++i) {
		inputFile >> inventory[i].id >> inventory[i].name >> inventory[i].price >> inventory[i].quantity;
	}
}

// converts to currency format
string dollarFormat(double original)
{
	ostringstream ostr;
	ostr << fixed << showpoint << setprecision(2) << original;
	string formatted = ostr.str();
	int dp = formatted.find('.'),		// position of decimal point
		pos = dp;						// search for comma position
	while (pos > 3) {
		pos -= 3;
		formatted.insert(pos, ",");
	}
	formatted.insert(0, "$");
	return formatted;
}

// displays inventory in columns
void displayInventory(Item inventory[])
{
	cout << "\nInventory List" << endl;
	cout << setw(6) << "ID" << setw(12) << "Name" << setw(10) << "Cost " << setw(6) << "Qty" << endl;
	for (int i = 0; i < SIZE; ++i) {
		cout << setw(6) << inventory[i].id << setw(12) << inventory[i].name;
		cout << setw(10) << dollarFormat(inventory[i].price) << setw(6) << inventory[i].quantity << endl;
	}
}

// sorts inventory by ID
void sortID(Item inventory[])
{
	Item temp;
	bool swap;
	do {
		swap = false;
		for (int i = 0; i < SIZE - 1; ++i) {
			if (inventory[i].id > inventory[i + 1].id) {
				temp = inventory[i];
				inventory[i] = inventory[i + 1];
				inventory[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}

// sorts inventory by price
void sortPrice(Item inventory[])
{
	Item temp;
	bool swap;
	do {
		swap = false;
		for (int i = 0; i < SIZE - 1; ++i) {
			if (inventory[i].price > inventory[i + 1].price) {
				temp = inventory[i];
				inventory[i] = inventory[i + 1];
				inventory[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}

// validates ID for purchase
void validateID(Item inventory[], int* idNum)
{
	int i = 0;
	while (*idNum == inventory[i].id) {
		for (i = 0; i < SIZE; ++i) {
			if (*idNum == inventory[i].id)
				break;
		}
		if (*idNum == inventory[i].id)
			break;
		else {
			cout << "\nWhat item do you want to purchase? (-1 to stop) ";
			cin >> *idNum;
			if (*idNum == -1)
				break;
		}
	}
}

// validates quantity of item
void validateQty(Item inventory[], int qty, int i)
{
	if (qty <= inventory[i].quantity)
		cout << "Cost of this item is " << dollarFormat(inventory[i].price * qty) << endl;
	else
		cout << "We don't have that much in inventory" << endl;
}