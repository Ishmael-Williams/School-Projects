#include <stdio.h>
#include "TOH.h"
#include <math.h> //for pow() function 
#include <iostream>
//#include <chrono> //time tracking functions
using namespace std;



//Moves a disk from its source peg to its destination
void moveDisk(towerSet tset, int diskMoving, int source, int destination){
	tset.moves++;
	
	cout << "\n*******************************************\n";
	
	//While loop used to ensure values moved across arrays don't overwrite other values
	int i = 1;
	while ( tset.pegs[destination].data[i] != 0){ i++;}
	
	//Once the topmost available position in an array is found, the disk is moved to that position
	tset.pegs[destination].data[i] = tset.pegs[source].data[diskMoving];
	
	//The value in previous position where the disk was is removed
	tset.pegs[source].data[diskMoving] = 0;
	
	//The amount of spaces used in each peg is updated to reflect the movement of a disk
	tset.pegs[destination].used++;
	tset.pegs[source].used--;
	
	tset.printState();
	if (tset.isSolved(tset.movesRequired) == true){
		cout << "\nThe puzzle has been solved\n";
//		delete (tset.pegs);
//		delete (tset.pegs[2].data);
//		delete (tset.pegs[3].data);
	}
	
}

//The recursive version of the solution for the Tower of Hanoi puzzle
void recursiveSolution(towerSet tset, int problemSize, int source, int auxiliary, int destination){
	
	//Derives which disk is moving in the current recursive step
	int diskToMove = tset.pegs[source].used - problemSize + 1;
	
	//if the amount of disks to move is 1, move the disk, otherwise more recursive steps are required
	if (problemSize > 1){
		recursiveSolution(tset, problemSize-1, source, destination, auxiliary); //This step moves the topmost n-1 disks so that the bottom disk may move to its destination
		moveDisk(tset, diskToMove, source, destination);
		recursiveSolution(tset, problemSize-1, auxiliary, source, destination ); //This step returns the topmost n-1 disks overtop the bottom disk once the bottom disk has moved
		
	} else {
		moveDisk(tset, diskToMove, source, destination);
	}

}


//The iterative version of the solution for the Tower of Hanoi puzzle
void iterativeSolution(towerSet tset){
	int problemSize = tset.capacity;
	int source = 1, auxiliary = 2, destination = 3;
	int diskToMove = 0;
	int movesRequired = tset.movesRequired;
	/*
	 * If-else block below chooses an iterative approach based on whether the number of disks in the problem is even or odd.
	 * In either case a while loop completes a rolling sequence of legal operations between the 3 pegs until an
	 * amount of operations is made equal to the minimum amount required to solve the problem.
	*/
	
	if (problemSize%2 == 0){
	//if size of the problem is even
		cout << "\nAttempting solution for an even number of disks\n";
		//pow(2,problemSize)-1 expresses the minimum amount of moves required for the amount of disks in the problem
		
		while (tset.moves < movesRequired){
			
			//make the legal move between 1 and 2
			if (tset.pegs[source].data[tset.pegs[source].used] < tset.pegs[auxiliary].data[tset.pegs[auxiliary].used]){
				diskToMove = tset.pegs[source].used;
				tset.moves++;
				moveDisk(tset, diskToMove, source, auxiliary);
			} else {
				diskToMove = tset.pegs[auxiliary].used;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, source);
			}
			if (tset.isSolved(movesRequired) == true) break;
			
			//make the legal move between 1 and 3
			if (tset.pegs[source].data[tset.pegs[source].used] < tset.pegs[destination].data[tset.pegs[destination].used]){
				diskToMove = tset.pegs[source].used;
				tset.moves++;
				moveDisk(tset, diskToMove, source, destination);
			} else {
				diskToMove = tset.pegs[destination].used;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, source);
			}
			if (tset.isSolved(movesRequired) == true) break;
			
			//make the legal move between 2 and 3
			if (tset.pegs[auxiliary].data[tset.pegs[auxiliary].used] < tset.pegs[destination].data[tset.pegs[destination].used]){
				diskToMove = tset.pegs[auxiliary].used;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, destination);
			} else {
				diskToMove = tset.pegs[destination].used;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, auxiliary);
			}
		}
	} else {
		//if size of the problem is odd
		cout << "\nAttempting solution for an odd number of disks\n";
		while (tset.moves < movesRequired){
			//make the legal move between 1 and 3
			if (tset.pegs[source].data[tset.pegs[source].used] < tset.pegs[destination].data[tset.pegs[destination].used]){
				diskToMove = tset.pegs[source].used;
				tset.moves++;
				moveDisk(tset, diskToMove, source, destination);
			} else {
				diskToMove = tset.pegs[destination].used;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, source);
			}
			if (tset.isSolved(movesRequired) == true) break;
			
			//make the legal move between 1 and 2
			if (tset.pegs[source].data[tset.pegs[source].used] < tset.pegs[auxiliary].data[tset.pegs[auxiliary].used]){
				diskToMove = tset.pegs[source].used;
				tset.moves++;
				moveDisk(tset, diskToMove, source, auxiliary);
			} else {
				diskToMove = tset.pegs[auxiliary].used;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, source);
			}
			
			if (tset.isSolved(movesRequired) == true) break;
			//make the legal move between 2 and 3
			if (tset.pegs[auxiliary].data[tset.pegs[auxiliary].used] < tset.pegs[destination].data[tset.pegs[destination].used]){
				diskToMove = tset.pegs[auxiliary].used;
				tset.moves++;
				moveDisk(tset, diskToMove, auxiliary, destination);
			} else {
				diskToMove = tset.pegs[destination].used;
				tset.moves++;
				moveDisk(tset, diskToMove, destination, auxiliary);
			}
		}
	}
}

//Takes the given Hanoi set and an integer, 1 or 2, to determine which solution type to implement.
void tohSolver(towerSet tset, int solutionType){
		if (solutionType == 1){
			recursiveSolution(tset, tset.capacity, 1, 2, 3);
		}
		else if (solutionType == 2){
			iterativeSolution(tset);
		}
}


//Running 1 attempt at solving the Hanoi problem
int main(int argc, char **argv)
{
	printf("Tower of Hanoi \n");
	towerSet t2(1);
	towerSet t1(7);
	cout << "Total moves required to solve: " << t1.movesRequired << endl;
	tohSolver(t1, 2);
	
//	long start = high_resolution_clock::now();
//	long stop = high_resolution_clock::now();
//	auto duration = duration_cast<microseconds>(stop - start);
	t1.towerSet::~towerSet();
	
	return 0;
}
	