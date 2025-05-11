#define _SECURE_SCL_DEPRECATE 0
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class GChar
{

public:
	static const int DEFAULT_CAPACITY = 5;

	//constructor
	GChar(string name = "john", int capacity = DEFAULT_CAPACITY);

	//copy constructor
	GChar(const GChar& source);

	//Overload Assignment
	GChar& operator=(const GChar& source);

	//Destructor
	~GChar();

	//Insert a New Tool
	void insert(const std::string& toolName);

private:

	//data members
	string name;
	int capacity;
	int used;
	string* toolHolder;

};
//constructor
GChar::GChar(string n, int cap)
{
	name = n;
	capacity = cap;
	used = 0;
	toolHolder = new string[cap];
}
//copy constructor
GChar::GChar(const GChar& source) //"source" is the object referenced from class: GChar
{
	cout << "Copy Constructor Called." << endl;
	name = source.name;
	capacity = source.capacity;
	used = source.used;
	toolHolder = new string[source.capacity];
	copy(source.toolHolder, source.toolHolder + used, toolHolder);
}
//Overload Assignment
GChar& GChar::operator=(const GChar& source)
{
	cout << "Overload Assignment Called." << endl;
	//Check for self assignment
	//c1=c1
	if (this == &source)
	{
		return *this;
	}
	this->name = source.name;
	this->capacity = source.capacity;
	used = source.used;

	copy(source.toolHolder, source.toolHolder + used, this->toolHolder);
}
//Destructor
GChar::~GChar()
{
	cout << "Destructor called for " << this->name << " @ this memory location " << this << endl;
	delete[] toolHolder;
}

void GChar::insert(const string& toolName)
{
	unsigned int i;
	//Homework (3/19): make toolHolder bigger each time it gets full
	if (used == capacity)
	{
		cout << " The tool holder is full, Cannot add any additional tools!!!" << endl;
		
		cout << "Doubling the size of the toolHolder: .... [Press Enter to Continue]" << endl;
		cin.get();
		//
		newArray = new string[capacity * 2];
		for (i = 0; i < (capacity); i++) {
			newArray[i] = toolHolder[i];
		}
	}
	else
	{
		toolHolder[used] = toolName;
		used++;
	}
}

int main()
{
	GChar gc1;
	gc1.insert("potion");
	gc1.insert("crossbow");
	gc1.insert("candle");
	gc1.insert("cloak");
	gc1.insert("sword");
	gc1.insert("book of spells");

	GChar gc2("Bob", 5);

	//Line of code below is "Overloading" gc3 by referencing gc2 => GChar& operator=(const GChar& source);
	GChar gc3 = gc2;

	return 0;
}