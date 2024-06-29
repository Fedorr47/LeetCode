#pragma once

#include <vector>

using namespace std;

namespace ArrayTasks
{
    class Solution {
    public:
        int removeDuplicates(vector<int>& nums) {
            // Initialize the counter and the second pointer.
            int j = 1, count = 1;
            // Start from the second element of the array and process
            // elements one by one.
            for (int i = 1; i < nums.size(); i++) {
                // If the current element is a duplicate, increment the count.
                if (nums[i] == nums[i - 1]) {
                    count++;
                }
                else {
                    // Reset the count since we encountered a different element
                    // than the previous one.
                    count = 1;
                }
                // For a count <= 2, we copy the element over thus
                // overwriting the element at index "j" in the array
                if (count <= 2) {
                    nums[j++] = nums[i];
                }
            }
            return j;
        }
        int removeDuplicates1(vector<int>& nums) {
            if (nums.size() < 3) return nums.size();
            // Initialize the counter
            int j = 2;
            //
            // Start from the third element of the array and process
            // elements one by one.
            //
            for (int i = 2; i < nums.size(); i++) {
                // If the current element is not a duplicate,
                if (nums[i] != nums[j - 2]) {
                    nums[j++] = nums[i];
                }
            }
            return j;
        }
    };
}