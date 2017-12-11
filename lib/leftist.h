#include "base.h"
#include <vector>

class LeftistHeap : virtual IHeap {
public:
    class Node {
    public:
        int key;
        int dist;
        Node *l, *r;

        Node() = default;
        Node(int key) :
                key(key),
                dist(0),
                l(NULL),
                r(NULL) {}
    };

    int dist(Node *l) {
        if (l == NULL)
            return 0;
        return l->dist;
    }

    Node* _meld(Node* l, Node* r) {
        if (l == NULL)
            return r;
        if (r == NULL)
            return l;
        if (l->key < r->key)
            std::swap(l, r);
        l->r = _meld(l->r, r);
        if (dist(l->r) > dist(l->l))
            std::swap(l->l, l->r);
        l->dist = std::min(dist(l->l), dist(l->r)) + 1;
        return l;
    }

    std::vector<Node*> heaps;

    void AddHeap(int key) {
        heaps.push_back(new Node(key));
    }

    void Insert(int index, int key) {
        heaps[index] = _meld(heaps[index], new Node(key));
    }

    int GetMin(int index) {
        return heaps[index]->key;
    }

    void ExtractMin(int index) {
        heaps[index] = _meld(heaps[index]->l, heaps[index]->r);
    }

    void Meld(int index1, int index2) {
        _meld(heaps[index1], heaps[index2]);
    }
};