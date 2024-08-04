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