#include "base.h"
#include <vector>

class SkewHeap : virtual IHeap {
public:
    class Node {
    public:
        int key;
        Node *l, *r;

        Node() = default;
        Node(int key) :
                key(key),
                l(NULL),
                r(NULL) {}

        Node& operator=(const Node& other) = default;
    };

    std::vector<Node*> heaps;

    Node* _meld(Node* l, Node* r) {
        if (l == NULL)
            return r;
        if (r == NULL)
            return l;
        if (l->key > r->key)
            std::swap(r, l);

        Node* tmp = l->r;
        l->r = l->l;
        l->l = _meld(r, tmp);

        return l;
    }

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