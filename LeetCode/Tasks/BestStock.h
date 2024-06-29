#pragma once

#include <vector>

using namespace std;

namespace BestStock
{
    class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int min = numeric_limits<int>::max();
            int max = 0;

            for (int i = 0; i < prices.size(); ++i)
            {
                if (prices[i] < min)
                    min = prices[i];
                else if (prices[i] - min > max)
                    max = prices[i] - min;
            }
            return max;
        }
    };
}