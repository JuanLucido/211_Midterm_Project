#include <iostream>
#include <fstream>
#include <string>	
#include <cstring>	//used to convert user entry into a character array
#include <vector>	
#include <limits>	//used for cin.ignore() to ignore user excessive input
#include <iomanip>	//user for cin-type directives

using namespace std;

const int MAX_SIZE = 5000; //Global for max size of user-entered char array

void returnToMenu() { //Returning prompt message
	cout << "\nReturning to previous menu ...\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void opsComplete() { //Alerts user that the action they performed completed
	cout << "\nOperation complete! Now returning to the previous menu...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool entryFailed(char array[], int low, int high, int &choice) { //Returns true/false within while loop parentheses

	int conversion = 0;

	if (strlen(array) > 2) {} //Converts Char array[] to statically cast integer
	else if (strlen(array) == 1) { conversion = static_cast<int>(array[0]) - 48; }
	else if (strlen(array) == 2) {
		conversion = 10 * (static_cast<int>(array[0]) - 48) + (static_cast<int>(array[1]) - 48);
	}

	if (conversion < low || conversion > high) { //Returns error until user inputs valid choice
		cin.clear(); //clears error flags
		cerr << "\nINVALID INPUT! Enter ONLY what the prompt says!!! ...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	else { //If user entered valid choice, exits loop
		choice = conversion; //sets conversion of character array to integer needed to menu/user
		return false;
	}
}

class PChar //Player Character
{
public:
	string teamName;
	string fullName;
	int str, dex, con, intl, wis, cha;
	vector<string> Inventory; //item inventory

	PChar(); //Default Constructor

	//Overload Assignment
	PChar& operator=(const PChar& source);

	void printCharacter(); //Self explanatory
	
	void changeInventory(); //Modifies Inventory vector

	void printInventory(); //Self explanatory

	void alterInventory(); //Prints PChar Inventory for when modifying it

	void changeStats(); //Changes str, dex, con, intl, wis, cha

	int statModifier(int currentStat); //Converts primary stat to appropriate D&D modifier

	char modifierSign(int currentStat); //Gives '+' character when paired with statModifier() function

	void changeName(); //Self explanatory

	void changeTeamName(string newTeamName) { *partyName = newTeamName; } //Used when new character is created

	string getTeamName() { return teamName; } //These are getters
	string getName() { return fullName; }
	int stre() { return str; }
	int dexe() { return dex; }
	int cons() { return con; }
	int intel() { return intl; }
	int wisd() { return wis; }
	int chari() { return cha; }

	void stren(int &str, int newValue) { str = newValue; } //These are setters
	void dexet(int& dex, int newValue) { dex = newValue; }
	void consti(int& str, int newValue) { con = newValue; }
	void inteli(int& str, int newValue) { intl = newValue; }
	void wisdo(int& str, int newValue) { wis = newValue; }
	void charis(int& str, int newValue) { cha = newValue; }

private:
	string *characterName = &fullName; //Pointers of stats to reference in printCharacter() function
	string *partyName = &teamName;
	int *STR = &str, 
		*DEX = &dex,
		*CON = &con,
		*INT = &intl,
		*WIS = &wis,
		*CHA = &cha;
	int* equipSize; //Used to reference size of Inventory
};

class Team //Stores generated PChar objcts onto Team (in vector)
{
public:
	string teamName;

	vector<PChar> party; //Vector of Player Character Objects!!!

	PChar pchar; //I've a lot of PChar objects created here because I couldn't get the program to work otherwise :(
	PChar pchar1, pchar2, pchar3, pchar4, pchar5, pchar6, pchar7, pchar8, pchar9, pchar10, pcharA, pcharB, pcharC;
	PChar pchar11, pchar12, pchar13, pchar14, pchar15, pchar16, pchar17, pchar18, pchar19, pchar20, pcharD, pcharE, pcharF;
	
	string getTeamName() { return teamName; } //Getter for team name
	void eraseParty(); //Used when reloading teams from text file
	void loadTeam1(); //Loads Team1.txt
	void loadTeam2(); //Loads Team2.txt

private:
	string* partyName = &teamName; //Self explanatory
};

