#include "leftistskew.h"

class SkewHeap :
    virtual IHeap,
    virtual public ILeftistSkewHeap 
{
protected:

    void inMeld(Node*& left, Node*& right) {
        Node* tmp = left->right;
        left->right = left->left;
        left->left = _meld(right, tmp);
    }
};