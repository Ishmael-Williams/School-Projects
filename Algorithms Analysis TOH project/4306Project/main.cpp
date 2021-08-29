#include <stdio.h>
#include "TowerOfHanoi.h"
#include <math.h> //for pow() function 
#include <iostream>
#include <chrono> //time tracking functions
#include <ctime> //CLOCKS_PER_SEC constant for converting clock ticks to micro seconds
using namespace std;



//Moves a disk from its source peg to its destination
void moveDisk(towerSet tset, int diskMoving, int source, int destination) {
	tset.moves++;
	diskMoves++;
	

	//While loop used to ensure values moved across arrays don't overwrite other values
	int i = 1;
	while (tset.pegs[destination].data[i] != 0) { i++; }

	//Once the topmost available position in an array is found, the disk is moved to that position
	tset.pegs[destination].data[i] = tset.pegs[source].data[diskMoving];

	//The value in previous position where the disk was is removed
	tset.pegs[source].data[diskMoving] = 0;

	//The amount of spaces used in each peg is updated to reflect the movement of a disk
	tset.pegs[destination].used++;
	tset.pegs[source].used--;

	tset.printState();
	

}



//The recursive version of the solution for the Tower of Hanoi puzzle
void recursiveSolution(towerSet tset, int problemSize, int source, int auxiliary, int destination) {

	//Derives which disk is moving in the current recursive step
	int diskToMove = tset.pegs[source].used - problemSize + 1;

	//if the amount of disks to move is 1, move the disk, otherwise more recursive steps are required
	if (problemSize > 1) {
		recursiveSolution(tset, problemSize - 1, source, destination, auxiliary); //This step moves the topmost n-1 disks so that the bottom disk may move to its destination
		moveDisk(tset, diskToMove, source, destination);
		recursiveSolution(tset, problemSize - 1, auxiliary, source, destination); //This step returns the topmost n-1 disks overtop the bottom disk once the bottom disk has moved

	}
	else {
		moveDisk(tset, diskToMove, source, destination);
	}

}


