#include "base.h"
#include <iostream>
#include <set>

class StlHeap : virtual IHeap {
public:
    std::multiset<int> heap;

    void Insert(int key) {
        heap.insert(key);
    }

    int GetMin() {
        return *heap.begin();
    }

    void ExtractMin() {
        heap.erase(heap.begin());
    }

    void Meld(StlHeap& other) {
        if (heap.size() < other.heap.size())
            std::swap(heap, other.heap);
        heap.insert(other.heap.begin(), other.heap.end());
        other.heap.clear();
    }
};