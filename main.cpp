#include <iostream>
#include <map>
#include <queue>
#include "utilities.h"
#include "node.h"
#include <sstream>
#include <fstream>

using namespace std;

class pNode {
public:
    pair<int, Node> p;

    pNode(pair <int, Node> p) : p(p) { };

    bool operator<(const pNode& other) const {
        return p.first < other.p.first;
    }

};

// output the entire board
void printGrid(vector<vector<int>> board) {
    for (auto row : board) {
        for (auto col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

//  reconstruct_path(cameFrom, current) {
//     total_path = [current]
//     while current in cameFrom.Keys:
//         current = cameFrom[current]
//         total_path.append(current)
//     return total_path;
// }

// void printSolution(map<vector<vector<int>>, Node, CompareNode> cameFrom, vector<vector<int>> current) {
//     int moves = 0;
//
//
// }

std::vector<int> splitString(const std::string& input) { // split the string into a vector of integers
    std::vector<int> numbers;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, ' ')) {
        numbers.push_back(std::stoi(token));
    }

    return numbers;
}

vector<vector<vector<int>>> getBoardsFromFile(int N) { // fill the grids from the text file
    vector<vector<vector<int>>> grids;
    ifstream file;
    file.open("15_puzzles.txt");
    string line;
    int row = 0;
    vector<vector<int>> grid = vector(N, vector(N, 0));

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }
        vector<int> numbers = splitString(line);
        for (int i = 0; i < N; i++) {
            grid[row][i] = numbers[i];
        }
        row++;
        if (row == N) {
            grids.push_back(grid);
            row = 0;
        }
    }

    return grids;
}

class InfinityInt {
public:
    InfinityInt() : value(numeric_limits<int>::max()) {} // Initialize value to infinity

    InfinityInt(int val) : value(val) {}

    operator int() const { return value; }

    InfinityInt& operator=(int val) {
        value = val;
        return *this;
    }

private:
    int value;
};

void a_star_search(vector<vector<int>>start, vector<vector<int>> goal, Utilities u) {
    // set of nodes that may need to be (re-)evaluated
    typedef vector<vector<int>> boardState;
    priority_queue<pNode> openSet; // stores boards
    map<boardState, pNode> cameFrom; // map of navigated nodes (key is board, value is the board it came from and move that got it there)
    map<boardState, InfinityInt> gScore; // map of cost from start along best known path (key is board, value is cost)
    map<boardState, InfinityInt> fScore; // map of total cost of getting from start to goal through the board (key is board, value is cost)

    gScore[start] = 0;
    fScore[start] = u.h(start, goal);

    openSet.push(pNode(make_pair(0, Node(start, ""))));

    while (!openSet.empty()) { // openSet isnt empty
        auto current = openSet.top(); // the node in openSet having the lowest fScore[] value
        openSet.pop();

        // printGrid(current.p.second.boardState);
        // cout << endl;

        if (u.h(current.p.second.boardState, goal) == 0) { // current board is goal
            cout << "Solution found!" << endl;
            // printSolution(cameFrom, current.second.boardState);
            return;
        }

        // get successors of boardState
        auto successors = u.getSuccessors(current.p.second.boardState);

        for (auto successor : successors) {
            int sGScore = gScore[current.p.second.boardState] + 1; // cost from start to successor through current path
            if (sGScore < gScore[successor.boardState]) {;
                gScore[successor.boardState] = sGScore;
                fScore[successor.boardState] = sGScore + u.h(successor.boardState, goal);
                cameFrom.insert({successor.boardState, current});


                openSet.push(pair<int, Node>(fScore[successor.boardState], successor));

            }
        }
    }

    cout << "done" << endl;
}

int main()
{

    Utilities u;
    vector<vector<vector<int>>> boards = getBoardsFromFile(4);
    vector<vector<int>> goal = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, -1}
    };

    for (auto board : boards) {
        a_star_search(board, goal, u);
    }

    return 0;
}
