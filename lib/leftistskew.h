#pragma once

#include "base.h"

template<typename T>
class ILeftistSkewHeap : virtual public IHeap {
protected:
    virtual void inMeld(T*& left, T*& right) = 0;

    T* _meld(T*& left, T*& right) {
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        if (left->key > right->key)
            std::swap(left, right);

        inMeld(left, right);

        return left;
    }

    T* _heap;

public:
	ILeftistSkewHeap() :
		_heap(NULL) {}

    void Insert(int key) {
    	T* tmp = new T(key);
        _heap = _meld(_heap, tmp);
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