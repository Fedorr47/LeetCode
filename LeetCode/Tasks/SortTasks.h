#pragma once
#include <span>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

//--------------------------------------------------------------------------------------------------------------
void merge(std::span<int> arr, int p, int q, int r) {
    // Создаем L ← A[p..q] и M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1);
    vector<int> M(n2);

    std::copy(arr.begin() + p, arr.begin() + q + 1, L.begin());
    std::copy(arr.begin() + q + 1, arr.begin() + r + 1, M.begin());

    // Поддерживаем текущий индекс подмассивов и основного массива
    int i = 0, j = 0, k = p;

    // Пока не достигнем конца одного из подмассивов, выбираем больший элемент
    // из L и M и помещаем его в правильное место в A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // Когда у нас заканчиваются элементы в одном из подмассивов,
    // подбираем оставшиеся элементы и помещаем в A[p..r]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

// Разделяем массив на два подмассива, сортируем их и сливаем
void mergeSort(std::span<int> arr, int l, int r) {
    if (l < r) {
        // m - это точка, где массив делится на два подмассива
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Слияние отсортированных подмассивов
        merge(arr, l, m, r);
    }
}

// Итеративная версия сортировки слиянием
void mergeSort_iter(vector<int>& arr) {
    int n = arr.size();

    for (int curr_size = 1; curr_size < n; curr_size = 2 * curr_size) 
    {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) 
        {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            merge(arr, left_start, mid, right_end);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------
int partition(span<int> array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (array[j] <= pivot) {
            ++i;
            std::swap(array[i], array[j]);
        }
    }

    std::swap(array[i + 1], array[high]);
    return i + 1;
}

void quickSortIterative(span<int> array, int low, int high) {
    stack<pair<int, int>> st;
    st.push({ low, high });

    while (!st.empty()) {
        auto [l, h] = st.top();
        st.pop();

        if (l < h) {
            int p = partition(array, l, h);

            if (p - 1 > l) {
                st.push({ l, p - 1 });
            }
            if (p + 1 < h) {
                st.push({ p + 1, h });
            }
        }
    }
}

// Функция быстрой сортировки
void quickSort(span<int> array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}
//--------------------------------------------------------------------------------------------------------------
void max_heap(vector<int>& nums, int sz, int idx)
{
    stack<int> st;
    int largerst = 0;
    st.push(idx);

    while (!st.empty())
    {
        auto top = st.top();
        st.pop();

        largerst = top;
        int l = 2 * top + 1;
        int r = 2 * top + 2;

        if (l < sz && nums[l] > nums[largerst])
        {
            largerst = l;
        }
        if (r < sz && nums[r] > nums[largerst])
        {
            largerst = r;
        }
        if (largerst != top)
        {
            swap(nums[largerst], nums[top]);
            st.push(largerst);
        }
    }
}

vector<int> heap_sort(vector<int>& nums) {
    auto res = nums;
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        max_heap(res, n, i);
    }

    for (int i = n - 1; i >= 0; --i)
    {
        swap(res[i], res[0]);
        max_heap(res, i, 0);
    }

    return res;
}
//--------------------------------------------------------------------------------------------------------------

void countingSort(std::vector<int>& arr) {
    // Проверка на пустой массив
    if (arr.empty()) return;

    // Находим минимальный и максимальный элементы массива
    int shift = *std::min_element(arr.begin(), arr.end());
    int K = *std::max_element(arr.begin(), arr.end()) - shift;

    // Инициализируем вектор подсчетов
    std::vector<int> counts(K + 1, 0);

    // Подсчитываем количество каждого элемента
    for (int elem : arr) {
        counts[elem - shift] += 1;
    }

    // Обновляем вектор подсчетов до индексов в отсортированном массиве
    int startingIndex = 0;
    for (int i = 0; i < K + 1; i++) {
        int count = counts[i];
        counts[i] = startingIndex;
        startingIndex += count;
    }

    // Создаем отсортированный массив
    std::vector<int> sortedArray(arr.size());
    for (int elem : arr) {
        sortedArray[counts[elem - shift]] = elem;
        counts[elem - shift] += 1;
    }

    // Копируем отсортированный массив обратно в оригинальный массив
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = sortedArray[i];
    }
}

void countingSortByDigit(std::span<int> arr, int exp)
{
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(std::span<int> arr) {
    int maxElem = *std::ranges::max_element(arr);

    for (int exp = 1; maxElem / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

void bucketSort(std::vector<int>& arr, int K) {
    if (arr.empty()) return;

    int shift = *std::min_element(arr.begin(), arr.end());
    int maxValue = *std::max_element(arr.begin(), arr.end()) - shift;

    std::vector<std::vector<int>> buckets(K);

    double bucketSize = static_cast<double>(maxValue) / K;
    if (bucketSize < 1) {
        bucketSize = 1.0;
    }

    for (int elem : arr) {
        int index = static_cast<int>((elem - shift) / bucketSize);
        if (index == K) {
            buckets[K - 1].push_back(elem);
        }
        else {
            buckets[index].push_back(elem);
        }
    }

    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
    }

    int index = 0;
    for (const auto& bucket : buckets) {
        for (int elem : bucket) {
            arr[index++] = elem;
        }
    }
}


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

    class Solution_sort_list {
    public:
        ListNode* tail = new ListNode();
        ListNode* nextSubList = new ListNode();

        ListNode* sortList(ListNode* head) {
            if (!head || !head->next) return head;
            int n = getCount(head);
            ListNode* start = head;
            ListNode dummyHead(0);

            for (int size = 1; size < n; size = size * 2) {
                tail = &dummyHead;
                while (start) {
                    if (!start->next) {
                        tail->next = start;
                        break;
                    }
                    ListNode* mid = split(start, size);
                    merge(start, mid);
                    start = nextSubList;
                }
                start = dummyHead.next;
            }

            return dummyHead.next;
        }

        ListNode* split(ListNode* start, int size) {
            ListNode* midPrev = start;
            ListNode* end = start->next;

            for (int index = 1; index < size && (midPrev->next || end->next);
                index++) {
                if (end->next) {
                    end = (end->next->next) ? end->next->next : end->next;
                }
                if (midPrev->next) {
                    midPrev = midPrev->next;
                }
            }
            ListNode* mid = midPrev->next;
            nextSubList = end->next;
            midPrev->next = nullptr;
            end->next = nullptr;
            return mid;
        }

        void merge(ListNode* list1, ListNode* list2) {
            ListNode dummyHead(0);
            ListNode* newTail = &dummyHead;
            while (list1 && list2) {
                if (list1->val < list2->val) {
                    newTail->next = list1;
                    list1 = list1->next;
                    newTail = newTail->next;
                }
                else {
                    newTail->next = list2;
                    list2 = list2->next;
                    newTail = newTail->next;
                }
            }
            newTail->next = (list1) ? list1 : list2;
            while (newTail->next) {
                newTail = newTail->next;
            }
            tail->next = dummyHead.next;
            tail = newTail;
        }

        int getCount(ListNode* head) {
            int cnt = 0;
            ListNode* ptr = head;
            while (ptr) {
                ptr = ptr->next;
                cnt++;
            }
            return cnt;
        }
    };
}

