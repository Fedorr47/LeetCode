#pragma once

#include <vector>
#include <unordered_map>
using namespace std;

namespace MaxPointsOnLine
{
    class Solution {
    public:
        int maxPoints(vector<vector<int>>& points) {
            int res = 1;
            int points_len = points.size();

            for (size_t i = 0; i < points_len; ++i) {
                auto Point1 = points[i];
                unordered_map<float, int> slopes;
                for (size_t j = i + 1; j < points_len; ++j) {
                    float slope = 0;
                    auto Point2 = points[j];
                    if (Point1[0] == Point2[0]) {
                        slope = std::numeric_limits<int>::max();
                    }
                    else {
                        slope = static_cast<float>((Point2[1] - Point1[1])) /
                            static_cast<float>((Point2[0] - Point1[0]));
                    }
                    slopes[slope] += 1;
                    res = max(res, slopes[slope] + 1);
                }
            }
            return res;
        }
    };
}