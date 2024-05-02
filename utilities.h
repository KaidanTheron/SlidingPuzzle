//
// Created by Kaidan Theron on 2024/05/02.
//

#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include "node.h"

using namespace std;

class Utilities {
public:
    int h(vector<vector<int>> BoardState, vector<vector<int>> GoalState);

    vector<Node> getSuccessors(vector<vector<int>> BoardState);

};

#endif //UTILITIES_H
