#include <iostream>
#include <vector>
#include <limits>
//#include "puzzle.h"
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

    if(puzzleChoice == 1){
        cout << "custom" << endl;
    }
    else{
        cout << "default" << endl;
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
    return 0;
}