#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <span>
#include <ranges>
#include <iostream>
#include <unordered_set>
#include <iomanip> 
#include <queue>
#include <numeric>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

bool hasCycle(ListNode* head) {
    ListNode* hare = head;
    ListNode* torture = head;

    while (torture->next != nullptr)
    {
        if (torture->next->next != nullptr)
        {
            hare = hare->next->next;
        }
        else
        {
            return false;
        }
        if (torture == hare)
        {
            return true;
        }
        torture = torture->next;
    }
    return false;
}

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList_hash(Node* head) {
    unordered_map<Node*, Node*> mp;

    Node* curr = head;
    Node* curr_deep = new Node(head->val);
    mp.emplace(head, curr_deep);
    Node* prev_deep = curr_deep;
   
    while (curr != nullptr)
    {
        if (mp.contains(curr))
        {
            curr_deep = mp[curr];
        }
        else
        {
            curr_deep = new Node(curr->val);
            mp.emplace(curr, curr_deep);
        }

        if (mp.contains(curr->random))
        {
            curr_deep->random = mp[curr->random];
        }
        else
        {
            Node* random = curr->random;

            if (random != nullptr)
            {
                Node* new_random = new Node(random->val);
                mp.emplace(random, new_random);
                curr_deep->random = new_random;
            }
        }
       
        curr = curr->next;
        prev_deep->next = curr_deep;
        prev_deep = curr_deep;
    }

    return mp[head];
}

Node* copyRandomList(Node* head) {
    if (!head) {
        return nullptr;
    }
    
    Node* ptr = head;
    while (ptr != nullptr) {
        Node* newNode = new Node(ptr->val);
        newNode->next = ptr->next;
        ptr->next = newNode;
        ptr = newNode->next;
    }
    ptr = head;

    while (ptr != nullptr) {
        ptr->next->random =
            (ptr->random != nullptr) ? ptr->random->next : nullptr;
        ptr = ptr->next->next;
    }

    Node* ptr_old_list = head;        // A->B->C
    Node* ptr_new_list = head->next;  // A'->B'->C'
    Node* head_new = head->next;

    while (ptr_old_list != nullptr) {
        ptr_old_list->next = ptr_old_list->next->next;
        ptr_new_list->next = (ptr_new_list->next != nullptr)
            ? ptr_new_list->next->next
            : nullptr;
        ptr_old_list = ptr_old_list->next;
        ptr_new_list = ptr_new_list->next;
    }
    return head_new;
}


ListNode* reverseList(ListNode* head) {
    ListNode* current = head;
    ListNode* prev = nullptr;
    while (current != nullptr)
    {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummy = new ListNode(0, head);
    ListNode* before = dummy;

    for (int i = 1; i < left; ++i) {
        before = before->next;
    }

    ListNode* prev = before;
    ListNode* curr = before->next;

    for (int i = left; i <= right; ++i) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    before->next->next = curr;
    before->next = prev;

    return dummy->next;
}

ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr)
        return nullptr;

    ListNode* dummy = new ListNode(301);
    ListNode* prev_node = dummy;
    ListNode* first = head->next;
    ListNode* second = head;

    if ((head->next != nullptr && head->next->val != head->val) || head->next == nullptr)
    {
        prev_node->next = new ListNode(head->val);
        prev_node = prev_node->next;
    }

    while (first != nullptr)
    {
        if (!(first->val == second->val)  &&
            !(first->next != nullptr && first->next->val == first->val))
        {
            prev_node->next = new ListNode(first->val);
            prev_node = prev_node->next;
        }
        first = first->next;
        second = second->next;
    }

    return dummy->next;
}

