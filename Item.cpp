#include "Item.h"
#include "RandomUtils.h"

#include <random>
#include <string.h>

Item::Item() 
{
	std::default_random_engine generator;
	RandomUtils random(generator);

	Group = random.getRandomGroup();
	Subgroup = random.getRandomSubgroup();
	Name = random.getRandomName();
	Timestamp = random.getRandomTimestamp();
}

Item::Item(const Item& Original)
{ // copy constructor
	Group = Original.Group;
	Subgroup = Original.Subgroup;
	Timestamp = Original.Timestamp;
	Name.assign(Original.Name);
}

// TODO what to destroy?
Item::~Item()
{
	
}

Item::Item(char group, int subgroup, std::string name, Date date) 
{
	Group = group;
	Subgroup = subgroup;
	Name.assign(name);
	Timestamp = Date(date);
}

std::string Item::ToString() const 
{
	return Name + " " + Timestamp.ToString();
}

int Item::getSubgroup() const 
{
	return Subgroup;
}