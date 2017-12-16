#pragma once

#include "base.h"

class ILeftistSkewHeap : virtual public IHeap {
protected:
    struct Node {
        int key;
        int dist;
        Node *left, *right;

        Node() { *this = NULL; }
        Node(int key) :
                key(key),
                dist(0),
                left(nullptr),
                right(nullptr) {}

        ~Node() {
            delete left;
            delete right;
        }
    };

    int dist(Node *left) {
        if (left == nullptr)
            return 0;
        return left->dist;
    }

    virtual void inMeld(Node*& left, Node*& right) = 0;

    Node* _meld(Node* left, Node* right) {
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        if (left->key > right->key)
            std::swap(left, right);

        inMeld(left, right);

        return left;
    }

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
        _heap = _meld(_heap->left, _heap->right);
    }

    void Meld(IHeap& other) {
        _heap = _meld(_heap, dynamic_cast<ILeftistSkewHeap&>(other)._heap);
        dynamic_cast<ILeftistSkewHeap&>(other)._heap = nullptr;
    }

    ~ILeftistSkewHeap() {
        delete _heap;
    }
};