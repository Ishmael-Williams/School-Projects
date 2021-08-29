#include <stdio.h>
#include "set.h"
#include <iostream>
using namespace std;
using namespace assignment5;

int main(int argc, char **argv)
{
	set *set1 = new set();
	cout << "insert 1 into a set\n";
	set1->insert(1);
	
	cout << "Search the set for 1... ";
	if (set1->contains(1) == true){
		cout << "1 was found in the set\n";
	}
	
	cout << "insert 2 into the set\n";
	set1->insert(2);
	cout << "Print the set: ";
	set1->printSet();
	
	cout << "Make a new set with an overloaded constructor:";
	set *set2 = set1;
	cout << "\nPrint the copied set: ";
	set2->printSet();
	cout << "Make a new set with the overloaded assignment operator: ";
	set *set3 = set2;
	cout << "\nPrint set 3: ";
	set3->printSet();
	cout << "Remove 2 from set 3 and print it";
	set3->erase(2);
	cout << endl << "Set 3: ";
	set3->printSet();
	cout << "Get the complement of set 3 and set 2";
//	set1 = set1->complement(set3);
//	set1 = set2+set3;
//	set1 = set::intersection(set2,set3);

	set1->size();

	
	return 0;
}
