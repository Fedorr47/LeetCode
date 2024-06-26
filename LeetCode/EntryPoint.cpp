#include "BalanceBST.h"

using namespace BST;

int main()
{
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    Solution sol;
    sol.balance_BST(root);
	return 0;
}