//The iterative version of the solution for the Tower of Hanoi puzzle
void iterativeSolution(towerSet tset) {
	int problemSize = tset.capacity;
	int source = 1, auxiliary = 2, destination = 3;
	
	int movesRequired = tset.movesRequired;
	int diskToMove = 0; //holds the index value of the disk to move from one peg to another
	int location1 = 0, location2 = 0; //these variables also hold the index value of the disk to move, which is ultimately passed to diskToMove

	/*
	 * If-else block below chooses an iterative approach based on whether the number of disks in the problem is even or odd.
	 * In either case a while loop completes a rolling sequence of legal operations between the 3 pegs until an
	 * amount of operations is made equal to the minimum amount required to solve the problem.
	*/

	if (problemSize % 2 == 0) {
		//if size of the problem is even
		cout << "\nAttempting solution for an even number of disks\n";

		while (tset.moves < movesRequired) {
			//make the legal move between 1 and 2

			//indexes in the source and destination peg are compared to find the smaller disk (position "used")
			//if a peg contains no disks it is given "1" as its position
			if (tset.pegs[source].used == 0) location1 = 1;
			else location1 = tset.pegs[source].used;

			if (tset.pegs[auxiliary].used == 0) location2 = 1;
			else location2 = tset.pegs[auxiliary].used;

			//The following if block attempts to place the smallest disk between two pegs on the other larger disk or simply place a disk over an empty peg
			if (tset.pegs[source].data[location1] < tset.pegs[auxiliary].data[location2] && tset.pegs[source].data[location1] != 0 || tset.pegs[auxiliary].data[location2] == 0) {
				diskToMove = location1;
				tset.moves++;
				moveDisk(tset, diskToMove, source, auxiliary);
			}
			else {
				diskToMove = location2;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, source);
			}
			if (tset.isSolved(movesRequired) == true) break; //end the while loop if the puzzle is solved before the next cycle of the while loop
			
			
			//make the legal move between 1 and 3
			if (tset.pegs[source].used == 0) location1 = 1;
			else location1 = tset.pegs[source].used;

			if (tset.pegs[destination].used == 0) location2 = 1;
			else location2 = tset.pegs[destination].used;

			if (tset.pegs[source].data[location1] < tset.pegs[destination].data[location2] && tset.pegs[source].data[location1] != 0 || tset.pegs[destination].data[location2] == 0) {
				diskToMove = location1;
				tset.moves++;
				moveDisk(tset, diskToMove, source, destination);
			}
			else {
				diskToMove = location2;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, source);
			}
			if (tset.isSolved(movesRequired) == true) break;

			
			//make the legal move between 2 and 3
			if (tset.pegs[auxiliary].used == 0) location1 = 1;
			else location1 = tset.pegs[auxiliary].used;

			if (tset.pegs[destination].used == 0) location2 = 1;
			else location2 = tset.pegs[destination].used;

			if (tset.pegs[auxiliary].data[location1] < tset.pegs[destination].data[location2] && tset.pegs[auxiliary].data[location1] != 0 || tset.pegs[destination].data[location2] == 0) {
				diskToMove = location1;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, destination);
			}
			else {
				diskToMove = location2;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, auxiliary);
			}
		}
	}
	else {
		//if size of the problem is odd. Identical to the even solution except for the order of the comparisons between pegs.
		cout << "\nAttempting solution for an odd number of disks\n";
		while (tset.moves < movesRequired) {
			
			//make the legal move between 1 and 3
			if (tset.pegs[source].used == 0) location1 = 1;
			else location1 = tset.pegs[source].used;

			if (tset.pegs[destination].used == 0) location2 = 1;
			else location2 = tset.pegs[destination].used;

			if (tset.pegs[source].data[location1] < tset.pegs[destination].data[location2] && tset.pegs[source].data[location1] != 0 || tset.pegs[destination].data[location2] == 0) {
				diskToMove = location1;
				tset.moves++;
				moveDisk(tset, diskToMove, source, destination);
			}
			else {
				diskToMove = location2;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, source);
			}
			if (tset.isSolved(movesRequired) == true) break;


			//make the legal move between 1 and 2
			if (tset.pegs[source].used == 0) location1 = 1;
			else location1 = tset.pegs[source].used;

			if (tset.pegs[auxiliary].used == 0) location2 = 1;
			else location2 = tset.pegs[auxiliary].used;

			if (tset.pegs[source].data[location1] < tset.pegs[auxiliary].data[location2] && tset.pegs[source].data[location1] != 0 || tset.pegs[auxiliary].data[location2] == 0 ) {
				diskToMove = location1;
				tset.moves++;
				moveDisk(tset, diskToMove, source, auxiliary);
			}
			else {
				diskToMove = location2;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, source);
			}
			if (tset.isSolved(movesRequired) == true) break;
			

			//make the legal move between 2 and 3
			if (tset.pegs[auxiliary].used == 0) location1 = 1;
			else location1 = tset.pegs[auxiliary].used;
			
			if (tset.pegs[destination].used == 0) location2 = 1;
			else location2 = tset.pegs[destination].used;

			if (tset.pegs[auxiliary].data[location1] < tset.pegs[destination].data[location2] && tset.pegs[auxiliary].data[location1] != 0 || tset.pegs[destination].data[location2] == 0) {
				diskToMove = location1;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, destination);
			}
			else {
				diskToMove = location2;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, auxiliary);
			}
		}
	}
}

//Takes the given Hanoi set and an integer, 1 or 2, to determine which solution type to implement.
void tohSolver(towerSet tset, int solutionType) {
	
	if (solutionType == 1) {
		recursiveSolution(tset, tset.capacity, 1, 2, 3);
	}
	else if (solutionType == 2) {
		iterativeSolution(tset);
	}
	
	
}


//Run attempts at solving the Hanoi problem
int main(int argc, char** argv)
{
	printf("Tower of Hanoi \n");
	double testTimes = 0; //holds the microseconds of the recursive and iterative solutiosn respectively
	double testTicks = 0; //holds the clock ticks ofs both solutions
	

	//Setup the Tower of Hanoi objects that will be used to run tests for both solution types
	int disks = 3;
	towerSet t1(disks);
	
	
	
	//Run Tower of Hanoi tests by printing the new puzzle, implementing a solution and tracking the duration, then printing the completed puzzle
	t1.printState();
	auto start = chrono::high_resolution_clock::now();
	tohSolver(t1, 2);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = (stop - start);

	testTimes = (duration.count() / CLOCKS_PER_SEC);
	testTicks = duration.count();

	
	
	//Print the results of the ticks and microseconds of both types of solutions
	cout << "\n\n--------Analysis--------\n";
	cout << "  Clock ticks: " << testTicks << "\nMicro Seconds: " << testTimes << "\n      Seconds: " << testTimes/pow(10,6) << endl;
	
				
	return 0;
}
