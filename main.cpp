//Name: Christian Melendez
//SID: 862189972
//email: cmele014@ucr.edu
//Project 1: The Eight-Puzzle

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//TEST CASES
//Depth 0 (Reference)
vector<vector<int>> puzzle0 {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 0}
};

//Depth 2
vector<vector<int>> puzzle2 {
	{1, 2, 3},
	{4, 5, 6},
	{0, 7, 8}
};

//Depth 4
vector<vector<int>> puzzle4 {
	{1, 2, 3},
	{5, 0, 6},
	{4, 7, 8}
};

//Depth 8
vector<vector<int>> puzzle8 {
	{1, 3, 6},
	{5, 0, 2},
	{4, 7, 8}
};

//Depth 12
vector<vector<int>> puzzle12 {
	{1, 3, 6},
	{5, 0, 7},
	{4, 8, 2}
};

//Depth 16
vector<vector<int>> puzzle16 {
	{1, 6, 7},
	{5, 0, 3},
	{4, 8, 2}
};

//Depth 20
vector<vector<int>> puzzle20 {
	{7, 1, 2},
	{4, 8, 5},
	{6, 3, 0}
};

//Depth 24
vector<vector<int>> puzzle24 {
	{0, 7, 2},
	{4, 6, 1},
	{3, 5, 8}
};

//Empty Puzzle (Will Not Expand)
vector<vector<int>> emptyPuzzle {
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
};

//MISPLACED HEURISTIC
int misplacedHeuristic(vector<vector<int>> puzzle) {
	int numMisplaced = 0;

	//For each tile in puzzle
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//Add 1 if tile in puzzle != to reference
			if (puzzle[i][j] != puzzle0[i][j]) {
				numMisplaced++;
			}
		}
	}

	return numMisplaced;
}

//MANHATTAN DISTANCE
int manhattanDistance(vector<vector<int>> puzzle){
	int distance = 0;

	//For each tile in puzzle
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (puzzle[i][j] != 0) { //Don't calculate distance for the blank
				//Compare to each tile in reference
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						//Once found, add distance to total
						if (puzzle[i][j] == puzzle0[k][l])
							distance += abs(i - k) + abs(j - l); //Distance horizontally + vertically
					}
				}
			}
		}
	}

	return distance;
}

