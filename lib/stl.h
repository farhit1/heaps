#include "base.h"
#include <set>
#include <vector>

class StlHeap : virtual IHeap {
public:
    std::vector<std::multiset<int> > heaps;

    void AddHeap(int key) {
        heaps.push_back(std::multiset<int>());
        heaps.back().insert(key);
    }

    void Insert(int index, int key) {
        heaps[index].insert(key);
    }

    int GetMin(int index) {
        return *heaps[index].begin();
    }

    void ExtractMin(int index) {
        heaps[index].erase(heaps[index].begin());
    }

    void Meld(int index1, int index2) {
        if (heaps[index1].size() < heaps[index2].size())
            swap(heaps[index1], heaps[index2]);
        heaps[index1].insert(heaps[index2].begin(), heaps[index2].end());
        heaps[index2].clear();
    }
};