//----------------------------------------------------------------------------
bool canJumpFromPosition(int position, vector<int>& nums) {
    if (position == nums.size() - 1) {
        return true;
    }

    int furthestJump = min(position + nums[position], (int)nums.size() - 1);
    for (int nextPosition = position + 1; nextPosition <= furthestJump;
        nextPosition++) {
        if (canJumpFromPosition(nextPosition, nums)) {
            return true;
        }
    }

    return false;
}
bool canJump(vector<int>& nums) { return canJumpFromPosition(0, nums); }

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// 
struct TreeNode {
   int val;
   TreeNode* left;
   TreeNode* right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty() || inorder.empty()) return nullptr;

    unordered_map<int, int> inorderIndexMap;
    for (int i = 0; i < inorder.size(); i++) {
        inorderIndexMap[inorder[i]] = i;
    }

    stack<TreeNode*> st;
    TreeNode* root = new TreeNode(preorder[0]);
    st.push(root);

    for (int i = 1; i < preorder.size(); ++i) {
        int preorderValue = preorder[i];
        TreeNode* node = new TreeNode(preorderValue);


        if (inorderIndexMap[preorderValue] < inorderIndexMap[st.top()->val]) {
            st.top()->left = node;
        }
        else {
            TreeNode* parent = nullptr;
            while (!st.empty() && inorderIndexMap[preorderValue] > inorderIndexMap[st.top()->val]) {
                parent = st.top();
                st.pop();
            }
            parent->right = node;
        }

        st.push(node);
    }

    return root;
}

TreeNode* buildTree_post(vector<int>& inorder, vector<int>& postorder) {
    if (postorder.empty() || inorder.empty()) return nullptr;

    unordered_map<int, int> inorderIndexMap;
    for (int i = 0; i < inorder.size(); i++) {
        inorderIndexMap[inorder[i]] = i;
    }

    stack<TreeNode*> st;
    int postIndex = postorder.size() - 1;
    TreeNode* root = new TreeNode(postorder[postIndex--]);
    st.push(root);

    while (postIndex >= 0) {
        int postorderValue = postorder[postIndex];
        TreeNode* node = new TreeNode(postorderValue);

        if (inorderIndexMap[postorderValue] > inorderIndexMap[st.top()->val]) {
            st.top()->right = node;
        }
        else {
            TreeNode* parent = nullptr;
            while (!st.empty() && inorderIndexMap[postorderValue] < inorderIndexMap[st.top()->val]) {
                parent = st.top();
                st.pop();
            }
            parent->left = node;
        }

        st.push(node);
        postIndex--;
    }

    return root;
}

// Вспомогательная функция для вычисления высоты дерева
int treeHeight(TreeNode* root) {
    if (root == nullptr) return 0;
    return max(treeHeight(root->left), treeHeight(root->right)) + 1;
}

// Вспомогательная функция для печати уровня дерева
void printLevel(TreeNode* root, int level, int indentSpace, int levelHeight, int& spaces) {
    if (root == nullptr) {
        cout << setw((levelHeight - level + 1) * indentSpace + 1) << " ";
        return;
    }

    if (level == 1) {
        cout << setw(spaces) << " " << root->val;
        spaces = indentSpace * 2;
    }
    else if (level > 1) {
        printLevel(root->left, level - 1, indentSpace, levelHeight, spaces);
        printLevel(root->right, level - 1, indentSpace, levelHeight, spaces);
    }
}

// Функция для печати дерева в ASCII виде
void printTree(TreeNode* root) {
    int height = treeHeight(root);
    int levelHeight = height;
    int indentSpace = 3;

    for (int i = 1; i <= height; ++i) {
        int spaces = indentSpace * (levelHeight - i + 1);
        printLevel(root, i, indentSpace, levelHeight, spaces);
        cout << endl;
    }
}


void flatten_preorder(TreeNode* root)
{
    stack<TreeNode*>st;
    st.push(root);
    while (!st.empty())
    {
        TreeNode* curr = st.top();
        st.pop();
        if (curr == NULL) return;
        if (curr->right != NULL) st.push(curr->right);
        if (curr->left != NULL) st.push(curr->left);
        if (!st.empty())
        {
            curr->right = st.top();
        }
        curr->left = NULL;
    }
    return;
}

