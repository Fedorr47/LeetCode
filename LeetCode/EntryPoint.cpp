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

class  FirstLastBinary{
public:

    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            // Case 1: Find target
            if (nums[mid] == target) {
                return mid;
            }
            // Case 2: Subarray on mid's left is sorted
            else if (nums[mid] >= nums[left]) {
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            // Case 3: Subarray on mid's right is sorted
            else {
                if (target <= nums[right] && target > nums[mid]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};

class Dijkstra 
{
    vector<pair<int, int>> adj[101];
    vector<int> signalReceivedAt;

    void dijkstra(int source, int n) {
        priority_queue<pair<int, int>, vector<pair<int, int>>,
            greater<pair<int, int>>> pq;
        pq.push({ 0, source });

        signalReceivedAt[source] = 0;

        while (!pq.empty()) {
            auto [currNodeTime, currNode] = pq.top();
            pq.pop();

            if (currNodeTime > signalReceivedAt[currNode]) {
                continue;
            }

            for (pair<int, int> edge : adj[currNode]) {
                auto [time, neighborNode] = edge;

                if (signalReceivedAt[neighborNode] > currNodeTime + time) {
                    signalReceivedAt[neighborNode] = currNodeTime + time;
                    pq.push({ signalReceivedAt[neighborNode], neighborNode });
                }
            }
        }
    }

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        for (vector<int> time : times) {
            int source = time[0];
            int dest = time[1];
            int travelTime = time[2];

            adj[source].push_back({ travelTime, dest });
        }

        signalReceivedAt = vector<int>(n + 1, INT_MAX);
        dijkstra(k, n);

        int answer = INT_MIN;
        for (int i = 1; i <= n; i++) {
            answer = max(answer, signalReceivedAt[i]);
        }

        return answer == INT_MAX ? -1 : answer;
    }
};

class Kadane {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        const int n = nums.size();
        vector<int> rightMax(n);
        rightMax[n - 1] = nums[n - 1];
        int suffixSum = nums[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            suffixSum += nums[i];
            rightMax[i] = max(rightMax[i + 1], suffixSum);
        }

        int maxSum = nums[0];
        int specialSum = nums[0];
        int curMax = 0;
        int prefixSum = 0;
        for (int i = 0; i < n; ++i) {
            // This is Kadane's algorithm.
            curMax = max(curMax, 0) + nums[i];
            maxSum = max(maxSum, curMax);

            prefixSum += nums[i];
            if (i + 1 < n) {
                specialSum = max(specialSum, prefixSum + rightMax[i + 1]);
            }
        }

        return max(maxSum, specialSum);
    }
};

void reverseString(std::string& str) {
    std::reverse(str.begin(), str.end());
}

string addBinary(string a, string b) {
    int lenA = a.length();
    int lenB = b.length();
    int maxLen = std::max(lenA, lenB);

    std::string result(maxLen + 1, '0');

    std::string x(a);
    std::string y(b);
    reverseString(x);
    reverseString(y);

    int carry = 0;
    for (int i = 0; i < maxLen; i++) {
        int bitA = i < lenA ? x[i] - '0' : 0;
        int bitB = i < lenB ? y[i] - '0' : 0;

        int sum = bitA ^ bitB ^ carry;
        carry = (bitA & bitB) | (carry & (bitA ^ bitB));

        result[i] = sum + '0';
    }

    if (carry) {
        result[maxLen] = carry + '0';
    }
    else {
        result.pop_back();
    }

    reverseString(result);

    if (result[0] == '0' && result.length() > 1) {
        result.erase(0, 1);
    }

    return result;
}

string addBinary1(string a, string b) {
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


bool is_Interleave(string s1, int i, string s2, int j, string s3, int k,
    vector<vector<int>>& memo) {
    if (i == s1.length()) {
        return s2.substr(j) == s3.substr(k);
    }
    if (j == s2.length()) {
        return s1.substr(i) == s3.substr(k);
    }
    if (memo[i][j] >= 0) {
        return memo[i][j] == 1 ? true : false;
    }
    bool ans = false;
    if ((s3[k] == s1[i] &&
        is_Interleave(s1, i + 1, s2, j, s3, k + 1, memo)) ||
        (s3[k] == s2[j] &&
            is_Interleave(s1, i, s2, j + 1, s3, k + 1, memo))) {
        ans = true;
    }
    memo[i][j] = ans ? 1 : 0;
    return ans;
}
bool isInterleave(string s1, string s2, string s3) {
    if (s1.length() + s2.length() != s3.length()) {
        return false;
    }
    vector<vector<int>> memo(s1.length(), vector<int>(s2.length(), -1));
    return is_Interleave(s1, 0, s2, 0, s3, 0, memo);
}

class MedianFinder {
public:
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;

    MedianFinder() {}

    void addNum(int num) {
        lo.push(num);

        hi.push(lo.top());
        lo.pop();

        if (lo.size() < hi.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() {
        return lo.size() > hi.size() ? lo.top()
            : ((double)lo.top() + hi.top()) * 0.5;
    }
};



// Definition for a Node.
class NodeK {
public:
    int val;
    vector<NodeK*> children;

    NodeK() {}

    NodeK(int _val) {
        val = _val;
    }

    NodeK(int _val, vector<NodeK*> _children) {
        val = _val;
        children = _children;
    }
};

class InOrderN {
public:
    vector<int> postorder(NodeK* root) {
        if (root == nullptr)
            return vector<int>{};

        vector<int> res;
        deque<pair<NodeK*,int>> q;
        q.push_front({ root, 0 });

        while (!q.empty())
        {
            auto [top, was] = q.front();
            q.pop_front();

            if (top->children.size() == 0 || was)
            {
                res.push_back(top->val);
                continue;
            }

            q.push_front({top, 1});
            for (int i = top->children.size() - 1; i >= 0; --i)
            {
                q.push_front({ top->children[i], 0 });
            }
        }

        return res;
    }
};

int main() {
    NodeK* node5 = new NodeK(5);
    NodeK* node6 = new NodeK(6);
    NodeK* node3 = new NodeK(3, { node5, node6 });
    NodeK* node2 = new NodeK(2);
    NodeK* node4 = new NodeK(4);
    NodeK* node1 = new NodeK(1, { node3 , node2 , node4 });

    InOrderN rep;
    rep.postorder(node1);

    // Пример входных данных
    std::string s1 = "abc";
    std::string s2 = "bcd";
    std::string s3 = "abcbdc";

    // Вызов метода isInterleave
    bool result = isInterleave(s1, s2, s3);

    // Вывод результата
    std::cout << (result ? "True" : "False") << std::endl;

    return 0;
    return 0;
}
