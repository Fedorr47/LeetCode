#pragma once
#include <span>

using namespace std;

namespace SortTasks
{
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };


    class Solution {
    public:
        // https://leetcode.com/problems/insertion-sort-list/description/
        ListNode* insertionSortList(ListNode* head) {
            ListNode* dummy = new ListNode();
            ListNode* c = head;

            while (c != nullptr)
            {
                ListNode* prev = dummy;

                while (prev->next != nullptr && prev->next->val <= c->val)
                {
                    prev = prev->next;
                }

                ListNode* n = c->next;

                c->next = prev->next;
                prev->next = c;

                c = n;
            }
            return dummy->next;
        }
    };

    // Функция для создания односвязного списка из массива
    ListNode* createLinkedList(std::span<int> arr) {
        if (arr.size() == 0) return nullptr;
        ListNode* head = new ListNode(arr[0]);
        ListNode* current = head;
        for (int i = 1; i < arr.size(); ++i) {
            current->next = new ListNode(arr[i]);
            current = current->next;
        }
        return head;
    }
}