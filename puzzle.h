#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>

using namespace std;

const vector<vector<int>> GOAL = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}; //define goal state

struct PuzzleState{
    vector<vector<int>> puzzle;
    int cost = -1;
    int heuristics = -1;
    int totalCost = -1;
    string path;

    bool operator<(const PuzzleState& other) const{
        return totalCost < other.totalCost;                   //compare correct order
    }

    bool operator==(const PuzzleState& other) const{
        return puzzle == other.puzzle;                  //compare for goal
    }
};

PuzzleState customPuzzle(); //user built puzzle
bool GOALTEST(const PuzzleState& state);     //compare curr state to goal
vector<PuzzleState> EXPAND(const PuzzleState& state);

void uniformCostSearch(const PuzzleState& initialState);       //option 1 selected

int mispplacedTileFind(const vector<vector<int>> puzzle); //find num of misplaced tiles
void misplacedTile(PuzzleState& initialState);       //option 2 selected

int manhattanDistanceFind(const vector<vector<int>> puzzle); //calculate manhattan distance
void manhattanDistance(PuzzleState& initialState);       //option 3 selected


#endif