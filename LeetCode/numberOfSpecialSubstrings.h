#pragma once

#include <string>

using namespace std;

namespace SlidingWindow
{
    class Solution {
    public:
        int numberOfSpecialSubstrings(string s) {
            int substringCount = 0;

            int start = 0;
            int freq[26] = { 0 };
            for (int end = 0; end < s.size(); end++) {
                freq[s[end] - 'a']++;

                while (freq[s[end] - 'a'] > 1) {
                    freq[s[start] - 'a']--;
                    start++;
                }

                substringCount += (end - start + 1);
            }

            return substringCount;
        }
    };
}