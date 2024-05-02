//
// Created by Kaidan Theron on 2024/05/02.
//
#include <string>
#include <vector>

#ifndef NODE_H
#define NODE_H

using namespace std;

// class for storing boardState and move that got it there
struct Node {
    vector<vector<int>> boardState;
    string move;

    Node(vector<vector<int>> boardState, string move);
};



#endif //NODE_H
