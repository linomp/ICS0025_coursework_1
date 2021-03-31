
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

	data.InsertItem('B', 0, "z", Date(1, 1, 2021));
	data.InsertItem('B', 0, "b", Date(1, 3, 2021));
	data.InsertItem('B', 0, "c", Date(1, 2, 2021));
	
	data.PrintSubgroupByNames('B', 0);
	data.PrintSubgroupByDates('B', 0);
	
	assert(data.CountSubgroupItems('B', 0) == 3);
}

/*
From the selected group select a subgroup containing only one item. 
Apply methods PrintSubgroupByNames(), PrintSubgroupByDates() and CountSubgroupItems()
for the selected subgroup.
*/
void testCase4() {
	Data data = Data();

	data.InsertItem('B', 0, "z", Date(1, 1, 2021));
	data.InsertItem('B', 0, "b", Date(1, 3, 2021));
	data.InsertItem('B', 0, "c", Date(1, 2, 2021));
	data.InsertItem('B', 1, "d", Date(1, 2, 2021));

	data.PrintSubgroupByNames('B', 1);
	data.PrintSubgroupByDates('B', 1);

	assert(data.CountGroupItems('B') == 4);
	assert(data.CountSubgroupItems('B', 1) == 1);
}

/*
Apply methods PrintSubgroupByNames(), PrintSubgroupByDates() and CountSubgroupItems()
for a non-existing subgroup.
*/
void testCase5() {
	Data data = Data();

	data.InsertItem('B', 0, "z", Date(1, 1, 2021));
	data.InsertItem('B', 0, "b", Date(1, 3, 2021));
	data.InsertItem('B', 0, "c", Date(1, 2, 2021));
	data.InsertItem('B', 1, "d", Date(1, 2, 2021));

	try {
		data.PrintSubgroupByNames('B', 5); // non-existing subgroup
		assert(false); // Force test failure if exception is not thrown
	}
	catch (const std::exception& e) { 
		std::cout << e.what(); 
	}

	try {
		data.PrintSubgroupByDates('B', 5);  // non-existing subgroup
		assert(false); // Force test failure if exception is not thrown
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}

	assert(data.CountSubgroupItems('B', 5) == 0);

}


/*
Apply method PrintItem() for an existing item and for a non-existing item
*/
void testCase6() {
	Data data = Data();

	data.InsertItem('A', 0, "a0", Date(1, 1, 2021)); 

	data.PrintItem('A', 0, "a0");

	try {
		data.PrintItem('A', 0, "NO NAME");  // non-existing item
		assert(false); // Force test failure if exception is not thrown
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
}

/*
Create object containing 30 itemsand apply method PrintAll().
*/
void testCase7() { 
	Data data = Data(30);
	data.PrintAll();
}

/*
Apply methods PrintGroup() and CountGroupItems() for a non-existing group
*/
void testCase8() {
	Data data = Data();

	data.InsertItem('B', 0, "z", Date(1, 1, 2021));
	data.InsertItem('B', 0, "b", Date(1, 3, 2021));

	try {
		data.PrintGroup('Z'); // non-existing group
		assert(false); // Force test failure if exception is not thrown
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}

	assert(data.CountGroupItems('Z') == 0);
}

/*
* Apply method InsertItem() if:
*/ 
void testCase9() {
	Data data = Data();

	// a.The new item will be a member of an existing group and an existing subgroup.
	data.InsertItem('B', 0, "b0", Date(1, 1, 2021));
	data.InsertItem('B', 0, "b1", Date(1, 3, 2021));
	assert(data.CountGroupItems('B') == 2);

	// b.The new item will be a member of an existing group but the subgroup does not exist.
	data.InsertItem('B', 5, "b1", Date(1, 3, 2021));
	
	assert(data.CountGroupItems('B') == 3);
	assert(data.CountSubgroupItems('B', 5) == 1);

    // c.The new item will be a member of a non - existing group.
	data.InsertItem('C', 0, "c0", Date(1, 3, 2021));
	assert(data.CountItems() == 4);

	// d.This item already exists.
	Item* newItem = data.InsertItem('C', 0, "c0", Date(1, 3, 2021));
	assert(data.CountItems() == 4); // count should remain the same
	assert(!newItem); // should be nullptr

	// e.Apply method PrintAll() to check the results.
	data.PrintAll();
}

/*
* Apply method InsertSubgroup() if:
*/
void testCase10() {
	Data data = Data();

	// a.The new subgroup will be a member of an existing group.
	data.InsertItem('A', 0, "a0", Date(1, 1, 2021));
	auto newSubgroup1 = data.InsertSubgroup('A', 2, {});
	assert(newSubgroup1); // should not be nullptr

	// b.The new subgroup will be a member of a non - existing group.
	Item* newItem = new Item('B', 0, "b0", Date(1, 1, 2021));
	Item* newItem2 = new Item('B', 0, "b1", Date(1, 1, 2021));
	auto newSubgroup2 = data.InsertSubgroup('B', 0, { newItem, newItem2 });
	assert(newSubgroup2); // should not be nullptr
	assert(data.CountSubgroupItems('B', 0) == 2);

	// c.The subgroup already exists.
	auto newSubgroup3 = data.InsertSubgroup('B', 0, { });
	assert(!newSubgroup3); // should be nullptr
	assert(data.CountSubgroupItems('B', 0) == 2); // existing should not be changed

	// d.Apply method PrintAll() to check the results.
	data.PrintAll();
}

int main()
{/*
	testEmpty();
	testCase1();
	testCase2();
	testCase3();
	testCase4();
	testCase5();
	testCase6();
	testCase7();
	testCase8();
	testCase9();
	testCase10();
	*/

		//testCase11();
	
		//testCase12(); // create 100?
		
		//testCase13();
		//testCase14();
		//testCase15();
}
