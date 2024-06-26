#pragma once

#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

namespace BST
{ 
// Определение структуры TreeNode
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;

        // Конструктор по умолчанию
        TreeNode() : val(0), left(nullptr), right(nullptr) {}

        // Конструктор с параметром значения
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

        // Конструктор с параметрами значения, левого и правого дочерних узлов
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };

    class Solution {
    public:
        vector<TreeNode*> arr;
        void inOrder(TreeNode* root) {
            std::stack<TreeNode*> stack;
            TreeNode* current = root;

            while (current != nullptr || !stack.empty()) {
                while (current != nullptr) {
                    stack.push(current);
                    current = current->left;
                }
                current = stack.top();
                stack.pop();
                arr.push_back(current);
                current = current->right;
            }
        }

        // Итеративная версия функции для балансировки BST
        TreeNode* balanceBST(int l, int r) {
            if (l > r) return nullptr;

            std::stack<std::tuple<int, int, TreeNode**>> stack;
            TreeNode* root = nullptr;

            stack.push({ l, r, &root });

            while (!stack.empty()) {
                auto [start, end, nodeRef] = stack.top();
                stack.pop();

                if (start > end) continue;

                int mid = start + (end - start) / 2;
                *nodeRef = arr[mid];
                (*nodeRef)->left = nullptr;
                (*nodeRef)->right = nullptr;

                stack.push({ mid + 1, end, &(*nodeRef)->right });
                stack.push({ start, mid - 1, &(*nodeRef)->left });
            }

            return root;
        }

        TreeNode* balance_BST(TreeNode* root) {
            inOrder(root);
            return balanceBST(0, arr.size() - 1);
        }
    };

};