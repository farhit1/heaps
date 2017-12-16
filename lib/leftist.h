#include "leftistskew.h"

struct DistNode {
    int key;
    int dist;
    DistNode* left;
    DistNode* right;

    DistNode() { *this = NULL; }
    DistNode(int key) :
        key(key),
        dist(0),
        left(nullptr),
        right(nullptr) {}

    ~DistNode() {
        delete left;
        delete right;
    }
};

class LeftistHeap :
    virtual IHeap,
    virtual public ILeftistSkewHeap<DistNode>
{
protected:
    int dist(DistNode* left) {
        if (left == nullptr)
            return 0;
        return left->dist;
    }

    void inMeld(DistNode*& left, DistNode*& right) {
        left->right = _meld(left->right, right);
        if (dist(left->right) > dist(left->left))
            std::swap(left->left, left->right);
    }
};