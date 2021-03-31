
#include <iostream>
#include <assert.h>
#include "Data.h"

// Test empty container creation
void testEmpty() {
	Data data = Data();
	data.PrintAll();

	assert(data.CountItems() == 0);
}

/*
Create object containing 300 items.
Use methods PrintAll() and CountItems() to check the created object.
*/
void testCase1() {
	int n = 300;
	Data data = Data(n);
	data.PrintAll();

	assert(data.CountItems() == n);
}

/*
Select a group. 
Condition: there must be at least one subgroup containing at least two items.
Apply methods PrintGroup() and CountGroupItems() for the selected group
*/
void testCase2() {
	Data data = Data();

	Date d = Date(1, 1, 2021);
	
	data.InsertItem('A', 0, "itemA0", d);
	data.InsertItem('B', 0, "itemB0", d);
	data.InsertItem('B', 1, "itemB1", d);

	data.PrintGroup('A');
	data.PrintGroup('B');

	assert(data.CountItems() == 3);
	assert(data.CountGroupItems('A') == 1);
	assert(data.CountGroupItems('B') == 2);
}

/*
From the selected group select a subgroup containing at least two items. 
Apply methods PrintSubgroupByNames(), PrintSubgroupByDates() and CountSubgroupItems() 
for the selected subgroup
*/
void testCase3() {
	Data data = Data();

	Date d = Date(1, 1, 2021);

	data.InsertItem('A', 0, "itemA0", d);
	data.InsertItem('B', 0, "itemB00", d);
	data.InsertItem('B', 0, "itemB01", d);
	data.InsertItem('B', 0, "itemB02", d);
	
	data.PrintAll();
}

int main()
{
	testEmpty();
	testCase1();
	testCase2();
	testCase3();
	//testCase4();
	//testCase5();
	
	//testCase7();
	//testCase8();
	//testCase9();
	//testCase10();
	//testCase11();

	//testCase12();
	//testCase13();
	//testCase14();
	//testCase15();
}
