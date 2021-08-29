import java.util.Random;

/* Objects of the type Population contain all information required
 *  to logically represent and solve the NQueen problem. This includes
 *  the candidate boards that are randomly generated, as well as their respective
 *  fitness scores to track how close they are to a solution.
 */
public class Population {
	public int[][] boards;
	public int[] fitnessScores;
	public int boardSize = 0;
	public int numberOfBoards = 0;

	// random number generator object
	public static Random rand = new Random();

	// For each board in the population, determine and store its score
	public static void fitnessCheck(Population population) {
		for (int i = 0; i < population.fitnessScores.length; i++) {
			population.fitnessScores[i] = 0;
		}
		/*
		 * For each queen, check the entire board for other queens it will attack.
		 * 
		 * Note the check is not completed on a two-dimensional board, but instead on a
		 * one-dimensional array of column positions, and the queen row positions are
		 * assumed to be the index of the array they came from.
		 */
		for (int i = 0; i < population.numberOfBoards; i++) {
			for (int j = 0; j < population.boardSize; j++) {
				int queenCol = population.boards[i][j];
				int colStep = 0; // an iteration variable to check through other queens
				int columnCheck = 0; // holds the value of the column position to check for attacking queens
	
				// Below are all the checks to complete for all angles a queen can attack on.
				// Same column check
				while (colStep < population.boardSize) {
					if (population.boards[i][colStep] == queenCol && colStep != j) {
						population.fitnessScores[i] = population.fitnessScores[i] + 1;
					}
	
					colStep++;
				}
	
				// Upper right diagonal check
				colStep = j;
				columnCheck = population.boards[i][j];
				while (colStep >= 0 && columnCheck <= population.boardSize) {
					if (population.boards[i][colStep] == columnCheck && colStep != j) {
						population.fitnessScores[i] += 1;
					}
	
					colStep--;
					columnCheck++;
				}
	
				// upper left diagonal check
				colStep = j;
				columnCheck = population.boards[i][j];
				while (colStep >= 0 && columnCheck > 0) {
					if (population.boards[i][colStep] == columnCheck && colStep != j) {
						population.fitnessScores[i] += 1;
					}
	
					colStep--;
					columnCheck--;
				}
	
				// lower right diagonal check
				colStep = j;
				columnCheck = population.boards[i][j];
				while (colStep < population.boardSize && columnCheck <= population.boardSize) {
					if (population.boards[i][colStep] == columnCheck && colStep != j) {
						population.fitnessScores[i] += 1;
					}
	
					colStep++;
					columnCheck++;
				}
	
				// lower left diagonal check
				colStep = j;
				columnCheck = population.boards[i][j];
				while (colStep < population.boardSize && columnCheck >= 1) {
					if (population.boards[i][colStep] == columnCheck && colStep != j) {
						population.fitnessScores[i] += 1;
					}
	
					colStep++;
					columnCheck--;
				}
			}
		}
	}

	public static void naturalSelection(Population population) {
		int parent1, parent2;
	
		// splice parents to make a new child board which will replace the weakest board
		for (int i = 0; i < population.numberOfBoards; i++) {
			parent1 = i;
			parent2 = i + 1;
			if (parent2 < population.numberOfBoards) {
				population.generateChild(parent1, parent2);
			}
		}
	
		// Mutate based on a 5% chance (generating a random number 0-19, and proceeding
		// with a mutation if the random number is 1
		int mutationProbability = rand.nextInt(20);
	
		if (mutationProbability == 1) {
			int sizeBound = population.boardSize;
			int boardBound = population.numberOfBoards;
			int randomBoard = rand.nextInt(boardBound);
			int randomPiece = rand.nextInt(sizeBound);
			population.boards[randomBoard][randomPiece] = rand.nextInt(sizeBound) + 1;
		}
	}

	public Population(int boardSize, int numberOfBoards) {
		this.boardSize = boardSize;
		this.numberOfBoards = numberOfBoards;
		boards = new int[numberOfBoards][boardSize];
		fitnessScores = new int[numberOfBoards];
		generateRandomBoards(this);
		drawBoards(this);
		fitnessCheck(this);
	}

	// Using two parents boards, create a child board made of each parent as
	// determined by a crossover point for the child
	public void generateChild(int parent1, int parent2) {
		int[] childBoard = new int[this.boardSize];
		int crossoverPoint = this.boardSize / 2;
		int elite = parent1;
		int nonelite = parent2;

		if (this.fitnessScores[parent2] > this.fitnessScores[parent1]) {
			elite = parent2;
			nonelite = parent1;
		}

		for (int i = 0; i < this.boardSize; i++) {
			if (crossoverPoint > 0) {
				childBoard[i] = this.boards[elite][i];
				crossoverPoint--;
			} else {
				childBoard[i] = this.boards[nonelite][i];
			}
		}

		// use the newly generated child to replace the board with the lowest fitness
		// score
		int lowestScore = this.fitnessScores[0];
		int weakestBoard = 0;
		for (int i = 1; i < this.numberOfBoards; i++) {
			if (this.fitnessScores[i] < lowestScore) {
				lowestScore = this.fitnessScores[i];
				weakestBoard = i;
			}
		}

		for (int i = 0; i < this.boardSize; i++) {
			this.boards[weakestBoard][i] = childBoard[i];
		}

	}

	// generate random board configurations for all boards
	public static void generateRandomBoards(Population population) {
		int upperbound = population.boardSize;
		for (int i = 0; i < population.numberOfBoards; i++) {
			for (int j = 0; j < population.boardSize; j++) {
				population.boards[i][j] = rand.nextInt(upperbound) + 1;
			}
		}
	}

	// output to the console what each of the chess boards looks like
	public static void drawBoards(Population population) {
		System.out.println("Boards\n-------------------");
		for (int i = 0; i < population.numberOfBoards; i++) {
			for (int j = 0; j < population.boardSize; j++) {
				int placement = population.boards[i][j];
				int step = 1;
				while (step <= population.boardSize) {
					if (step == placement)
						System.out.print("Q ");
					else
						System.out.print("- ");
					step++;
				}
				System.out.println();
			}
			System.out.println("\n");
		}

	}

	// Main driver that executes all functions necessary to solve the NQueen problem
	// It also tracks and displays to console the time required to find a solution
	public static void main(String[] args) {
		Population population = new Population(5, 4);
		boolean solutionFound = false;
		long startTime = System.nanoTime();
		long endTime = 0;
		long duration = 0;
		while (solutionFound == false) {
			naturalSelection(population);
			fitnessCheck(population);
			for (int i = 0; i < population.numberOfBoards; i++) {
				if (population.fitnessScores[i] == 0) {
					solutionFound = true;
				}
			}
		}
		endTime = System.nanoTime();
		duration = endTime - startTime;
		double seconds = (double) duration / 1_000_000_000.0;

		drawBoards(population);
		for (int i = 0; i < population.numberOfBoards; i++) {
			System.out.println("Fitness score for board " + (i + 1) + ": " + population.fitnessScores[i]);
		}
		System.out.println("Time to completion: " + seconds + " seconds.");

	}

}
