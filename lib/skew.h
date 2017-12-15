#include "base.h"
#include <vector>

class SkewHeap : virtual IHeap {
private:
    struct Node {
        int key;
        Node *l, *r;

        Node() = default;
        Node(int key) :
                key(key),
                l(NULL),
                r(NULL) {}

        Node& operator=(const Node& other) = default;

        ~Node() {
            delete l;
            delete r;
        }
    };

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

    std::vector<Node*> heaps;

public:
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
        heaps[index1] = _meld(heaps[index1], heaps[index2]);
        heaps[index2] = NULL;
    }

    ~SkewHeap() {
        for (Node* i : heaps)
            delete i;
    }
};