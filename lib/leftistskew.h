#pragma once

#include "base.h"

class ILeftistSkewHeap : virtual IHeap {
protected:
    struct Node {
        int key;
        int dist;
        Node *l, *r;

        Node() { *this = NULL; }
        Node(int key) :
                key(key),
                dist(0),
                l(nullptr),
                r(nullptr) {}

        ~Node() {
            delete l;
            delete r;
        }
    };

    int dist(Node *l) {
        if (l == nullptr)
            return 0;
        return l->dist;
    }

    virtual Node* _meld(Node* l, Node* r) = 0;

    Node* _heap;

public:

	ILeftistSkewHeap() :
		_heap(NULL) {}

    void Insert(int key) {
        _heap = _meld(_heap, new Node(key));
    }

    int GetMin() {
        return _heap->key;
    }

    void ExtractMin() {
        _heap = _meld(_heap->l, _heap->r);
    }

    void Meld(ILeftistSkewHeap& other) {
        _heap = _meld(_heap, other._heap);
        other._heap = nullptr;
    }

    ~ILeftistSkewHeap() {
        delete _heap;
    }
};