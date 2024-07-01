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
        bool dfs(
            unordered_map<int, vector<int>>& graph,
            vector<bool>& seen,
            int current_node,
            int dest_node
        )
        {
            if (current_node == dest_node)
                return true;
            if (!seen[current_node])
            {
                seen[current_node] = true;
                for (auto& next_node : graph[current_node])
                {
                    if (dfs(graph, seen, next_node, dest_node))
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
            unordered_map<int, vector<int>> graph;
            vector<bool> seen(n, false);
            for (auto edge : edges)
            {
                graph[edge[0]].push_back(edge[1]);
                graph[edge[1]].push_back(edge[0]);
            }
            return dfs(graph, seen, source, destination);
        }
    };
}