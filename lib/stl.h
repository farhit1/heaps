#include "base.h"
#include <iostream>
#include <set>

class StlHeap : virtual public IHeap {
private:
    std::multiset<int> _heap;

public:
    void Insert(int key) {
        _heap.insert(key);
    }

    size_t size() {
        return _heap.size();
    }

    int GetMin() {
        return *_heap.begin();
    }

    void ExtractMin() {
        _heap.erase(_heap.begin());
    }

    void Meld(IHeap& other) {
        if (_heap.size() < dynamic_cast<StlHeap&>(other)._heap.size())
            std::swap(_heap, dynamic_cast<StlHeap&>(other)._heap);
        _heap.insert(dynamic_cast<StlHeap&>(other)._heap.begin(), dynamic_cast<StlHeap&>(other)._heap.end());
        dynamic_cast<StlHeap&>(other)._heap.clear();
    }
};