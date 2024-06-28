#pragma once

#include <vector>
#include <numeric>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

namespace DisjointTree
{
    struct UnionFind
    {
        UnionFind(int sz) :
            root(sz),
            rank(sz, 0),
            count(sz)
        {
            iota(root.begin(), root.end(), 0);
        }

        int find(int x)
        {
            if (root[x] == x)
            {
                return x;
            }
            return root[x] = find(root[x]);
        }

        void union_set(int x, int y)
        {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY)
            {
                if (rank[rootX] < rank[rootY])
                {
                    root[rootX] = rootY;
                }
                else if (rank[rootX] > rank[rootY])
                {
                    root[rootY] = rootX;
                }
                else
                {
                    root[rootY] = rootX;
                    rank[rootX] += 1;
                }
                count--;
            }
        }

        virtual int get_count() {
            return count;
        }

        bool is_connected(int x, int y)
        {
            return find(x) == find(y);
        }
        vector<int> root;
        vector<int> rank;
        int count;
    };

    class Solution {
    public:
        int findCircleNum(vector<vector<int>>& isConnected) {
            int con_len = isConnected.size();
            UnionFind uf(con_len);
            for (int i = 0; i < con_len; ++i)
            {
                for (int j = 0; j < con_len; ++j)
                {
                    if (i == j)
                        continue;
                    if (isConnected[i][j] && !uf.is_connected(i, j))
                    {
                        uf.union_set(i, j);
                    }
                }
            }
            return uf.get_count();
        }

        bool validTree(int n, vector<vector<int>>& edges) {
            int edg_size = edges.size();
            UnionFind uf(n);

            if (edg_size >= n)
                return false;

            for (int i = 0; i < edg_size; ++i)
            {
                uf.union_set(edges[i][0], edges[i][1]);
            }

            return uf.get_count() == 1;
        }

        int countComponents(int n, vector<vector<int>>& edges) {
            int edg_size = edges.size();
            UnionFind uf(n);

            for (int i = 0; i < edg_size; ++i)
            {
                uf.union_set(edges[i][0], edges[i][1]);
            }

            return uf.get_count();
        }

        int earliestAcq(vector<vector<int>>& logs, int n) {
            int logs_len = logs.size();
            std::sort(logs.begin(), logs.end(), [&logs](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });
            UnionFind uf(n);
            for (int i = 0; i < logs_len; ++i)
            {
                int x = logs[i][1];
                int y = logs[i][2];
                if (!uf.is_connected(x, y))
                {
                    uf.union_set(x, y);
                }
                if (uf.get_count() == 1)
                {
                    return logs[i][0];
                }

            }
            return -1;
        }

        string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
            UnionFind uf(s.size());

            for (vector<int> pair : pairs) {
                uf.union_set(pair[0], pair[1]);
            }

            unordered_map<int, vector<int>> rootToComponent;
            for (int vertex = 0; vertex < s.size(); vertex++) {
                int root = uf.find(vertex);
                rootToComponent[root].push_back(vertex);
            }


            string smallestString(s.length(), ' ');
            for (auto component : rootToComponent) 
            {
                vector<int> indices = component.second;
                vector<char> characters;

                for (int index : indices) {
                    characters.push_back(s[index]);
                }
                sort(characters.begin(), characters.end());

                for (int index = 0; index < indices.size(); index++) {
                    smallestString[indices[index]] = characters[index];
                }
            }

            return smallestString;
        }

        // Evaluate Division https://leetcode.com/problems/evaluate-division/submissions/1302921379/
        vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
            unordered_map<string, pair<string, double>> gidWeight;

            // Step 1). build the union groups
            for (int i = 0; i < equations.size(); i++) {
                vector<string> equation = equations[i];
                string dividend = equation[0], divisor = equation[1];
                double quotient = values[i];

                unionGroups(gidWeight, dividend, divisor, quotient);
            }

            // Step 2). run the evaluation, with "lazy" updates in find() function
            vector<double> results(queries.size());
            for (int i = 0; i < queries.size(); i++) {
                vector<string> query = queries[i];
                string dividend = query[0], divisor = query[1];

                if (!gidWeight.count(dividend) || !gidWeight.count(divisor))
                    // case 1). at least one variable did not appear before
                    results[i] = -1.0;
                else {
                    pair<string, double> dividendEntry = find(gidWeight, dividend);
                    pair<string, double> divisorEntry = find(gidWeight, divisor);

                    string dividendGid = dividendEntry.first;
                    string divisorGid = divisorEntry.first;
                    double dividendWeight = dividendEntry.second;
                    double divisorWeight = divisorEntry.second;

                    if (dividendGid != divisorGid)
                        // case 2). the variables do not belong to the same chain/group
                        results[i] = -1.0;
                    else
                        // case 3). there is a chain/path between the variables
                        results[i] = dividendWeight / divisorWeight;
                }
            }

            return results;
        }

        pair<string, double> find(unordered_map<string, pair<string, double>>& gidWeight, const string& nodeId) {
            if (!gidWeight.count(nodeId))
                gidWeight[nodeId] = { nodeId, 1.0 };

            pair<string, double> entry = gidWeight[nodeId];
            // found inconsistency, trigger chain update
            if (entry.first != nodeId) {
                pair<string, double> newEntry = find(gidWeight, entry.first);
                gidWeight[nodeId] = { newEntry.first, entry.second * newEntry.second };
            }

            return gidWeight[nodeId];
        }

        void unionGroups(unordered_map<string, pair<string, double>>& gidWeight, const string& dividend, const string& divisor, double value) {
            pair<string, double> dividendEntry = find(gidWeight, dividend);
            pair<string, double> divisorEntry = find(gidWeight, divisor);

            string dividendGid = dividendEntry.first;
            string divisorGid = divisorEntry.first;
            double dividendWeight = dividendEntry.second;
            double divisorWeight = divisorEntry.second;

            // merge the two groups together,
            // by attaching the dividend group to the one of divisor
            if (dividendGid != divisorGid) {
                gidWeight[dividendGid] = { divisorGid, divisorWeight * value / dividendWeight };
            }
        }

    };
}

