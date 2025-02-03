#include <iostream>
#include <vector>
#include <limits>
#include "puzzle.h"
using namespace std;

int main(){
    int puzzleChoice = 0;
    int solveChoice = 0;

    cout << "Choose custom puzzle (1) or choose default(2)" << endl;

    while(!(cin >> puzzleChoice) || puzzleChoice != 1 && puzzleChoice != 2){
        cout << "--Invalid input try again--" << endl
        << "Choice: " ;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    PuzzleState initialState;

    if(puzzleChoice == 1){
        //initialState = customPuzzle();
    }
    else{
        initialState.puzzle = {{1,2,3}, {0,4,6}, {7,8,5}};
        initialState.cost = 0;
        initialState.path = "";
    }

    cout << endl;
    
    cout << "Choose solving method: " << endl
        << "(1) Uniform Cost Search" << endl
        << "(2) A* with Misplaced Tile" << endl
        << "(3) A* with Manhattan Distance" << endl;

    while(!(cin >> solveChoice) || solveChoice != 1 && solveChoice != 2 && solveChoice != 3){
        cout << "--Invalid input try again--" << endl
        << "Choice: " ;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if(solveChoice == 1){
        cout << "Running Uniform Cost Search..." << endl;
        //uniformCostSearch(initialState);
    }else if (solveChoice == 2){
        cout << "Running A* with Misplaced Tile Heuristic..." << endl;
       //aStarMisplacedTile(initialState);
    }else if (solveChoice == 3){
        cout << "Running A* with Manhattan Distance Heuristic..." << endl;
        //aStarManhattanDistance(initialState);
    }

    return 0;
}