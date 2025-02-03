#include "puzzle.h"
#include <iostream>
#include <limits>

PuzzleState customPuzzle(){ //user built puzzle
    PuzzleState state;
    state.puzzle = vector<vector<int>>(3, vector<int>(3));  // 3x3 board
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



















void uniformCostSearch(const PuzzleState& initstate);       //option 1 selected
void misplacedTile(const PuzzleState& initstate);       //option 2 selected
int mispplacedTileFind(const vector<vector<int>> puzzle); //find num of misplaced tiles
void manhattanDistance(const PuzzleState& initstate);       //option 3 selected
int manhattanDistanceFind(const vector<vector<int>> puzzle); //calculate manhattan distance
bool isGoalState(const PuzzleState& state);     //compare curr state to goal
vector<PuzzleState> moves(const PuzzleState& state);