PChar::PChar() //Default Constructor
{
	*characterName = "New Character";
	teamName = "NULL";
	str = dex = con = intl = wis = cha = 10;
	Inventory.push_back("Dagger");
	equipSize = new int(Inventory.size());
}

PChar& PChar::operator=(const PChar& source) { //Overload Assignment Operator ( = ). Used when loading teams from text file
	//cout << "Overload Assignment Called." << endl;

	if (this == &source)
	{
		return *this;
	}
	this->teamName = source.teamName; //References all stats of temporary PChar object being referenced
	this->fullName = source.fullName;
	this->str = source.str;
	this->dex = source.dex;
	this->con = source.con;
	this->intl = source.intl;
	this->wis = source.wis;
	this->cha = source.cha;
	for (int i = 0; i < Inventory.size(); i++) { //Deletes previous Inventory
		Inventory.pop_back();
	}
	for (int i = 0; i < source.Inventory.size(); i++) { //Copies new Inventory
		Inventory.push_back(source.Inventory.at(i));
	}
	equipSize = new int(Inventory.size()); //Resets pointer Inventory size
}

void PChar::changeName() //Self explanatory
{
	string newName;
	
	cout << "\n---------------------------------------------------------\n";
	cout << "\nChanging name of: [" << getName() << "]! Input new name: ";
	getline(cin, newName);
	fullName = newName;
	opsComplete();
}

void PChar::printInventory() //Prints PChar
{
	cout << "\nInventory: [" << *equipSize << "] Total Items\n";
	for (int i = 0; i < *equipSize; i++) {
		cout << "- "<< Inventory.at(i) << endl;
	}
}

void PChar::alterInventory() //Prints PChar Inventory for when modifying it
{
	cout << "\nInventory: [" << *equipSize << "] Total Items\n";
	for (int i = 0; i < *equipSize; i++) {
		cout << i + 1 << ") " << Inventory.at(i) << endl;
	}
}

