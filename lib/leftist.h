#include "leftistskew.h"

class LeftistHeap :
    virtual IHeap,
    virtual public ILeftistSkewHeap
{
protected:

    void inMeld(Node*& left, Node*& right) {
        left->right = _meld(left->right, right);
        if (dist(left->right) > dist(left->left))
            std::swap(left->left, left->right);
    }
};