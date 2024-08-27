#pragma once

#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<vector<int>> allPathsSourceTarget_bfs(vector<vector<int>>& graph)
{
    vector<vector<int>> paths;
    if (graph.size() == 0) {
        return paths;
    }

    vector<int> path;
    queue<pair<int, vector<int>>> q;
    q.push({ 0 , {0} });

    while (!q.empty()) {
        auto [node, path] = q.front();
        q.pop();
        for (int nextNode : graph[node]) {
            vector<int> tmpPath(path.begin(), path.end());
            tmpPath.push_back(nextNode);
            if (nextNode == graph.size() - 1) {
                paths.push_back(tmpPath);
            }
            else {
                q.push({ nextNode, tmpPath });
            }
        }
    }
    return paths;
}

vector<vector<int>> allPathsSourceTarget_dfs(vector<vector<int>>& graph)
{
    vector<vector<int>> paths;
    if (graph.empty()) {
        return paths;
    }

    stack<pair<int, vector<int>>> stk;
    stk.push({ 0, {0} });

    while (!stk.empty()) {
        auto [node, path] = stk.top();
        stk.pop();

        if (node == graph.size() - 1) {
            paths.push_back(path);
            continue;
        }

        for (int nextNode : graph[node]) {
            vector<int> newPath = path;
            newPath.push_back(nextNode);
            stk.push({ nextNode, newPath });
        }
    }

    return paths;
}

bool validPath_bfs(int n, vector<vector<int>>& edges, int start, int end) {
    vector<vector<int>> adjacency_list(n);
    for (vector<int> edge : edges) {
        adjacency_list[edge[0]].push_back(edge[1]);
        adjacency_list[edge[1]].push_back(edge[0]);
    }

    queue<int> q;
    q.push(start);
    vector<bool> seen(n);
    seen[start] = true;

    while (!q.empty()) {
        // Get the current node.
        int node = q.front();
        q.pop();

        // Check if we have reached the target node.
        if (node == end) {
            return true;
        }

        // Add all neighbors to the stack.
        for (int neighbor : adjacency_list[node]) {
            // Check if neighbor has been added to the queue before.
            if (!seen[neighbor]) {
                seen[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false;
}


bool validPath_dfs(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<int>> adjacency_list(n);
    for (vector<int> edge : edges) {
        adjacency_list[edge[0]].push_back(edge[1]);
        adjacency_list[edge[1]].push_back(edge[0]);
    }

    stack<int> stk;
    stk.push(source);
    vector<bool> seen(n);
    seen[source] = true;

    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if (node == destination) {
            return true;
        }

        for (int neighbor : adjacency_list[node]) {
            if (!seen[neighbor]) {
                seen[neighbor] = true;
                stk.push(neighbor);
            }
        }
    }

    return false;
}
namespace connect {
    class Node {
    public:
        int val;
        Node* left;
        Node* right;
        Node* next;

        Node() : val(0), left(NULL), right(NULL), next(NULL) {}

        Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

        Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
    };

    Node* connect(Node* root) {
        if (root == nullptr)
            return root;

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            int sz = q.size();

            for (int i = 0; i < sz; ++i)
            {
                Node* node = q.front();
                q.pop();
                if (i < sz - 1)
                    node->next = q.front();

                if (node->left != nullptr)
                    q.push(node->left);
                if (node->right != nullptr)
                    q.push(node->right);
            }
        }
        return root;
    }

    // https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
    Node* connect_const_space(Node* root) {
        if (root == nullptr) {
            return root;
        }
        Node* leftmost = root;
        while (leftmost->left != nullptr) {
            Node* head = leftmost;
            while (head != nullptr) {
                head->left->next = head->right;
                if (head->next != nullptr) {
                    head->right->next = head->next->left;
                }
                head = head->next;
            }
            leftmost = leftmost->left;
        }
        return root;
    }
    // https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/editorial/?envType=study-plan-v2&envId=top-interview-150
    Node* connect_const_space_child_nulls(Node* root) {
        if (root == nullptr) {
            return root;
        }

        Node* leftmost = root;

        while (leftmost != nullptr) {
            Node* current = leftmost;
            Node* prev = nullptr;
            leftmost = nullptr;

            while (current != nullptr) {
                if (current->left != nullptr) {
                    if (prev != nullptr) {
                        prev->next = current->left;
                    }
                    else {
                        leftmost = current->left;
                    }
                    prev = current->left;
                }

                if (current->right != nullptr) {
                    if (prev != nullptr) {
                        prev->next = current->right;
                    }
                    else {
                        leftmost = current->right;
                    }
                    prev = current->right;
                }

                current = current->next;
            }
        }

        return root;
    }
}

// https://leetcode.com/problems/critical-connections-in-a-network/description/
class BridgeFinder {
public:
    std::vector<int> seen;
    std::vector<int> time_of_ins;
    std::vector<int> lowtime_of_ins;
    std::vector<std::vector<int>> adj;
    int time = 0;

    void dfs(int node, int parent, std::vector<std::vector<int>>& ans) {
        seen[node] = true;
        time_of_ins[node] = lowtime_of_ins[node] = time++;

        for (auto neighbour : adj[node]) {
            if (neighbour == parent)
                continue;
            if (!seen[neighbour]) {
                dfs(neighbour, node, ans);
                lowtime_of_ins[node] = std::min(lowtime_of_ins[node], lowtime_of_ins[neighbour]);

                if (lowtime_of_ins[neighbour] > time_of_ins[node]) {
                    ans.push_back({ node, neighbour });
                }
            }
            else {
                lowtime_of_ins[node] = std::min(lowtime_of_ins[node], time_of_ins[neighbour]);
            }
        }
    }

    std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>>& connections) {
        seen.resize(n, false);
        time_of_ins.resize(n, 0);
        lowtime_of_ins.resize(n, 0);
        adj.resize(n);

        for (const auto& edge : connections) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<std::vector<int>> ans;
        dfs(0, -1, ans);

        return ans;
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
        deque<pair<NodeK*, int>> q;
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

            q.push_front({ top, 1 });
            for (int i = top->children.size() - 1; i >= 0; --i)
            {
                q.push_front({ top->children[i], 0 });
            }
        }

        return res;
    }
};