void PChar::changeInventory() //Modifies Inventory vector
{
	char selection[MAX_SIZE];
	int userChoice;

	char subSelection[MAX_SIZE];
	int userSubSelection;

	string itemName;

	while (true) {
		int low = 1;
		int high = *equipSize + 2; //locally defined lower and upper limits

		do {

			cout << "\n---------------------------------------------------------\n";
			cout << "\nEditing Inventory of: [" << getName() << "]!\n\nSelect an option to edit/delete an item or add a new one:\n";
			alterInventory();
			cout << "___\n";
			cout << *equipSize + 1 << ") " << "Add new Item\n"
				 << *equipSize + 2 << ") " << "Return to previous menu\n\nYour selection : ";
			cin.getline(selection, MAX_SIZE);
		} while (entryFailed(selection, low, high, userChoice));

		if (userChoice == *equipSize + 2) { //Exits this void function
			returnToMenu();
			return;
		}
		else if (userChoice == *equipSize + 1 ) { //Adds new item to vector
			cout << "\n---------------------------------------------------------\n";
			cout << "\nEnter the name of new item: ";
			getline(cin, itemName);
			Inventory.push_back(itemName);
			delete equipSize;
			equipSize = new int(Inventory.size());
			cout << "Equip size: " << *equipSize << endl;
		}
		else if (userChoice <= *equipSize) { //Edits selected item
			do {
				low = 1;
				high = 2;
				cout << "\n---------------------------------------------------------\n";
				cout << "1) Replace / Change item name\n"
					 << "2) Delete item\n\nYour selection: ";
				cin.getline(subSelection, MAX_SIZE);
			} while (entryFailed(subSelection, low, high, userSubSelection));

			switch (userSubSelection) { 
			case 1: //Edits selected item name
				cout << "\nEnter item's new name: ";
				getline(cin, itemName);
				Inventory[userChoice - 1] = itemName;
				break;
			case 2: // Deletes item
				cout << "Deleting item ..."; 
				Inventory.erase(Inventory.begin() + (userChoice - 1));
				delete equipSize;
				equipSize = new int(Inventory.size());
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
		} 
		opsComplete();
	}
}

void PChar::printCharacter() //Self explanatory
{
	cout << "\n---------------------------------------------------------\n";
	cout << "\n[ " << getName() << " ]'s Stats:\n"
		 << "\nMember of: " << getTeamName() << endl << endl
		 << "Strength\t= " << setw(2) << *STR << " , (" << modifierSign(*STR) << statModifier(*STR) << ")\n"
		 << "Dexterity\t= " << setw(2) << *DEX << " , (" << modifierSign(*DEX) << statModifier(*DEX) << ")\n"
		 << "Constitution\t= " << setw(2) << *CON << " , (" << modifierSign(*CON) << statModifier(*CON) << ")\n"
		 << "Intelligence\t= " << setw(2) << *INT << " , (" << modifierSign(*INT) << statModifier(*INT) << ")\n"
		 << "Wisdom\t\t= " << setw(2) << *WIS << " , (" << modifierSign(*WIS) << statModifier(*WIS) << ")\n"
		 << "Charisma\t= " << setw(2) << *CHA << " , (" << modifierSign(*CHA) << statModifier(*CHA) << ")\n";
	printInventory();
}

int PChar::statModifier(int currentStat) //returns D&D calculation for stat modifier 
{
	double tempStat = (static_cast<double>(currentStat) - 10) / 2;
	return static_cast<int>(floor(tempStat));
}

char PChar::modifierSign(int currentStat) //returns stat's sign if it's positive
{
	double tempStat = (static_cast<double>(currentStat) - 10) / 2;
	if (tempStat >= 0) {
		return '+';
	}
	else {
		return '\0'; //returns nothing (NULL) since negative values already display their sign in execution
	}
}

void PChar::changeStats() //Alters existing character.
{
	char selection[MAX_SIZE];
	int userChoice;

	char stats[MAX_SIZE];
	int stat;

	while (true) {
		int low = 1; //locally defined lower and upper limits
		int high = 7;
		do {
			cout << "\n---------------------------------------------------------\n";
			cout << "\nChanging [" << getName() << "]'s Stats!\n";
			cout << "\nSelect a number option to change a stat or go back:\n"
				<< "1) Strength\t= " << setw(2) << stre() << " , (" << modifierSign(stre()) << statModifier(stre()) << ")\n"
				<< "2) Dexterity\t= " << setw(2) << dexe() << " , (" << modifierSign(dexe()) << statModifier(dexe()) << ")\n"
				<< "3) Constitution\t= " << setw(2) << cons() << " , (" << modifierSign(cons()) << statModifier(cons()) << ")\n"
				<< "4) Intelligence\t= " << setw(2) << intel() << " , (" << modifierSign(intel()) << statModifier(intel()) << ")\n"
				<< "5) Wisdom\t= " << setw(2) << wisd() << " , (" << modifierSign(wisd()) << statModifier(wisd()) << ")\n"
				<< "6) Charisma\t= " << setw(2) << chari() << " , (" << modifierSign(chari()) << statModifier(chari()) << ")\n"
				<< "7) Return to previous menu\n\nYour selection: ";

			cin.getline(selection, MAX_SIZE);

		} while (entryFailed(selection, low, high, userChoice));

		if (userChoice == 7) { //Exits this void function to be input back into Character Editor Menu/Loop
			returnToMenu();
			return; 
		} 

		do {
			low = 1;
			high = 20;
			cout << "Enter an integer within the range 1 - 20: ";
			cin.getline(stats, MAX_SIZE);
		} while (entryFailed(stats, low, high, stat));

		switch (userChoice) {
		case 1:
			stren(str, stat);
			break;
		case 2:
			dexet(dex, stat);
			break;
		case 3:
			consti(con, stat);
			break;
		case 4:
			inteli(intl, stat);
			break;
		case 5:
			wisdo(wis, stat);
			break;
		case 6:
			charis(cha, stat);
			break;
		}
		opsComplete();
	}
}

void Team::loadTeam1() //Loads Team1 specifically from Team1.txt
{
	ifstream teamIn;

	teamIn.open("Team1.txt");
	if (teamIn.fail()) {
		cerr << "File failed to open 'Team1.txt'";
		abort();
	}

	string item;

	getline(teamIn, pchar.teamName);
	*partyName = pchar.teamName;
	unsigned int i = 0;

	while(!teamIn.eof()) {
		
		//Clear out character inventory built by constructor just in case items are in the inventory
		while (pchar.Inventory.size() > 0) {
			pchar.Inventory.pop_back();
		}
		getline(teamIn, pchar.fullName);
		teamIn >> pchar.str;
		teamIn >> pchar.dex;
		teamIn >> pchar.con;
		teamIn >> pchar.intl;
		teamIn >> pchar.wis;
		teamIn >> pchar.cha;
		getline(teamIn, item);
		getline(teamIn, item);
		while (item != "----------") { //Checks for character divider that separates character objects
			pchar.Inventory.push_back(item);
			getline(teamIn, item);
		}
		
		switch (i) {
		case 0:
			pchar1 = pchar;
			party.push_back(pchar1);
			break;
		case 1:
			pchar2 = pchar;
			party.push_back(pchar2);
			break;
		case 2:
			pchar3 = pchar;
			party.push_back(pchar3);
			break;
		case 3:
			pchar4 = pchar;
			party.push_back(pchar4);
			break;
		case 4:
			pchar5 = pchar;
			party.push_back(pchar5);
			break;
		case 5:
			pchar6 = pchar;
			party.push_back(pchar6);
			break;
		case 6:
			pchar7 = pchar;
			party.push_back(pchar7);
			break;
		case 7:
			pchar8 = pchar;
			party.push_back(pchar8);
			break;
		case 8:
			pchar9 = pchar;
			party.push_back(pchar9);
			break;
		case 9:
			pchar10 = pchar;
			party.push_back(pchar10);
			break;
		default:
			break;
		}
		i++;
	}
	teamIn.close();
}

void Team::loadTeam2() //Loads Team2 specifically from Team2.txt
{
	ifstream teamIn;

	teamIn.open("Team2.txt");
	if (teamIn.fail()) {
		cerr << "File failed to open 'Team2.txt'";
		abort();
	}

	string item;

	getline(teamIn, pchar.teamName);
	*partyName = pchar.teamName;
	unsigned int i = 0;

	while (!teamIn.eof()) {
		while (pchar.Inventory.size() > 0) {
			pchar.Inventory.pop_back();
		}
		getline(teamIn, pchar.fullName);
		teamIn >> pchar.str;
		teamIn >> pchar.dex;
		teamIn >> pchar.con;
		teamIn >> pchar.intl;
		teamIn >> pchar.wis;
		teamIn >> pchar.cha;
		getline(teamIn, item);
		getline(teamIn, item);
		while (item != "----------") {
			pchar.Inventory.push_back(item);
			getline(teamIn, item);
		}

		switch (i) {
		case 0:
			pchar11 = pchar;
			party.push_back(pchar11);
			break;
		case 1:
			pchar12 = pchar;
			party.push_back(pchar12);
			break;
		case 2:
			pchar13 = pchar;
			party.push_back(pchar13);
			break;
		case 3:
			pchar14 = pchar;
			party.push_back(pchar14);
			break;
		case 4:
			pchar15 = pchar;
			party.push_back(pchar15);
			break;
		case 5:
			pchar16 = pchar;
			party.push_back(pchar16);
			break;
		case 6:
			pchar17 = pchar;
			party.push_back(pchar17);
			break;
		case 7:
			pchar18 = pchar;
			party.push_back(pchar18);
			break;
		case 8:
			pchar19 = pchar;
			party.push_back(pchar19);
			break;
		case 9:
			pchar20 = pchar;
			party.push_back(pchar20);
			break;
		default:
			break;
		}
		i++;
	}
	teamIn.close();
}

void Team::eraseParty() //Used to reduce size of team.party (of PChar objects) to 0
{
	while (party.size() > 0) {
		party.erase(party.begin());
	}
}

void reduceVector(vector <PChar> &vec, int choice) //Called when deleting a PChar on a team. Pass by reference
{
	vector <PChar> temp;
	int size = vec.size() - 1;
	for (int i = 0; i < vec.size(); i++) {
		if (i == choice - 1) { } //Passes over character intended to be deleted
		else {
			temp.push_back(vec.at(i)); //Stores old vector of PChar's to temporary array of PChars
		}
	}
	while (vec.size() > 0) {
		vec.erase(vec.begin()); //Reduces old vector of PChars to 0
	}
	for (int i = 0; i < size; i++) {
		vec.push_back(temp.at(i)); //Copies temp vector of PChars to team's
	}
}

void reloadVector(vector <PChar>& vec) //Called when adding a new character to vector of PChars
{
	vector <PChar> temp;
	int size = vec.size();
	for (int i = 0; i < vec.size(); i++) {
			temp.push_back(vec.at(i));
	}
	while (vec.size() > 0) {
		vec.erase(vec.begin());
	}
	for (int i = 0; i < size; i++) {
		vec.push_back(temp.at(i));
	}
}

void alterTeam(Team &team, int &size) //Menu called when editing a specific team. Pass by reference. Modifies intended team
{
	while (true) {
		size = team.party.size();
		cout << "\n---------------------------------------------------------\n";
		cout << "\nEditing Team: " << team.teamName << "\n\n";
		for (int i = 0; i < 13; i++) { //13 because that the max amount supported by Team Class
			if (i < size) {
				cout << i + 1 << ". " << team.party.at(i).getName() << endl; //Prints out selected team list of characters
			}
			else {
				if (i == team.party.size()) { cout << endl; }
				cout << "(Empty Slot)\n";
			}
		}

		char selection[MAX_SIZE];
		int userChoice;

		char subSelection[MAX_SIZE];
		int subChoice;

		int low = 1; //locally defined lower and upper limits
		int high = size + 3;
		do {
			cout << "\nSelect a #'d character above to VIEW / EDIT / DELETE, or option below:\n\n"
				<< size + 1 << ". Add NEW character to (Empty Slot)\n"
				<< size + 2 << ". Change Team Name\n"
				<< size + 3 << ". Return to previous menu\n\nYour selection: ";
			cin.getline(selection, MAX_SIZE);
		} while (entryFailed(selection, low, high, userChoice));

		if (userChoice <= size) {
			high = 5;
			int subChoice;

			while (true) {
				do {
					team.party.at(userChoice - 1).printCharacter();
					cout << "\nChoose to EDIT this character or DELETE it:\n"
						<< "1. CHANGE NAME\n"
						<< "2. EDIT STATS\n"
						<< "3. EDIT INVENTORY\n"
						<< "4. DELETE\n"
						<< "5. Return to previous menu\n\nYour selection : ";
					cin.getline(subSelection, MAX_SIZE);
				} while (entryFailed(subSelection, low, high, subChoice));

				if (subChoice == 5) { 
					returnToMenu();
					break; 
				}

				switch (subChoice) {
				case 1:
					team.party.at(userChoice - 1).changeName();
					break;
				case 2:
					team.party.at(userChoice - 1).changeStats();
					break;
				case 3:
					team.party.at(userChoice - 1).changeInventory();
					break;
				case 4:
					cout << "\n---------------------------------------------------------\n";
					cout << "\nDeleting character ...\n";
					reduceVector(team.party, userChoice);
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}
				if (subChoice == 4) {
					opsComplete();
					break;
				}
			}
		}
		else if (userChoice == size + 1){ //Add new PChar Object to vector
			cout << "\n---------------------------------------------------------\n";
			cout << "\nCreating new character ...\n";
			PChar temp;
			temp.teamName = team.getTeamName();
			team.party.push_back(temp);
			reloadVector(team.party);
			opsComplete();
		}
		else if (userChoice == size + 2) {
			cout << "\nChanging [ " << team.teamName << " ]'s name: ";
			cin.getline(selection, MAX_SIZE);
			team.teamName = selection;
			opsComplete();
		}
		else if (userChoice == size + 3) {
			returnToMenu();
			return;
		}
	}
}

void exportTeams(Team team1, Team team2) //Called when outputting Teams to outputTeam1.txt or outputTeam2.txt
{
	char selection[MAX_SIZE];
	int userChoice;

	int low = 1; //locally defined lower and upper limits
	int high = 3;
	do {
		cout << "\nExport Team1 or Team2?\n\n"
			<< "1. TEAM1\n"
			<< "2. TEAM2\n"
			<< "3. Return to previous menu\n\nYour selection: ";
		cin.getline(selection, MAX_SIZE);
	} while (entryFailed(selection, low, high, userChoice));
	
	if (userChoice == 3) { 
		returnToMenu(); 
		return; 
	}

	ofstream outFile;

	switch (userChoice) {
	case 1:
	{
		outFile.open("outputTeam1.txt");
		if (outFile.fail())//checks that file can be opened
		{
			cerr << "File failed to open: outputTeam1.txt";//spits out error message if not
			abort();// aborts program
		}
		int size;
		outFile << team1.teamName << endl;
		for (int i = 0; i < team1.party.size(); i++) {
			outFile << "\n[ " << team1.party.at(i).getName() << " ]'s Stats:\n\n"
				<< "Strength\t\t= " << setw(2) << team1.party.at(i).stre() << " , (" << team1.party.at(i).modifierSign(team1.party.at(i).stre()) << team1.party.at(i).statModifier(team1.party.at(i).stre()) << ")\n"
				<< "Dexterity\t\t= " << setw(2) << team1.party.at(i).dexe() << " , (" << team1.party.at(i).modifierSign(team1.party.at(i).dexe()) << team1.party.at(i).statModifier(team1.party.at(i).dexe()) << ")\n"
				<< "Constitution\t= " << setw(2) << team1.party.at(i).cons() << " , (" << team1.party.at(i).modifierSign(team1.party.at(i).cons()) << team1.party.at(i).statModifier(team1.party.at(i).cons()) << ")\n"
				<< "Intelligence\t= " << setw(2) << team1.party.at(i).intel() << " , (" << team1.party.at(i).modifierSign(team1.party.at(i).intel()) << team1.party.at(i).statModifier(team1.party.at(i).intel()) << ")\n"
				<< "Wisdom\t\t\t= " << setw(2) << team1.party.at(i).wisd() << " , (" << team1.party.at(i).modifierSign(team1.party.at(i).wisd()) << team1.party.at(i).statModifier(team1.party.at(i).wisd()) << ")\n"
				<< "Charisma\t\t= " << setw(2) << team1.party.at(i).chari() << " , (" << team1.party.at(i).modifierSign(team1.party.at(i).chari()) << team1.party.at(i).statModifier(team1.party.at(i).chari()) << ")\n";

			size = team1.party.at(i).Inventory.size();

			outFile << "\nInventory: [" << size << "] Total Items\n";
			for (int j = 0; j < size; j++) {
				outFile << "- " << team1.party.at(i).Inventory.at(j) << endl;
			}
			outFile << "----------\n";
		}
		outFile.close();
		break;
	}
	case 2:
	{
		outFile.open("outputTeam2.txt");
		if (outFile.fail()) { //checks that file can be opened
			cerr << "File failed to open: outputTeam2.txt";//spits out error message if not
			abort();// aborts program
		}
		int size;
		outFile << team2.teamName << endl;
		for (int i = 0; i < team2.party.size(); i++) {
			outFile << "\n[ " << team2.party.at(i).getName() << " ]'s Stats:\n\n"
				<< "Strength\t\t= " << setw(2) << team2.party.at(i).stre() << " , (" << team2.party.at(i).modifierSign(team2.party.at(i).stre()) << team2.party.at(i).statModifier(team2.party.at(i).stre()) << ")\n"
				<< "Dexterity\t\t= " << setw(2) << team2.party.at(i).dexe() << " , (" << team2.party.at(i).modifierSign(team2.party.at(i).dexe()) << team2.party.at(i).statModifier(team2.party.at(i).dexe()) << ")\n"
				<< "Constitution\t= " << setw(2) << team2.party.at(i).cons() << " , (" << team2.party.at(i).modifierSign(team2.party.at(i).cons()) << team2.party.at(i).statModifier(team2.party.at(i).cons()) << ")\n"
				<< "Intelligence\t= " << setw(2) << team2.party.at(i).intel() << " , (" << team2.party.at(i).modifierSign(team2.party.at(i).intel()) << team2.party.at(i).statModifier(team2.party.at(i).intel()) << ")\n"
				<< "Wisdom\t\t\t= " << setw(2) << team2.party.at(i).wisd() << " , (" << team2.party.at(i).modifierSign(team2.party.at(i).wisd()) << team2.party.at(i).statModifier(team2.party.at(i).wisd()) << ")\n"
				<< "Charisma\t\t= " << setw(2) << team2.party.at(i).chari() << " , (" << team2.party.at(i).modifierSign(team2.party.at(i).chari()) << team2.party.at(i).statModifier(team2.party.at(i).chari()) << ")\n";

			size = team2.party.at(i).Inventory.size();

			outFile << "\nInventory: [" << size << "] Total Items\n";
			for (int j = 0; j < size; j++) {
				outFile << "- " << team2.party.at(i).Inventory.at(j) << endl;
			}
			outFile << "----------\n";
		}
		outFile.close();
		break;
	}
	}


	
}

void mainMenu(Team &team1, Team &team2) //This is the main menu splash page when entering program
{
	while (true) {
		cout << "\n---------------------------------------------------------\n\n"
			<< "---------- WELCOME TO THE MAIN MENU ----------\n";
		cout << "\nTeam1: " << team1.teamName << "\t\t" << "Team2: " << team2.teamName << "\n\n";

		int size1 = team1.party.size();
		int size2 = team2.party.size();

		for (int i = 0; i < 13; i++) { //13 because that the max amount supported by Team Class
			if (i < size1) {
				cout << left << setw(32) << team1.party.at(i).getName();
			}
			else {
				cout << left << setw(32) << "(Empty Slot)";
			}
			if (i < size2) {
				cout << team2.party.at(i).fullName << endl;
			}
			else {
				cout << "(Empty Slot)\n";
			}
		}

		char selection[MAX_SIZE];
		int userChoice;

		int low = 1; //locally defined lower and upper limits
		int high = 5;
		do {
			cout << "\nSelect an option below to continue:\n\n"
				<< "1. View / Edit Team1\n"
				<< "2. View / Edit Team2\n"
				<< "3. Reload Teams from text file\n"
				<< "4. Export Teams to text file\n"
				<< "5. Quit Program\n\nYour selection: ";

			cin.getline(selection, MAX_SIZE);
		} while (entryFailed(selection, low, high, userChoice));

		switch (userChoice) {
		case 1:
			alterTeam(team1, size1);
			break;
		case 2:
			alterTeam(team2, size2);
			break;
		case 3: //Reloads Teams
			cout << "\n---------------------------------------------------------\n";
			cout << "\nWARNING: Reloading ALL teams from text files erases all current progress made so far!\nConsider exporting Team data first before proceeding.\n";
			
			char subSelection[MAX_SIZE];
			int subUserChoice;
			high = 2;
			do {
				cout << "\nProceed???\n\n"
					<< "1. YES\n"
					<< "2. NO\n\nYour selection: ";
				cin.getline(subSelection, MAX_SIZE);
			} while (entryFailed(subSelection, low, high, subUserChoice));

			if (subUserChoice == 1) {
				team1.eraseParty();
				team2.eraseParty();
				team1.loadTeam1();
				team2.loadTeam2();
				opsComplete();
			}
			else if (subUserChoice == 2) {
				returnToMenu;
			}
			break;
		case 4:
			cout << "\n---------------------------------------------------------\n";
			exportTeams(team1, team2);
			opsComplete();
			break;
		case 5:
			return; //Exits function to exit program
		}
	}
}

void introPrompt() //Self explanatory
{
	cout << "========== WELCOME TO DUNGEONS & DRAGONS TEAMBUILDER 1.0 ==========\n\n"
		<< "This programs helps you manage and edit your D&D groups party members.\n"
		<< "\nWe highly advise that you input your team's name and characters' stats\n"
		<< "into 'Team1.txt' and 'Team2.txt' before continuing.\n\n"
		<< "Any time you see '...' the program stalled. Press [ENTER] to contine!\n\n";
	cout << "===================================================================\n\n...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nLoading in 'Team1.txt' and 'Team2.txt'\n\n...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exitPrompt() //Self explanatory
{
	cout << "\n===================================================================\n\n";
	cout << "Thank you for using DUNGEONS & DRAGONS TEAMBUILDER 1.0, goodbye!!!\n\n...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
	Team team1; //Created 2 Team objects 
	Team team2;
	introPrompt();
	team1.loadTeam1(); //Loads intial Teams
	team2.loadTeam2();
	mainMenu(team1, team2); //This function branches off to all other function calls
	exitPrompt();
	return 0;
}