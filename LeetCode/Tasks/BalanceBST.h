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

    class SolutionVine {
    public:
        TreeNode* balanceBST(TreeNode* root) {
            if (!root) return nullptr;

            // Step 1: Create the backbone (vine)
            // Temporary dummy node
            TreeNode* vineHead = new TreeNode(0);
            vineHead->right = root;
            TreeNode* current = vineHead;
            while (current->right) {
                if (current->right->left) {
                    rightRotate(current, current->right);
                }
                else {
                    current = current->right;
                }
            }

            // Step 2: Count the nodes
            int nodeCount = 0;
            current = vineHead->right;
            while (current) {
                ++nodeCount;
                current = current->right;
            }

            // Step 3: Create a balanced BST
            int m = pow(2, floor(log2(nodeCount + 1))) - 1;
            makeRotations(vineHead, nodeCount - m);
            while (m > 1) {
                m /= 2;
                makeRotations(vineHead, m);
            }

            TreeNode* balancedRoot = vineHead->right;
            // Delete the temporary dummy node
            delete vineHead;
            return balancedRoot;
        }

    private:
        // Function to perform a right rotation
        void rightRotate(TreeNode* parent, TreeNode* node) {
            TreeNode* tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;
            parent->right = tmp;
        }

        // Function to perform a left rotation
        void leftRotate(TreeNode* parent, TreeNode* node) {
            TreeNode* tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            parent->right = tmp;
        }

        // Function to perform a series of left rotations to balance the vine
        void makeRotations(TreeNode* vineHead, int count) {
            TreeNode* current = vineHead;
            for (int i = 0; i < count; ++i) {
                TreeNode* tmp = current->right;
                leftRotate(current, tmp);
                current = current->right;
            }
        }
    };

    class SolutionRecursion {
    public:
        vector<TreeNode*> arr;
        void inOrder(TreeNode* root) {
            if (!root) return;
            inOrder(root->left);
            arr.push_back(root);
            inOrder(root->right);
        }

        TreeNode* balanceBST(const int l, const int r) {
            if (l > r) return NULL;
            const int m = (l + r) / 2;
            TreeNode* const left = balanceBST(l, m - 1);
            TreeNode* const right = balanceBST(m + 1, r);
            arr[m]->left = left;
            arr[m]->right = right;
            return arr[m];
        }

        TreeNode* balanceBST(TreeNode* root) {
            inOrder(root);
            return balanceBST(0, arr.size() - 1);
        }
    };

};