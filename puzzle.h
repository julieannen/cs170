#include <vector>
#include <string>
using namespace std;

struct PuzzleState{
    vector<vector<int>> puzzle;
    int cost = -1;
    int heuristics = -1;
    int totalCost = -1;
    string path;

    bool operator<(const PuzzleState& other) const{
        return puzzle < other.puzzle;                   //compare correct order
    }

    bool operator==(const PuzzleState& other) const{
        return puzzle == other.puzzle;                  //compare for goal
    }
};