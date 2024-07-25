#pragma once

#include <vector>
#include <string_view>
using namespace std;

namespace KMP
{
    class Solution {
    public:

        vector<size_t> computePrefixFunction(string_view pattern) {
            size_t m = pattern.size();
            vector<size_t> pi(m, 0);

            for (size_t i = 1, j = 0; i < m; ++i) {
                while (j > 0 && pattern[i] != pattern[j]) {
                    j = pi[j - 1];
                }
                if (pattern[i] == pattern[j]) {
                    ++j;
                }
                pi[i] = j;
            }

            return pi;
        }

        int strStr(string_view haystack, string_view needle) {
            if (needle.empty()) return 0; // Если образец пустой, возвращаем 0

            size_t m = needle.size();
            size_t n = haystack.size();
            vector<size_t> pi = computePrefixFunction(needle);

            for (size_t i = 0, j = 0; i < n; ++i) {
                while (j > 0 && haystack[i] != needle[j]) {
                    j = pi[j - 1];
                }
                if (haystack[i] == needle[j]) {
                    ++j;
                }
                if (j == m) {
                    return i - m + 1; // Найдено совпадение
                    //j = pi[j - 1];
                }
            }

            return -1; // Если не найдено
        }

        string longestPrefix(string s) {
            size_t n = s.size();
            if (n == 0)
                return "";

            vector<size_t> pi = computePrefixFunction(s);
            size_t length = pi[n - 1]; // Длина самого длинного префикса, который
            // также является суффиксом

            return string(s.substr(0, length));
        }
    };
}