//PRINT PUZZLE
void printPuzzle(vector<vector<int>> puzzle) {
	for (int i = 0; i < puzzle.size(); i++) {
		cout << "| ";
		for (int j = 0; j < puzzle[i].size(); j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

//OPERATORS (RETURN BLANK SPACE IF ILLEGAL)
//Blank space up
vector<vector<int>> up(vector<vector<int>> puzzle, int row, int col) {
	if (row > 0) {
		puzzle[row][col] = puzzle[row - 1][col];
		puzzle[row - 1][col] = 0;
	} else {
		return emptyPuzzle;
	}
	return puzzle;
}

//Blank space down
vector<vector<int>> down(vector<vector<int>> puzzle, int row, int col) {
	if (row < 2) {
		puzzle[row][col] = puzzle[row + 1][col];
		puzzle[row + 1][col] = 0;
	} else {
		return emptyPuzzle;
	}
	return puzzle;
	
}

//Blank space left
vector<vector<int>> left(vector<vector<int>> puzzle, int row, int col) {
	if (col > 0) {
		puzzle[row][col] = puzzle[row][col - 1];
		puzzle[row][col - 1] = 0;
	} else {
		return emptyPuzzle;
	}
	return puzzle;
	
}

//Blank space right
vector<vector<int>> right(vector<vector<int>> puzzle, int row, int col) {
	if (col < 2) {
		puzzle[row][col] = puzzle[row][col + 1];
		puzzle[row][col + 1] = 0;
	} else {
		return emptyPuzzle;
	}
	return puzzle;
}

//NODE DATA STRUCTURE
struct node {
	//Each node is a puzzle
	vector<vector<int>> puzzle;

	//Depth of node
	int depth;

	//Heuristics
	int misplaced;
	int fn;

	//Create new node
	node(vector<vector<int>> newPuzzle, int newDepth) {
		puzzle = newPuzzle;
		depth = newDepth + 1;

		misplaced = depth + misplacedHeuristic(puzzle);
		fn = depth + manhattanDistance(puzzle);
	}
};

//Check if puzzle has been visited
bool isNotVisitedPuzzle(vector<vector<vector<int>>> visitedPuzzles, vector<vector<int>> puzzle) {
	for (int i = 0; i < visitedPuzzles.size(); i++) {
		if (puzzle == visitedPuzzles[i]) {
			return false;
		}
	}
	return true;
}

//Check if goal state is reached
bool isGoalState(vector<vector<int>> puzzle) {
	if (puzzle == puzzle0) {
		return true;
	} else {
		return false;
	}
}

//UNIFORM COST SEARCH (BREADTH-FRST SEARCH)
int uniformCostSearch(vector<vector<int>> puzzle) {
	int expandedNodes = 0;
	int depth = -1;
	int row, col;

	//Vector of visited puzzles
	vector<vector<vector<int>>> visitedPuzzles;

	//Make queue and create root with initial state
	queue<node*> tree;
	struct node* initialState = new node(puzzle, depth);
	tree.push(initialState);

	//Goal State is Initial State
	if (isGoalState(initialState->puzzle)) {
		cout << "Solution found at depth " << initialState->depth << endl;
		cout << "Total expanded nodes: " << expandedNodes << endl;
		return 0;
	}

	//While Loop
	while (true) {
		node* currentNode = tree.front();

		//Failure
		if (tree.empty()) {
			cout << "No solution" << endl;
			return 0;
		}

		//Determine where the blank space in the current puzzle is
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (currentNode->puzzle[i][j] == 0) {
					row = i;
					col = j;
				}
			}
		}

		/*Apply each move to the current node to make children
		Push only if move was legal and if not visited before*/

		//1st Child (Up)
		struct node* upNode = new node(up(currentNode->puzzle, row, col), currentNode->depth);
		if (upNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, upNode->puzzle)) {
			tree.push(upNode); //Push puzzle to back of queue
			visitedPuzzles.push_back(upNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(upNode->puzzle)) {
				cout << "Solution found at depth " << upNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//2nd Child (Down)
		struct node* downNode = new node(down(currentNode->puzzle, row, col), currentNode->depth);
		if (downNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, downNode->puzzle)) {
			tree.push(downNode); //Push puzzle to back of queue
			visitedPuzzles.push_back(downNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(downNode->puzzle)) {
				cout << "Solution found at depth " << downNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//3rd Child (Left)
		struct node* leftNode = new node(left(currentNode->puzzle, row, col), currentNode->depth);
		if (leftNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, leftNode->puzzle)) {
			tree.push(leftNode); //Push puzzle to back of queue
			visitedPuzzles.push_back(leftNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(leftNode->puzzle)) {
				cout << "Solution found at depth " << leftNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//4th Child (Right)
		struct node* rightNode = new node(right(currentNode->puzzle, row, col), currentNode->depth);
		if (rightNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, rightNode->puzzle)) {
			tree.push(rightNode); //Push puzzle to back of queue
			visitedPuzzles.push_back(rightNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(rightNode->puzzle)) {
				cout << "Solution found at depth " << rightNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		tree.pop();
	}
}

//A-STAR SEARCH (MANHATTAN DISTANCE HEURISTIC)
int AStarManhattanSearch(vector<vector<int>> puzzle) {
	int expandedNodes = 0;
	int depth = -1;
	int row, col;

	//Vector of visited puzzles
	vector<vector<vector<int>>> visitedPuzzles;

	//Make queue and create root with initial state
	queue<node*> newNodes;
	struct node* initialState = new node(puzzle, depth);

	//Goal State is Initial State
	if (isGoalState(initialState->puzzle)) {
		cout << "Solution found at depth " << initialState->depth << endl;
		cout << "Total expanded nodes: " << expandedNodes << endl;
		return 0;
	}

	//Frontier Vector Initialization
	vector<node*> frontier {initialState};

	//While Loop
	while (true) {
		node* currentNode = frontier.front();

		//Failure
		if (frontier.empty()) {
			cout << "No solution" << endl;
			return 0;
		}

		//Determine where the blank space in the current puzzle is
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (currentNode->puzzle[i][j] == 0) {
					row = i;
					col = j;
				}
			}
		}

		/*Apply each move to the current node to make children
		Push to new node tree only if move was legal and if not visited before*/
		//1st Child (Up)
		struct node* upNode = new node(up(currentNode->puzzle, row, col), currentNode->depth);
		if (upNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, upNode->puzzle)) {
			newNodes.push(upNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(upNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(upNode->puzzle)) {
				cout << "Solution found at depth " << upNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//2nd Child (Down)
		struct node* downNode = new node(down(currentNode->puzzle, row, col), currentNode->depth);
		if (downNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, downNode->puzzle)) {
			newNodes.push(downNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(downNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(downNode->puzzle)) {
				cout << "Solution found at depth " << downNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//3rd Child (Left)
		struct node* leftNode = new node(left(currentNode->puzzle, row, col), currentNode->depth);
		if (leftNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, leftNode->puzzle)) {
			newNodes.push(leftNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(leftNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(leftNode->puzzle)) {
				cout << "Solution found at depth " << leftNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//4th Child (Right)
		struct node* rightNode = new node(right(currentNode->puzzle, row, col), currentNode->depth);
		if (rightNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, rightNode->puzzle)) {
			newNodes.push(rightNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(rightNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(rightNode->puzzle)) {
				cout << "Solution found at depth " << rightNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}

		//Pop the expanded node
		frontier.erase(frontier.begin());

		//Add the new nodes to frontier and empty the new node tree
		while (!(newNodes.empty())) {
			frontier.push_back(newNodes.front());
			newNodes.pop();
		}

		//Sort frontier in increasing order of FN
		sort(frontier.begin(), frontier.end(), [](node* x, node* y) {
			return x->fn < y->fn; 
			});
	}
}

//A-STAR SEARCH (MISPLACED HEURISTIC)
int AStarMisplacedHeuristicSearch(vector<vector<int>> puzzle) {
	int expandedNodes = 0;
	int depth = -1;
	int row, col;

	//Vector of visited puzzles
	vector<vector<vector<int>>> visitedPuzzles;

	//Make queue and create root with initial state
	queue<node*> newNodes;
	struct node* initialState = new node(puzzle, depth);

	//Goal State is Initial State
	if (isGoalState(initialState->puzzle)) {
		cout << "Solution found at depth " << initialState->depth << endl;
		cout << "Total expanded nodes: " << expandedNodes << endl;
		return 0;
	}

	//Frontier Vector Initialization
	vector<node*> frontier{ initialState };

	//While Loop
	while (true) {
		node* currentNode = frontier.front();

		//Failure
		if (frontier.empty()) {
			cout << "No solution" << endl;
			return 0;
		}

		//Determine where the blank space in the current puzzle is
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (currentNode->puzzle[i][j] == 0) {
					row = i;
					col = j;
				}
			}
		}

		/*Apply each move to the current node to make children
		Push to new node tree only if move was legal and if not visited before*/
		//1st Child (Up)
		struct node* upNode = new node(up(currentNode->puzzle, row, col), currentNode->depth);
		if (upNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, upNode->puzzle)) {
			newNodes.push(upNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(upNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(upNode->puzzle)) {
				cout << "Solution found at depth " << upNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//2nd Child (Down)
		struct node* downNode = new node(down(currentNode->puzzle, row, col), currentNode->depth);
		if (downNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, downNode->puzzle)) {
			newNodes.push(downNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(downNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(downNode->puzzle)) {
				cout << "Solution found at depth " << downNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//3rd Child (Left)
		struct node* leftNode = new node(left(currentNode->puzzle, row, col), currentNode->depth);
		if (leftNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, leftNode->puzzle)) {
			newNodes.push(leftNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(leftNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(leftNode->puzzle)) {
				cout << "Solution found at depth " << leftNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}
		//4th Child (Right)
		struct node* rightNode = new node(right(currentNode->puzzle, row, col), currentNode->depth);
		if (rightNode->puzzle != emptyPuzzle && isNotVisitedPuzzle(visitedPuzzles, rightNode->puzzle)) {
			newNodes.push(rightNode); //Push puzzle to back of newNodes queue
			visitedPuzzles.push_back(rightNode->puzzle); //Mark puzzle as visited
			expandedNodes++;

			//Goal State Reached
			if (isGoalState(rightNode->puzzle)) {
				cout << "Solution found at depth " << rightNode->depth << endl;
				cout << "Total expanded nodes: " << expandedNodes << endl;
				return 0;
			}
		}

		//Pop the expanded node
		frontier.erase(frontier.begin());

		//Add the new nodes to frontier and empty the new node tree
		while (!(newNodes.empty())) {
			frontier.push_back(newNodes.front());
			newNodes.pop();
		}

		//Sort frontier in increasing order of the node's misplaced value
		sort(frontier.begin(), frontier.end(), [](node* x, node* y) {
			return x->misplaced < y->misplaced;
			});
	}
}
int main() {
	//uniformCostSearch(puzzle12);
	AStarManhattanSearch(puzzle20);
	//AStarMisplacedHeuristicSearch(puzzle12);

	return 0;
}