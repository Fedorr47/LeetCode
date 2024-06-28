#pragma once

#include <vector>
#include <algorithm>

using namespace std;

namespace TotalImportanceRoads
{
    class Solution {
    public:
        long long maximumImportance(int n, vector<vector<int>>& roads) {
            vector<long long> degrees(n, 0);

            for (vector<int> road : roads)
            {
                degrees[road[0]]++;
                degrees[road[1]]++;
            }

            std::sort(degrees.begin(), degrees.end());

            int value = 1;
            int totalImportance = 0;

            for (long long degree : degrees)
            {
                totalImportance += (degree * value);
                ++value;
            }

            return totalImportance;
        }
    };
}