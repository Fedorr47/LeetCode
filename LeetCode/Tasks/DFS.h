#pragma once
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

namespace DFS
{
    class Solution {
    public:

        void dfsr(vector<vector<int>>& graph, int node, vector<int>& path,
            vector<vector<int>>& paths) {
            path.push_back(node);
            if (node == graph.size() - 1) {
                paths.emplace_back(path);
                return;
            }
            vector<int> nextNodes = graph[node];
            for (int nextNode : nextNodes) {
                dfsr(graph, nextNode, path, paths);
                path.pop_back();
            }
        }

        vector<vector<int>> allPathsSourceTargetr(vector<vector<int>>& graph) {
            vector<vector<int>> paths;
            if (graph.size() == 0) {
                return paths;
            }
            vector<int> path;
            dfsr(graph, 0, path, paths);
            return paths;
        }
    };
}