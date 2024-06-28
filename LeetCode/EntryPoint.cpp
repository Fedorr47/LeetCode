#include <iostream>

#include "Tasks\DisjointTree.h"

using namespace DisjointTree;

// Test Case
int main() {
    vector<vector<int>> pairs{ {0,3} ,{1,2} };
    vector<vector<string>> equations {{"a", "b"}, {"b", "c"}};
    vector<double> values{2.0, 3.0};
    vector<vector<string>> queries {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    Solution sol;
    auto val = sol.calcEquation(equations, values, queries);
    return 0;
}