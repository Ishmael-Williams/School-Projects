//Tower of Hanoi solver including iterative and recursive solutions

#ifndef _TOH_H_
#define _TOH_H_

#include <cstdlib>
#include <iostream> 
using namespace std;


 
static int diskMoves = 0; // global variable keeping track of which step of solving Hanoi the program is at


/*3 Peg objects are created per Tower of Hanoi set. Each peg contains a dynamic array (called data) sized just large enough
	for the amount of disks in the set. "used" contains an integer of how many disks are currently seated in the given peg.
*/
class peg{
	public:
		int *data;
		int used;
		~peg(){ delete[] data;}
		};

/*
  A towerSet object simulates a standard Tower of Hanoi set containing 3 pegs.
 */
class towerSet
{
	public:
		towerSet(int capacity);
		~towerSet();
		
		//print current state of the disks on the pegs
		void printState() const;
		
		//Tracks whether the Hanoi set has been solved
		bool isSolved (int movesRequired);
		
		int movesRequired;
		
		//3 dynamic arrays are used to represent the pegs of the Tower of Hanoi puzzle
		peg *pegs;
		
		//Tracks the amount of moves the Hanoi set has currently made in an attempt to solve the puzzle
		int moves;
		
		//Holds the value of the amount of disks in the current Tower of Hanoi set. This determines the size of the arrays making each peg.
		size_t capacity;
		
		
};

#endif