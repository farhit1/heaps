#include "base.h"
#include <set>
#include <vector>

class StlHeap : virtual IHeap {
public:
    std::vector<std::set<int> > heaps;

    void AddHeap(int key) {
        heaps.push_back(std::set<int> { key });
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
        for (int i : heaps[index2])
            heaps[index1].insert(i);
        heaps[index2].clear();
    }
};