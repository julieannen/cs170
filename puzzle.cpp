#include "puzzle.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

PuzzleState customPuzzle(){ //user built puzzle
    PuzzleState state;
    state.puzzle = vector<vector<int>>(3, vector<int>(3));  // 3x3 puzzle
    state.cost = 0;
    state.path = "";

    cout << "Enter custom puzzle, use 0 for blank tile: " << endl
        << "(Hit enter between each number)" << endl;

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){         //defines custom puzzle for user input
            while( !(cin >> state.puzzle[i][j]) || state.puzzle[i][j] < 0 || state.puzzle[i][j] > 8){       //checks for valid input
                cout << "--Invalid input, enter numbers (0-8) only--" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    cout << endl << "Entered Puzzle: " << endl;

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){         //outputs custom puzzle
            cout << state.puzzle[i][j] ;
        }
        cout << endl;
    }
    return state;
}

bool isGoalState(const PuzzleState& state){     //check if goal state reached
    return state.puzzle == GOAL;
}

vector<PuzzleState> moves(const PuzzleState& state){
    vector<PuzzleState> moves;      //vector contains possible states of the puzzle

    int blankPositionRow = -1;
    int blankPositionCol = -1;

    for(int i = 0; i < 3; ++i){         //find (i, j) position of blank tile
        for(int j = 0; j < 3; ++j){
            if(state.puzzle[i][j] == 0){
                blankPositionRow = i;
                blankPositionCol = j;
                break;          //since (i, j) position found no need to continue search
            }
        }
        if(blankPositionRow != -1) break; //break out of second loop if (i, j) position found
    }


    //four possible moves

    if(blankPositionRow > 0){       //move up
        PuzzleState newState = state;       //new state created with updated blank position
        swap(newState.puzzle[blankPositionRow][blankPositionCol], newState.puzzle[blankPositionRow - 1][blankPositionCol]);

        newState.cost++;    //cost updated
        newState.path += "up ";      //tracing updated
        moves.push_back(newState);      //new state stored in possible states vector
    }

    if(blankPositionRow < 2){       //move down
        PuzzleState newState = state;
        swap(newState.puzzle[blankPositionRow][blankPositionCol], newState.puzzle[blankPositionRow + 1][blankPositionCol]);

        newState.cost++;    //cost updated
        newState.path += "down ";      //tracing updated
        moves.push_back(newState);      //new state stored in possible states vector
    }

    if(blankPositionCol > 0){ //move left
        PuzzleState newState = state;
        swap(newState.puzzle[blankPositionRow][blankPositionCol], newState.puzzle[blankPositionRow][blankPositionCol - 1]);

        newState.cost++;    //cost updated
        newState.path += "left ";      //tracing updated
        moves.push_back(newState);      //new state stored in possible states vector
    }

    if(blankPositionCol < 2){ //move right
        PuzzleState newState = state;
        swap(newState.puzzle[blankPositionRow][blankPositionCol], newState.puzzle[blankPositionRow][blankPositionCol + 1]);

        newState.cost++;    //cost updated
        newState.path += "right ";      //tracing updated
        moves.push_back(newState);      //new state stored in possible states vector
    }
    return moves;
}

void uniformCostSearch(const PuzzleState& initialState){       //option 1 selected
    priority_queue<PuzzleState> storedStates;        // nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    set<PuzzleState> visited;           //track visited avoid repeat

    storedStates.push(initialState);        //MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    visited.insert(initialState);       //initialize queue with start state

    while(!storedStates.empty()){       //loop do
        PuzzleState curr = storedStates.top();        // if EMPTY(nodes) then return "failure"
        storedStates.pop();

        if(isGoalState(curr)){      // if problem.GOAL-TEST(node.STATE) succeeds then return node
            cout << "Solution found with cost: " << curr.cost << endl;
            cout << "Path: " << curr.path << endl;
            return; 
        }

        vector<PuzzleState> Moves = moves(curr);        // EXPAND(node, problem.OPERATORS)

        for (size_t i = 0; i < Moves.size(); ++i){      //find cost of every move
            PuzzleState move = Moves[i];

            if (visited.find(move) == visited.end()){       //add to storedStates in not visited yet
                move.totalCost = move.cost;     //total cost updated
                storedStates.push(move);
                visited.insert(move);
            }
        }

    }
    cout << "No solution found." << endl;
 
}












// void misplacedTile(const PuzzleState& initialState);       //option 2 selected
// int mispplacedTileFind(const vector<vector<int>> puzzle); //find num of misplaced tiles
// void manhattanDistance(const PuzzleState& initialState);       //option 3 selected
// int manhattanDistanceFind(const vector<vector<int>> puzzle); //calculate manhattan distance
