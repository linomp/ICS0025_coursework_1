#include "Data.h"
#include "Item.h"
#include "RandomUtils.h"

#include <iostream>
#include <map>
#include <algorithm>

Data::Data()
{
}

Data::Data(int n)
{
	std::default_random_engine generator;
	RandomUtils random(generator);

	for (int i = 0; i < n; i++) { 
		char group = random.getRandomGroup();
		int subgroup = random.getRandomSubgroup();
		std::string name = random.getRandomName();
		Date d = random.getRandomTimestamp();

		InsertItem(group, subgroup, name, d);
	}
}

Data::~Data()
{
	
	for (auto& outerMapIt : DataStructure) {

		for (auto& innerMapIt : *outerMapIt.second) {
			for (auto& it3 : *innerMapIt.second) {
				// deallocate every element of the list
				delete it3;
			}
			// deallocate the list
			std::cout << "destroying Subgroup \"" << innerMapIt.first << '\"' << std::endl;
			delete innerMapIt.second;
		}
		// deallocate the inner map
		std::cout << "destroying Group \"" << outerMapIt.first << '\"' << std::endl;
		delete outerMapIt.second;
	}
	
	// map itself is in stack
	DataStructure.clear(); // TODO neccesary?
}

Item* Data::InsertItem(char c, int i, std::string s, Date d) 
{
	auto it = DataStructure.find(c);

	Item* newItem = new Item(c, i, s, d);

	if (it != DataStructure.end()) { // group exists
		auto group = it->second;
		auto subgroupIt = group->find(i);

		if (subgroupIt != group->end()) { // subgroup exists
			subgroupIt->second->push_back(newItem); 
		}
		else
		{
			InsertSubgroup(c, i, { newItem });
		}
	}
	else {
		InsertGroup(c, { i }, { { newItem } });
	}

	return newItem;
}

std::list<Item*>* Data::InsertSubgroup(char s, int i, std::initializer_list<Item*> items) 
{
	auto groupIt = DataStructure.find(s);
	groupIt->second->emplace(i, new std::list<Item*>(items) );

	return groupIt->second->find(i)->second;
}

std::map<int, std::list<Item*>*>* Data::InsertGroup(char c, std::initializer_list<int> subgroupKeys, std::initializer_list<std::initializer_list<Item*>> items) 
{
	std::map<int, std::list<Item*>*>* group = new std::map<int, std::list<Item*>*>();

	for (int sg : subgroupKeys) {
		std::list<Item*>* newSubgroup = new std::list<Item*>(); // empty subgroup
		for (auto itemList : items) {
			for (Item* item : itemList) {
				if (item->getSubgroup() == sg) {
					newSubgroup->push_back(item); // fill with corresponding items
				}
			}
		}
		group->emplace(sg, newSubgroup);  // insert subgroup
	}
	DataStructure.emplace(c, group);  // insert group
	return group;
}

void Data::PrintAll() 
{
	auto print = [](const Item* item) { std::cout << "  - " << item->ToString() << std::endl; };

	for (auto it = DataStructure.cbegin(); it != DataStructure.cend(); ++it) {
		auto group = it->second;
		std::cout << it->first << ':' << std::endl; // print group key

		for (auto inner_it = group->cbegin(); inner_it != group->cend(); ++inner_it) {
			std::cout << " " << inner_it->first << ':' << std::endl; // print subgroup key

			// print items under subgroup
			std::for_each(inner_it->second->cbegin(), inner_it->second->cend(), print);
		}

		std::cout << std::endl << std::endl;
	}
}

int Data::CountItems() 
{
	int totalSize = 0;
	for (auto it = DataStructure.cbegin(); it != DataStructure.cend(); ++it) {
		auto subgroup = it->second;
		for (auto inner_it = subgroup->cbegin(); inner_it != subgroup->cend(); ++inner_it) {
			totalSize += inner_it->second->size();
		}
	}

	return totalSize;
}

std::map<int, std::list<Item*>*>* Data::GetGroup(char c)
{
	auto groupIt = DataStructure.find(c);
	if (groupIt != DataStructure.end()) { // group exists
		return groupIt->second;
	}

	return nullptr;
}

void Data::PrintGroup(char c)
{
	auto group = GetGroup(c);
	if (!group) {
		throw std::invalid_argument("Group not found!");
	}

	auto print = [](const Item* item) { std::cout << "  - " << item->ToString() << std::endl; };

	std::cout << c << ':' << std::endl; // print group

	for (auto inner_it = group->cbegin(); inner_it != group->cend(); ++inner_it) {
		std::cout << " " << inner_it->first << ':' << std::endl; // print subgroup

		// print items under subgroup
		std::for_each(inner_it->second->cbegin(), inner_it->second->cend(), print);
	}

	std::cout << std::endl << std::endl; // print group 
}

int Data::CountGroupItems(char c)
{
	auto group = GetGroup(c);
	if (!group) {
		throw std::invalid_argument("Group not found!");
	}

	int totalSize = 0; 
	for (auto inner_it = group->cbegin(); inner_it != group->cend(); ++inner_it) {
		totalSize += inner_it->second->size();
	} 

	return totalSize;
}


std::list<Item*>* Data::GetSubgroup(char c, int i) {
	return nullptr;
}

void Data::PrintSubgroupByNames(char c, int i) {
}

void Data::PrintSubgroupByDates(char c, int i) {
}

int Data::CountSubgroupItems(char c, int i) {
	return 0;
}
