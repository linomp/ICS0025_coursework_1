#include "Item.h"
#include "Date.h"


Item::Item() {
		
	Group = 'A'; // TODO randomize 'A'...'Z'
	Subgroup = 0; // TODO randomize 0...99
	Name = "name"; // TODO get random name from file
	
    // TODO randomize Date params
	Timestamp = Date::CreateRandomDate(Date(1, 1, 2019), Date(1, 1, 2020));

}

Item::Item(char group, int subgroup, std::string name, Date date) {
	Group = group;
	Subgroup = subgroup; 
	Name.assign(name);
	Timestamp = Date(date);
}

std::string Item::ToString() const {
	return Name + " " + Timestamp.ToString();
}

int Item::getSubgroup() const {
	return Subgroup;
}