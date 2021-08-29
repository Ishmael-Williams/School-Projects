/*
	--------------------------------How the Tower of Hanoi puzzle is setup--------------------------------
	- 3 Peg objects are created per Tower of Hanoi object. Each peg contains a dynamic array "data" sized 
	  just large enough for the amount of disks in the set. "used" contains an integer of how many disks 
	  are currently seated in the given peg.

	- Recursive and iterative solutions are used

	! For reasons I don't understand, all indexing begins at 1 in this program instead of 0. Attempts 
	  to begin at 0 have caused the program to fail and values that would otherwise crash the program
	  (like calling array[4] in an array of size 4 that ends at array[3]) do *not* cause the program to fail
*/


#ifndef _TOH_H_
#define _TOH_H_

#include <cstdlib>
#include <iostream> 
using namespace std;

//Due to recursion a global variable is used to track the amount of moves made in an instance of the puzzle.
//Neither solution requires this variable
static long double diskMoves = 0; 


//The peg class simulates pegs in the Hanoi puzzle by using 3 dynamic arrays whose capacity are defined by arguments passed to the constructor.

class peg {
public:
	int* data;
	int used; //"used" tracks how many disks are on a given peg
	~peg() { delete[] data; }
};


/*
	A towerSet object simulates a standard Tower of Hanoi set containing 3 peg objects
	- printState()

*/
class towerSet
{
	public:
		//The constructor takes an argument that will define how many disks are in the puzzle
		towerSet(int capacity); 
		~towerSet();

		//print current state of the disks on the pegs
		void printState() const;
    
		//Reset the tower set
		void reset();

		//Tracks whether the Hanoi set has been solved
		bool isSolved(double movesRequired);
		
		//3 dynamic arrays are used to represent the pegs of the Tower of Hanoi puzzle
		peg* pegs;

		//Holds the value of the amount of disks in the current Tower of Hanoi set. This determines the size of the arrays defining each peg.
		size_t capacity;

		//Tracks the amount of moves the Hanoi set has currently made in an attempt to solve the puzzle
		double moves;

		//The minimum moves necessary to solve the puzzle defined in the constructor as pow(2,n)-1 where n = number of disks
		long double movesRequired;
};

#endif