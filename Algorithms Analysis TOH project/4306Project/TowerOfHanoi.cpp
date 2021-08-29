//Definition file for the TOH.h header file

#include <cstdlib>
#include <iostream>
#include "TowerOfHanoi.h"
#include "math.h" //pow(x,y) function
using namespace std;

//Destructor
towerSet::~towerSet() {
}

//Default constructor, defines the pegs of the Tower of Hanoi problem according to the amount of disks to solve for
towerSet::towerSet(int problemSize) {
	capacity = problemSize;
	pegs = new peg[3];

	//The array of pegs indexes at 1 instead of 0. I don't currently understand this behavior but using peg[0] causes the program to fail and peg[3] does not.
	pegs[1].data = new int[capacity + 2];
	pegs[2].data = new int[capacity + 2];
	pegs[3].data = new int[capacity + 2];
	moves = 0;
	movesRequired = pow(2, capacity) - 1;
	pegs[1].used = capacity;
	pegs[2].used = 0;
	pegs[3].used = 0;

	/*
	 * The first (source) peg is populated with numbers corresponding to disks. The largest disk corresponds to the largest number,
	 * which is also the total amount of disks in the problem.
	 * The remaining pegs are provided with zeros that represent empty peg space
	 */
	for (int i = capacity+2; i > 0; i--) {
		pegs[1].data[capacity - i + 1] = i;
		pegs[2].data[i] = 0;
		pegs[3].data[i] = 0;

	}


}

//Resets the tower set as if it were newly created in the constructor
void towerSet::reset()
{
	diskMoves = 0;
	moves = 0;
	pegs[1].used = capacity;
	pegs[2].used = 0;
	pegs[3].used = 0;
	for (int i = capacity; i > 0; i--) {
		pegs[1].data[capacity - i + 1] = i;
		pegs[2].data[i] = 0;
		pegs[3].data[i] = 0;

	}
}

//Determines whether the Hanoi set has been solved by comparing the moves made against the moves required. 
//The iterative solution uses this to know when to stop, the recursive solution does not require this info.
bool towerSet::isSolved(double movesRequired) {
	if (moves == movesRequired)
		return true;

	return false;
}

//Print the current state of the Tower of Hanoi set in terms of the pegs and where the disks are on the pegs.
void towerSet::printState() const {
	/*
	   - unfortunately, to track the number of moves made in the recursive solution the global variable diskMoves is incremented here
	     rather than in the moveDisk() function where the actual movement occurs. 
	   - This function will skew the amount of moves made in the puzzle if called more or less times than moveDisk()
	*/

	diskMoves++;
	if (moves == 0) diskMoves = 0;
	cout << "\nDisk moves: " << diskMoves << "/" << movesRequired; 
	cout << "\n -------------------------------\n";
	cout << "| peg 1      peg 2      peg 3  |\n";
	cout << "|                              |\n";

	for (size_t i = capacity; i > 0; i--) {
		cout << "|   " << pegs[1].data[i] << "          " << pegs[2].data[i] << "          " << pegs[3].data[i] << "    |" << endl;
	}
	cout << " -------------------------------\n";

}

