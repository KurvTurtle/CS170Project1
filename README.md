# CS170Project1Project 1					           CS170: Introduction to Artificial Intelligence
Christian Melendez								     Dr. Eamonn Keogh
SID: 862189972
cmele014@ucr.edu
2/20/2021

In completing this project I consulted:
The blind and heuristic search slides from lecture
“How to sort a vector of custom objects in C++ (https://www.techiedelight.com/sort-vector-custom-objects-cpp/)
C++ Documentation at cplusplus.com for vectors
GeeksForGeeks - Stacks and Queues using STL (https://www.youtube.com/watch?v=fV_DchJem0U&feature=emb_logo)
GeeksForGeeks - Vector in C++ STL (https://www.geeksforgeeks.org/vector-in-cpp-stl/)

Important code is original
Unimportant subroutines that are not completely original:
Node data structure (create new node part)
Using custom comparator when sorting the frontier vector in the A* algorithms

OUTLINE
Cover Page (Pg. 1)
Introduction & Design (Pg. 2)
Comparison of Algorithms (Pg. 3)
Comparison of Algorithms On Sample Puzzles w/ Data (Pg. 4 - 7)
Conclusion (Pg. 8)
Trace on Puzzle 2 with Uniform Cost Search (Pg. 8)
Trace on Puzzle 2 with A* Misplaced Tile Heuristic (Pg. 9)
Code (Pg.10-11) (Github Link)
CS170 PROJECT 1: THE EIGHT-PUZZLE
Christian, SID 862189972, February 20, 2021
INTRODUCTION
In this project, my task is to implement a uniform cost search algorithm and 2 different
A* algorithms to solve several 8-puzzles. The 8-puzzles given are all solvable and are of 0, 2, 4, 8, 12, 16, 20, and 24 depth. A “solved” or goal state of an 8-puzzle is when each number goes in a sequential tile as follows:
1   2   3
4   5   6
7   8   0, where 0 represents an empty tile.

All algorithms used are able to solve the puzzles optimally. However, solving the 8-puzzles of higher depths require the use of more efficient algorithms because of time and space limitations. I set a 15 minute time limit when running an algorithm. If it can’t solve the given puzzle within that time, the algorithm is said to be unable to solve that particular puzzle.
The algorithms are written in C++ in the Visual Studio IDE. The total number of expanded nodes are used as a metric to compare the efficiency of each algorithm as they are all optimal. When available, the process memory and runtime from the Diagnostic Tools tab in Visual Studio are compared as well.

DESIGN
	The 8-puzzle is designed in C++ as a 2D 3x3 vector. Each number is represented by itself and the empty tile is represented as the number 0.
The operators used to manipulate the 8-puzzle are to “move” the empty tile up, down, left, or right by 1 tile. What the operators actually do within the vector are swap the positions between the empty tile and the other corresponding tile.
Any time one of these operators are executed, there is a check to see if the operation is legal. If so, the operator returns the new puzzle. Otherwise, an “empty” puzzle is returned with all empty tiles or 0’s.
The algorithms used rely on the node data structure. All nodes consist of a 2D 3x3 vector puzzle, a depth, and values for the misplaced and Manhattan Distance heuristics. Children are not hard coded within the data structure. Instead, new nodes are created when necessary.


COMPARISON OF ALGORITHMS
Uniform cost search, A* search with a misplaced tile heuristic, and A* with a Manhattan
Distance heuristic were used to solve the 8-puzzle.

Uniform Cost Search
Uniform cost search for the 8-puzzle is functionally identical to a breadth-first search. This is because the cost of any operator (or transition from one level of the tree to another) is always 1. It can also be said that the total cost of reaching a node is equal to its depth.
Uniform cost search will expand the node with the smallest cost. In this case, it expands each node from left to right level by level just like breadth first search. This is the least efficient of the 3 algorithms.

The Misplaced Tile Heuristic
The first A* search algorithm implemented uses the misplaced tile heuristic. Any tile in the puzzle that is not in the correct position adds 1 to the value of this heuristic (not counting the empty tile or 0). 
Adding this heuristic combined with the cost of reaching a node will create the complete heuristic for an A* search. Only using the misplaced tile heuristic creates a Hill-Climbing or Greedy algorithm that may lead to very slow and memory heavy results. The misplaced tile heuristic A* search is the 2nd most efficient algorithm of the 3.

The Manhattan Distance Heuristic
The second A* search algorithm implemented uses the Manhattan Distance Heuristic. This heuristic takes the “Manhattan Distance” between any tile and the tile it should be at in the goal state. The Manhattan Distance value is the sum of the distance from the puzzle’s goal state horizontal position and its goal state vertical position for each tile (not counting the empty tile).
For example take this 8-puzzle:
				1   2   3
				5   0   6
					4   7   8
	The 1, 2, 3, and 6 are all in their goal state positions and don’t contribute to the Manhattan Distance heuristic. The 5, 7, and 8 are 1 horizontal space away from their goal state (total = 3). The 4 is 1 vertical space away from its goal state (total = 4). So the total Manhattan Distance heuristic value is 4 for this 8-puzzle.
	Like with the other A* search, this wouldn’t be A* if we don’t add the cost to get to a node with the heuristic value. This total is the true Manhattan Distance heuristic value for A* search. This is the most efficient of the 3 algorithms.


COMPARISON OF ALGORITHMS ON SAMPLE PUZZLES
These are all the sample puzzles given and their corresponding optimal depths.

Fig 1. Sample Puzzles

The first puzzle with depth 0 is the goal state and used for testing purposes. With the rest of the puzzles, we observe that the algorithms perform relatively similar when the search depth is low. However, when the depth increases, the efficiency of the algorithms are drastically different.

The uniform cost and A* with misplaced tile heuristic searches don’t reach to the end of the solution depth axis because they were unable to solve those puzzles in a reasonable time. As we can clearly see, those searches would have grown their nodes expanded value exponentially, making it impossible to solve puzzles larger than listed.



DATA
Uniform Cost Search
Puzzle0
Expanded Nodes: 0
Process Memory: 933KB
Runtime: N/A

Puzzle2
Expanded Nodes: 7
Process Memory: 946KB
Runtime: N/A

Puzzle4
Expanded Nodes: 33
Process Memory: 1MB
Runtime: N/A

Puzzle8
Expanded Nodes: 311
Process Memory: 2MB
Runetime: N/A

Puzzle12
Expanded Nodes: 2328
Process Memory: 7.5MB
Runtime: 34s

Puzzle16/Puzzle20/Puzzle24
Unable to finish within 15 mins


A-Star Search (Misplaced Heuristic)
Puzzle0
Expanded Nodes: 0
Process Memory: N/A
Runtime: N/A

Puzzle2
Expanded Nodes: 5
Process Memory: N/A
Runtime: N/A

Puzzle4
Expanded Nodes: 10
Process Memory: N/A
Runtime: N/A

Puzzle8
Expanded Nodes: 35
Process Memory: N/A
Runtime: N/A

Puzzle12
Expanded Nodes: 214
Process Memory: N/A
Runtime: N/A

Puzzle16
Expanded Nodes: 1106
Process Memory: 4.5MB
Runtime: 8s

Puzzle20
Expanded Nodes: 5108
Process Memory: 16MB 
Runtime: 2min 54s

Puzzle24
Unable to finish within 15 mins


A-Star Search (Manhattan Distance)
Puzzle0
Expanded Nodes: 0
Process Memory: N/A
Runtime: N/A

Puzzle2
Expanded Nodes: 5
Process Memory: N/A
Runtime: N/A

Puzzle4
Expanded Nodes: 10
Process Memory: N/A
Runtime: N/A

Puzzle8
Expanded Nodes: 24
Process Memory: N/A
Runtime: N/A

Puzzle12
Expanded Nodes: 64
Process Memory: N/A
Runtime: N/A

Puzzle16
Expanded Nodes: 386
Process Memory: N/A
Runtime: ~1s

Puzzle20
Expanded Nodes: 770
Process Memory: 3MB
Runtime: 4s

Puzzle24
Expanded Nodes: 6412
Process Memory: 19MB
Runtime: 4min 42s
CONCLUSION

