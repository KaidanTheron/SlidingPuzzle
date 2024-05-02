//
// Created by Kaidan Theron on 2024/05/02.
//

#include "utilities.h"
#include "node.h"
#include <iostream>

using namespace std;

int Utilities::h(vector<vector<int>> BoardState, vector<vector<int>> GoalState) { // heuristic function
    int h = 0;
    for (int i = 0; i < BoardState.size(); i++) {
        for (int j = 0; j < BoardState.size(); j++) {
            if (BoardState[i][j] != GoalState[i][j]) {
                h++;
            }
        }
    }
    return h;

}

vector<Node> Utilities::getSuccessors(vector<vector<int>> BoardState) {
    vector<Node> successors;
    int blankRow, blankCol;
    bool foundBlank = false;

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for (int i = 0; i < BoardState.size(); i++) {
        if (foundBlank) {
            break;
        }
        for (int j = 0; j < BoardState.size(); j++) {
            if (BoardState[i][j] == -1) {
                blankRow = i;
                blankCol = j;
                foundBlank = true;
                break;
            }
        }
    }

    for (auto direction : directions) {
        auto newRow = blankRow + direction.first;
        auto newCol = blankCol + direction.second;

        if (newRow >= 0 && newRow < BoardState.size() && newCol >= 0 && newCol < BoardState.size()) {
            vector<vector<int>> newBoardState = BoardState;
            swap(newBoardState[blankRow][blankCol], newBoardState[newRow][newCol]);
            Node newNode = Node(newBoardState, "");
            successors.push_back(newNode);
        }
    }

    return successors;
}