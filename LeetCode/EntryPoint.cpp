#include <iostream>

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <stack>

using namespace std;

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
{
    vector<vector<int>> paths;
    if (graph.empty()) {
        return paths;
    }

    stack<pair<int, vector<int>>>
        stk;
    stk.push({ 0, {0} });

    while (!stk.empty()) {
        auto [node, path] = stk.top();
        stk.pop();

        if (node == graph.size() - 1) {
            paths.push_back(path);
            continue;
        }

        for (int nextNode : graph[node]) {
            path.push_back(nextNode);
            stk.push({ nextNode, path });
            path.pop_back();
        }
    }

    return paths;
}

class Solution {
public:
    void dfs(vector<vector<int>>& graph, int node, vector<int>& path,
        vector<vector<int>>& paths) {
        path.push_back(node);
        if (node == graph.size() - 1) {
            paths.emplace_back(path);
            return;
        }
        vector<int> nextNodes = graph[node];
        for (int nextNode : nextNodes) {
            dfs(graph, nextNode, path, paths);
            path.pop_back();
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> paths;
        if (graph.size() == 0) {
            return paths;
        }
        vector<int> path;
        dfs(graph, 0, path, paths);
        return paths;
    }
};

int main() {
    vector<vector<int>> graph{ {1,2} ,{3},{3},{} };
    allPathsSourceTarget(graph);
    return 0;
}
