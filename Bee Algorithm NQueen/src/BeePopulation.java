import java.util.Random;

public class BeePopulation {
	static final int size = 10;
	static final int numberofBoards = 10;
	static int bestScore = 0;
	static int worstBoard = 0;
	static int bestBoard = 0;
	static double yield = 0;
	public static Random rand = new Random();
	Candidate candidate[] = new Candidate[numberofBoards];

	public class Candidate {
		int[][] board = new int[size][size];
		int fitnessScore = 0;

	}

	public BeePopulation() {
		int randomNumber = 0;
		for (int i = 0; i < numberofBoards; i++) {
			candidate[i] = new Candidate();
			for (int j = 0; j < size; j++) {
				randomNumber = rand.nextInt(size);
				candidate[i].board[j][randomNumber] = 1;

			}
			fitnessCheck(candidate[i]);

		}

	}

	// Check to see if a queen can be placed in a particular position
	static void fitnessCheck(Candidate candidate) {
		candidate.fitnessScore = 0;
		int step = 0;
		int column = 0;
		for (int i = 0; i < size; i++) {
			step = 0;
			while (candidate.board[i][step] != 1) {
				step++;
			}

			/* Check all attacking positions */
			// check upper left
			column = step - 1;
			for (int row = i - 1; row > 0; row--) {
				if (column < 0)
					break;
				if (candidate.board[row][column] == 1)
					candidate.fitnessScore++;
				column--;
			}
			// check lower left
			column = step - 1;
			for (int row = i + 1; row < size; row++) {
				if (column < 0)
					break;
				if (candidate.board[row][column] == 1)
					candidate.fitnessScore++;
				column--;
			}
			// check above
			for (int row = i - 1; row >= 0; row--) {
				if (candidate.board[row][step] == 1)
					candidate.fitnessScore++;
			}

			// check below
			for (int row = i + 1; row < size; row++) {
				if (candidate.board[row][step] == 1)
					candidate.fitnessScore++;
			}

			// check upper right
			column = step + 1;
			for (int row = i - 1; row >= 0; row--) {
				if (column == size)
					break;

				if (candidate.board[row][column] == 1)
					candidate.fitnessScore++;
				column++;
			}
			// check lower right
			column = step + 1;
			for (int row = i + 1; row < size; row++) {
				if (column == size)
					break;
				if (candidate.board[row][column] == 1)
					candidate.fitnessScore++;
				column++;
			}

		}
		// System.out.println("Candidate fitness score: " + candidate.fitnessScore);
	}

	// print the completed state of the board
	static void drawBoard(Candidate candidate) {
		System.out.println();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				System.out.print(candidate.board[i][j] + " ");
			}
			System.out.print("\n");
		}

	}

	// The function finds two metrics: the best (lowest) fitness score, and a factor
	// describing
	// the magnitude by which the best score is better than the average
	static void findBestScore(BeePopulation population) {
		bestScore = population.candidate[0].fitnessScore;
		int worstScore = population.candidate[0].fitnessScore;
		double averageScore = bestScore;

		for (int i = 1; i < numberofBoards; i++) {
			if (population.candidate[i].fitnessScore < bestScore) {
				bestScore = population.candidate[i].fitnessScore;
				bestBoard = i;
			}
			if (population.candidate[i].fitnessScore > worstScore) {
				worstScore = population.candidate[i].fitnessScore;
				worstBoard = i;
			}
			averageScore += population.candidate[i].fitnessScore;
		}
		averageScore /= numberofBoards;

		if (bestScore != 0)
			yield = averageScore / bestScore;
		// System.out.println("Average score: " + averageScore);
		// System.out.println("Best score: " + bestScore + "\nWorst score: " +
		// worstScore +"\nYield factor: " + yield);
		// System.out.println(averageScore + "/" + bestScore + " = " + yield);
	}

	// Use the yield value to determine how many agents should focus on the board of
	// the best value
	static void recruit(BeePopulation population) {
		double percentageYield = yield / 10;
		// System.out.println("Percentage yield: " + percentageYield);
		int agentsRecruited = (int) ((percentageYield * numberofBoards)) + 1;
		int worstScore = population.candidate[0].fitnessScore;
		// System.out.println("Agents recruited: " + agentsRecruited);
		while (agentsRecruited > 0) {
			for (int i = 1; i < numberofBoards; i++) {
				if (population.candidate[i].fitnessScore > worstScore) {
					worstScore = population.candidate[i].fitnessScore;
					worstBoard = i;
				}
			}
			population.candidate[worstBoard].board = population.candidate[bestBoard].board;
			agentsRecruited--;
		}

	}

	// each agent searches the solutions local to its current one
	static void searchLocally(BeePopulation population) {
		int randomNumber = 0;
		int boardID = 0;
		int step;

		// System.out.println("\nSearch locally...");
		while (boardID < numberofBoards) {
			for (int i = 0; i < size; i++) {
				step = 0;
				while (population.candidate[boardID].board[i][step] != 1) {
					step++;
				}
				randomNumber = rand.nextInt(2);
				if (randomNumber == 0) {
					population.candidate[boardID].board[i][step] = 0;
					if (step - 1 >= 0)
						population.candidate[boardID].board[i][step - 1] = 1;
					else
						population.candidate[boardID].board[i][step + 1] = 1;
				} else {
					population.candidate[boardID].board[i][step] = 0;
					if (step + 1 < size)
						population.candidate[boardID].board[i][step + 1] = 1;
					else
						population.candidate[boardID].board[i][step - 1] = 1;
				}
			}
			// drawBoard(population.candidate[boardID]);
			boardID++;
		}
	}

	// driver
	public static void main(String[] args) {
		int iterations = 1;
		int boardsMade = 0;
		BeePopulation population = new BeePopulation();
		findBestScore(population);

		long endTime = 0;
		long duration = 0;

		

		int solutionsFound = 0;
		double averageTime = 0;
		
//		while (solutionsFound < 6) {
//			population = new BeePopulation();
//			for (int i = 0; i < numberofBoards; i++) {
//				fitnessCheck(population.candidate[i]);
//			}
			long startTime = System.nanoTime();
			while (bestScore > 0) {
				recruit(population);
				searchLocally(population);
				for (int i = 0; i < numberofBoards; i++) {
					fitnessCheck(population.candidate[i]);
				}
				findBestScore(population);
				iterations++;
				if (iterations % 50 == 0) {
					population = new BeePopulation();
				}
			}
			endTime = System.nanoTime();
			duration = endTime - startTime;
			solutionsFound++;
			System.out.println("Attempt " + solutionsFound + " : " + (double)(duration/1_000_000_000.0) + " seconds.");
			averageTime += duration;
			
//		}

		averageTime /= solutionsFound;
		double seconds = (double) averageTime / 1_000_000_000.0;

		
		for (int i = 0; i < numberofBoards; i++) {
			drawBoard(population.candidate[i]);
			System.out.println("Candidate " + i + " fitness score: " + population.candidate[i].fitnessScore);
		}
		System.out.println("Worst board: " + worstBoard + "\nBest board: " + bestBoard);
		boardsMade = numberofBoards * iterations;
		System.out.println("\nIterations required: " + iterations + "\nBoards made: " + boardsMade);
		System.out.println("Average time to completion for " + solutionsFound + " attempts: " + seconds + " seconds.");
		System.out.println("Board size: " + size + " Number of boards: " + numberofBoards);
	}

}