void flatten_inorder(TreeNode** root) {
    if (root == nullptr) {
        return;
    }

    stack<TreeNode*> st;
    TreeNode* curr = *root;
    TreeNode* prev = nullptr;
    bool new_root = true;

    while (!st.empty() || curr != nullptr) {
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();

        if (new_root)
        {
            *root = curr;
            new_root = false;
        }

        if (prev != nullptr) {
            prev->right = curr;
            prev->left = nullptr;
        }

        prev = curr;
        curr = curr->right;
    }
}

void flatten(TreeNode* root) {
    // Initialize a pointer
    // 'curr' to the root of the tree
    TreeNode* curr = root;

    // Iterate until 'curr'
    // becomes NULL
    while (curr) {
        // Check if the current
        // node has a left child
        if (curr->left) {
            // If yes, find the rightmost
            // node in the left subtree
            TreeNode* pre = curr->left;
            while (pre->right) {
                pre = pre->right;
            }

            // Connect the rightmost node in
            // the left subtree to the current
           //  node's right child
            pre->right = curr->right;

            // Move the entire left subtree to the
            // right child of the current node
            curr->right = curr->left;

            // Set the left child of
            // the current node to NULL
            curr->left = NULL;
        }

        // Move to the next node
        // on the right side
        curr = curr->right;
    }
}

int dfs(TreeNode* root) {
    int res = 0;
    stack<pair<TreeNode*, int>> stk;
    stk.push(make_pair(root, root->val));

    while (!stk.empty()) {
        auto [node, value] = stk.top();
        stk.pop();

        if (node->right == nullptr && node->left == nullptr) {
            res += value;
        }

        if (node->right != nullptr) {
            stk.push(make_pair(node->right, node->right->val + value * 10));
        }
        if (node->left != nullptr) {
            stk.push(make_pair(node->left, node->left->val + value*10));
        }
    }

    return res;
}

int maxPathSum(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int max_sum = INT_MIN;
    stack<pair<TreeNode*, int> > s;
    s.push(make_pair(root, 0));

    while (!s.empty()) {
        auto [node, state] = s.top();
        s.pop();

        if (node == nullptr) {
            continue;
        }

        if (state == 0) {
            // first visit to the node
            s.push(make_pair(node, 1));
            s.push(make_pair(node->left, 0));
        }
        else if (state == 1) {
            // second visit to the node
            s.push(make_pair(node, 2));
            s.push(make_pair(node->right, 0));
        }
        else {
            // third visit to the node
            int left_sum = (node->left != nullptr)
                ? node->left->val
                : 0;
            int right_sum = (node->right != nullptr)
                ? node->right->val
                : 0;
            max_sum
                = max(max_sum, node->val + max(0, left_sum)
                    + max(0, right_sum));
            int max_child_sum = max(left_sum, right_sum);
            node->val += max(0, max_child_sum);
        }
    }

    return max_sum;
}

int sumNumbers(TreeNode* root) {
    if (root == nullptr)
        return 0;
    return dfs(root);
}

int computeDepth(TreeNode* node) {
    int d = 0;
    while (node->left != nullptr) {
        node = node->left;
        ++d;
    }
    return d;
}
bool exists(int idx, int d, TreeNode* node) {
    int left = 0, right = pow(2, d) - 1;
    int pivot;
    for (int i = 0; i < d; ++i) {
        pivot = left + (right - left) / 2;
        if (idx <= pivot) {
            node = node->left;
            right = pivot;
        }
        else {
            node = node->right;
            left = pivot + 1;
        }
    }
    return node != nullptr;
}
int countNodes(TreeNode* root) {
    if (root == nullptr)
        return 0;
    int d = computeDepth(root);
    if (d == 0)
        return 1;
    int left = 1, right = pow(2, d) - 1;
    int pivot;
    while (left <= right) {
        pivot = left + (right - left) / 2;
        if (exists(pivot, d, root))
            left = pivot + 1;
        else
            right = pivot - 1;
    }
    return pow(2, d) - 1 + left;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left == NULL) {
        return right;
    }
    else if (right == NULL) {
        return left;
    }
    else
    {
        return root;
    }
}

