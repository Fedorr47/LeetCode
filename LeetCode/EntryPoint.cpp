#include <iostream>

#include "Tasks\DisjointTree.h"

using namespace DisjointTree;

// Test Case
int main() {
    vector<vector<int>> pairs{ {0,3} ,{1,2} };
    Solution sol;
    string val = sol.smallestStringWithSwaps("dcab", pairs);
    return 0;
}