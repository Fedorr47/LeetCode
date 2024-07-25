#pragma once

#include <unordered_map>

using namespace std;


class LFUCache {
public:
    using value_t = int;
    using key_t = int;
    using freq_t = int;

    unordered_map<key_t, list<pair<freq_t, value_t>>> frequencies;
    unordered_map<key_t, pair<int, list<pair<freq_t, value_t>>::iterator>> cache;
    int capacity;
    int minf;

    void insert(int key, int frequency, int value) {
        frequencies[frequency].push_back({ key, value });
        cache[key] = { frequency, --frequencies[frequency].end() };
    }

    LFUCache(int capacity) : capacity(capacity), minf(0) {}

    int get(int key) {
        const auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        const auto [f, iter] = it->second;
        const auto [_, kv] = *iter;
        frequencies[f].erase(iter);
        if (frequencies[f].empty()) {
            frequencies.erase(f);

            if (minf == f) {
                ++minf;
            }
        }

        insert(key, f + 1, kv);
        return kv;
    }

    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        }
        const auto it = cache.find(key);
        if (it != cache.end()) {
            it->second.second->second = value;
            get(key);
            return;
        }
        if (capacity == cache.size()) {
            cache.erase(frequencies[minf].front().first);
            frequencies[minf].pop_front();

            if (frequencies[minf].empty()) {
                frequencies.erase(minf);
            }
        }

        minf = 1;
        insert(key, 1, value);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    int val;
    int key;
    Node() {}
    Node(int in_key, int in_val) :
        key(in_key),
        val(in_val),
        next(nullptr),
        prev(nullptr)
    {}
    Node(int in_key, int in_val, Node* in_next, Node* in_prev) :
        key(in_key),
        val(in_val),
        next(in_next),
        prev(in_prev)
    {}
};

class LRUCache {
public:
    int capacity_;
    Node* head = nullptr;
    Node* tail = nullptr;
    unordered_map<int, Node*> mp;

    LRUCache(int in_capacity) {
        capacity_ = in_capacity;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    void add(Node* node)
    {
        Node* prev_end = tail->prev;
        prev_end->next = node;
        node->prev = prev_end;
        node->next = tail;
        tail->prev = node;
    }

    void remove(Node* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    int get(int key) {
        if (!mp.contains(key))
        {
            return -1;
        }

        Node* node = mp[key];
        remove(node);
        add(node);
        return node->val;
    }

    void put(int key, int value) {
        if (mp.contains(key))
        {
            remove(mp[key]);
        }

        Node* new_node = new Node(key, value);
        mp[key] = new_node;
        add(new_node);

        if (mp.size() > capacity_)
        {
            Node* node_to_del = head->next;
            remove(node_to_del);
            mp.erase(node_to_del->key);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

