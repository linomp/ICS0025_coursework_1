#pragma once

#include <map>
#include <list>
#include <initializer_list>
#include "Item.h";

class Data
{
private:
	// ** Interpretation of the type **
	// map with:
	//			key = char
	//			value = pointer to map with:
	//										key = int
	//										value = pointer to list of pointers to Item
	std::map<char, std::map<int, std::list<Item*>*>*> DataStructure;

public:
	// Constructs the object with empty container;
	Data();

	// Constructs the object and fills the container with n random items
	Data(int n);

	// Destructs the object and releases all the memory occupied by the container and the items in it.
	~Data();

	// Prints all the items stored in the container in command prompt window in easily readable format.
	void PrintAll();

	// Returnsthe total number of items in the container.
	int CountItems();

	// Creates and inserts the specified item. Returns the pointer to new item. 
	// If the specified item already exists or the input parameters are not correct, returns nullptr.
	// If necessary, creates the missing group and subgroup.
	Item* InsertItem(char c, int i, std::string s, Date d);

	std::list<Item*>* InsertSubgroup(char s, int i, std::initializer_list<Item*> items);

	std::map<int, std::list<Item*>*>* InsertGroup(char c, std::initializer_list<int> subgroups, std::initializer_list<std::initializer_list<Item*>> items);
};

