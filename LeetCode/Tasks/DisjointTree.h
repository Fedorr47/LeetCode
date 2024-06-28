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

        int get_count() {
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
    };
}