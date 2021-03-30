
#include <iostream>
#include <assert.h>
#include "Data.h"

/*
Create object containing 300 items.
Use methods PrintAll() and CountItems() to check the created object.
*/
void testCase1() {

	int n = 5;
	Data data = Data(n);
	data.PrintAll();

	assert(data.CountItems() == n);

}



int main()
{
	testCase1();

}