int deleteAndEarn(vector<int>& nums) {
    unordered_map<int, int> points;

    for (int num : nums) {
        points[num] += num;
    }

    vector<int> elements;
    for (auto& p : points) {
        elements.push_back(p.first);
    }
    sort(elements.begin(), elements.end());

    int twoBack = 0;
    int oneBack = points[elements[0]];

    for (int i = 1; i < elements.size(); i++) {
        int currentElement = elements[i];
        int temp = oneBack;
        if (currentElement == elements[i - 1] + 1) {
            oneBack = max(oneBack, twoBack + points[currentElement]);
        }
        else {
            oneBack += points[currentElement];
        }
        twoBack = temp;
    }

    return oneBack;
}

class Solution {
private:
    vector<vector<char>> board;
    int ROWS;
    int COLS;

public:
    bool exist(vector<vector<char>>& board, string word) {
        this->board = board;
        ROWS = board.size();
        COLS = board[0].size();
        for (int row = 0; row < ROWS; ++row)
            for (int col = 0; col < COLS; ++col)
                if (backtrack(row, col, word)) return true;
        return false;
    }

protected:
    bool backtrack(int row, int col, const string& word) {
        stack<tuple<int, int, int, char>> st; // (row, col, index)
        st.push({ row, col, 0, board[row][col]});
        int count = 3;
        vector<vector<char>> visited(ROWS, vector<char>(COLS, ' '));

        while (!st.empty()) {     
            auto [r, c, index, val] = st.top();
            st.pop();
            
            if (board[r][c] != word[index] && count > 0)
            {
                --count;
                continue;
            }

            if (board[r][c] == '#' && count == 0)
            {
                board[r][c] = val;
                continue;
            }

            if (index == word.size()-1)
            {
                return true;
            }

            int rowOffsets[4] = { 0, 1, 0, -1 };
            int colOffsets[4] = { 1, 0, -1, 0 };
            
            st.push({r,c,index,board[r][c]});
            board[r][c] = '#';

            for (int d = 0; d < 4; ++d) {
                int newRow = r + rowOffsets[d];
                int newCol = c + colOffsets[d];
                if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS)
                {
                    st.push({ newRow, newCol, index + 1, board[newRow][newCol] });
                }
            }
            count = 4;

        }
        return false;
    }
};

class sortListC {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* mid = getMid(head);
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);
        return merge(left, right);
    }

    ListNode* merge(ListNode* list1, ListNode* list2) {
        ListNode dummyHead(0);
        ListNode* ptr = &dummyHead;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                ptr->next = list1;
                list1 = list1->next;
            }
            else {
                ptr->next = list2;
                list2 = list2->next;
            }
            ptr = ptr->next;
        }
        if (list1)
            ptr->next = list1;
        else
            ptr->next = list2;

        return dummyHead.next;
    }

    ListNode* getMid(ListNode* head) {
        ListNode* midPrev = nullptr;
        while (head && head->next) {
            midPrev = (midPrev == nullptr) ? head : midPrev->next;
            head = head->next->next;
        }
        ListNode* mid = midPrev->next;
        midPrev->next = nullptr;
        return mid;
    }
};

string addBinary(string a, string b) {
    int n = a.size(), m = b.size();
    if (n < m)
        return addBinary(b, a);  // Ensure 'a' is always the longer string

    string result;
    int carry = 0, j = m - 1;

    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == '1') ++carry;
        if (j >= 0 && b[j--] == '1') ++carry;

        result.push_back((carry % 2) ? '1' : '0');
        carry /= 2;
    }

    if (carry == 1) result.push_back('1');  // Handle the last carry

    reverse(result.begin(),
        result.end());  // The result is built in reverse
    return result;
}

int main() {
    addBinary("1011", "1011");
    
    
    return 0;
}
