#pragma once

#include <unordered_map>
#include <string>

using namespace std;

struct TrieNode{
        unordered_map<char, TrieNode*> children;

        string word;
        TrieNode() : word("") {}
        bool word_flag = false;
};

class Trie {
public:
    TrieNode* root;
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* head = root;
        for (char c : word) {
            if (!head->children.contains(c)) {
                TrieNode* temp = new TrieNode();
                head->children.emplace(c, temp);
            }
            head = head->children[c];
        }
        head->word = word;
        head->word_flag = true;
    }

    TrieNode* search_prefix(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.contains(c)) {
                node = node->children[c];
            }
            else {
                return nullptr;
            }
        }
        return node;
    }

    bool contains_key(char c) { return root->children.contains(c); }

    bool search(string word) {
        TrieNode* node = search_prefix(word);
        return node != nullptr && node->word_flag;
    }

    bool startsWith(string word) {
        TrieNode* node = search_prefix(word);
        return node != nullptr;
    }
};

class Solution {

    Trie* trie = nullptr;

public:

    // https://leetcode.com/problems/word-break/description/?envType=study-plan-v2&envId=top-interview-150
    bool wordBreak(string s, vector<string>& wordDict) {
        trie = new Trie();
        for (string& word : wordDict) {
            trie->insert(word);
        }

        vector<bool> dp(s.length());
        for (int i = 0; i < s.length(); i++) {
            if (i == 0 || dp[i - 1]) {
                TrieNode* curr = trie->root;
                for (int j = i; j < s.length(); j++) {
                    char c = s[j];
                    if (!curr->children.contains(c)) {
                        break;
                    }

                    curr = curr->children[c];
                    if (curr->word_flag) {
                        dp[j] = true;
                    }
                }
            }
        }

        return dp[s.length() - 1];
    }
};