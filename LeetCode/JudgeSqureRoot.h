#pragma once

#include "cmath"

namespace JudgeSquareSum
{
    class Solution {
    public:
        bool judgeSquareSum(int c) {
            int left = 0;
            int right = sqrt(c);
            while (left < right)
            {
                int total = left * left + right * right;

                if (total == c)
                {
                    return true;
                }
                else if (total > c)
                {
                    --right;
                }
                else
                {
                    ++left;
                }

            }
            return false;
        }
    };
    
}