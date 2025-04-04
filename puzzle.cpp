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

bool GOALTEST(const PuzzleState& state){     //check if goal state reached
    return state.puzzle == GOAL;
}

vector<PuzzleState> EXPAND(const PuzzleState& state){
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
    vector<PuzzleState> nodes;        // nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    set<vector<vector<int>>> visited;           //track visited avoid repeat
    int nodesExpanded = 0; 
    int maxQueueSize = 0;

    nodes.push_back(initialState);        //MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    visited.insert(initialState.puzzle);       //initialize queue with start state

    while(!nodes.empty()){       //loop do,, if EMPTY(nodes) then return "failure"
        PuzzleState node = nodes.front();        
        nodes.erase(nodes.begin());     //node = REMOVEFRONT(nodes)

        nodesExpanded++;        //track # of nodes expanded

        if(GOALTEST(node)){      // if problem.GOALTEST(node.STATE) succeeds then return node
            cout << "Depth: " << node.cost << endl 
                 << "Path: " << node.path << endl
                 << "Nodes Expanded: " << nodesExpanded << endl
                 << "Max Queue Size: " << maxQueueSize << endl;

            return; 
        }

        vector<PuzzleState> Moves = EXPAND(node);        // EXPAND(node, problem.OPERATORS)

        for (size_t i = 0; i < Moves.size(); ++i){      //find cost of every move
            PuzzleState move = Moves[i];

            if (visited.find(move.puzzle) == visited.end()){       //add to nodes in not visited yet
                move.cost = node.cost + 1;     //total cost updated
                move.totalCost = move.cost;
                nodes.push_back(move);
                visited.insert(move.puzzle);
            }
        }

        sort(nodes.begin(), nodes.end());         //order queue
        maxQueueSize = max(maxQueueSize, static_cast<int>(nodes.size()));     //queue size updated

    }
    cout << "No solution found." << endl;
 
}

int mispplacedTileFind(const vector<vector<int>> puzzle){ //find num of misplaced tiles
    int misplacedAmt = 0;

    for(int i = 0; i < 3; ++i){     //traverse 3x3 grid
        for(int j = 0; j < 3; ++j){
            if(puzzle[i][j] != 0 && puzzle[i][j] != GOAL[i][j]){        //ignore blank space and compare node (i,j) to correct (i,j)
                misplacedAmt++;     //increase if (i,j) is different than goal(i,j)
            }
        }
    }
    return misplacedAmt;
}

void misplacedTile(PuzzleState& initialState){       //option 2 selected
    vector<PuzzleState> nodes;        // nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    set<vector<vector<int>>> visited;           //track visited avoid repeat
    int nodesExpanded = 0; 
    int maxQueueSize = 0;

    initialState.heuristics = mispplacedTileFind(initialState.puzzle);      //set h(n)
    initialState.totalCost = initialState.cost + initialState.heuristics;       //f(n) = c(n) + h(n)
    nodes.push_back(initialState);        //MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    visited.insert(initialState.puzzle);       //initialize queue with start state

    while(!nodes.empty()){
        PuzzleState node = nodes.front();        // if EMPTY(nodes) then return "failure"
        nodes.erase(nodes.begin());     //node = REMOVEFRONT(nodes)

        nodesExpanded++;        //track # of nodes expanded

        if(GOALTEST(node)){      // if problem.GOALTEST(node.STATE) succeeds then return node
            cout << "Depth: " << node.cost << endl 
                 << "Path: " << node.path << endl
                 << "Nodes Expanded: " << nodesExpanded<< endl
                 << "Max Queue Size: " << maxQueueSize << endl;

            return; 
        }

        vector<PuzzleState> Moves = EXPAND(node);        // EXPAND(node, problem.OPERATORS)

        for (size_t i = 0; i < Moves.size(); ++i){      //find cost of every move
            PuzzleState move = Moves[i];

            if (visited.find(move.puzzle) == visited.end()){       //add to nodes in not visited yet
                move.heuristics = mispplacedTileFind(move.puzzle);     //total cost updated
                move.totalCost = move.cost + move.heuristics;
                nodes.push_back(move);
                visited.insert(move.puzzle);
            }
        }

        sort(nodes.begin(), nodes.end());         //order queue
        maxQueueSize = max(maxQueueSize, static_cast<int>(nodes.size()));     //queue size updated

    }
    cout << "No solution found." << endl;
}

int manhattanDistanceFind(const vector<vector<int>> puzzle){ //calculate manhattan distance
    int distance = 0;

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            int value = puzzle[i][j];

            if(puzzle[i][j] != 0){      //ignores blank tile
                distance += abs(i - ((value - 1) / 3)); //find the goal row index for the number at (i,j) and calc distance from node row index 
                distance += abs(j - ((value - 1) % 3)); //find the goal col index for the number at (i,j) and calc distance form node col index
            }

        }
    }
    return distance;
}

void manhattanDistance(PuzzleState& initialState){       //option 3 selected
    vector<PuzzleState> nodes;        // nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    set<vector<vector<int>>> visited;           //track visited avoid repeat
    int nodesExpanded = 0; 
    int maxQueueSize = 0;

    initialState.heuristics = manhattanDistanceFind(initialState.puzzle);      //set h(n)
    initialState.totalCost = initialState.cost + initialState.heuristics;       //f(n) = c(n) + h(n)
    nodes.push_back(initialState);        //MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    visited.insert(initialState.puzzle);       //initialize queue with start state

    while(!nodes.empty()){
        PuzzleState node = nodes.front();        // if EMPTY(nodes) then return "failure"
        nodes.erase(nodes.begin());     //node = REMOVEFRONT(nodes)

        nodesExpanded++;        //track # of nodes expanded

        if(GOALTEST(node)){      // if problem.GOALTEST(node.STATE) succeeds then return node
            cout << "Depth: " << node.cost << endl 
                 << "Path: " << node.path << endl
                 << "Nodes Expanded: " << nodesExpanded<< endl
                 << "Max Queue Size: " << maxQueueSize << endl;

            return; 
        }

        vector<PuzzleState> Moves = EXPAND(node);        // EXPAND(node, problem.OPERATORS)

        for (size_t i = 0; i < Moves.size(); ++i){      //find cost of every move
            PuzzleState move = Moves[i];

            if (visited.find(move.puzzle) == visited.end()){       //add to nodes in not visited yet
                move.heuristics = manhattanDistanceFind(move.puzzle);     //total cost updated
                move.totalCost = move.cost + move.heuristics;
                nodes.push_back(move);
                visited.insert(move.puzzle);
            }
        }

        sort(nodes.begin(), nodes.end());         //order queue
        maxQueueSize = max(maxQueueSize, static_cast<int>(nodes.size()));     //queue size updated

    }
    cout << "No solution found." << endl;       //if EMPTY(nodes) then return "failure"
}