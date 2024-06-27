#pragma once

#include <vector>
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
            for (int i = 0; i < sz; ++i)
            {
                root[i] = i;
            }
        }
        int find(int x)
        {
            if (root[x] == x)
            {
                return x;
            }
            return root[x] = find(root[x]);
        }
        void unionSet(int x, int y)
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

        int getCount() {
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
                        uf.unionSet(i, j);
                    }
                }
            }
            return uf.getCount();
        }

        bool validTree(int n, vector<vector<int>>& edges) {
            int edg_size = edges.size();
            UnionFind uf(n);

            if (edg_size >= n)
                return false;

            for (int i = 0; i < edg_size; ++i)
            {
                uf.unionSet(edges[i][0], edges[i][1]);
            }

            return uf.getCount() == 1;
        }
    };
}