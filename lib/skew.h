#include "leftistskew.h"

struct Node {
    int key;
    Node* left;
    Node* right;

    Node() { *this = NULL; }
    Node(int key) :
        key(key),
        left(nullptr),
        right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

class SkewHeap :
    virtual IHeap,
    virtual public ILeftistSkewHeap<Node>
{
protected:
    void inMeld(Node*& left, Node*& right) {
        Node* tmp = left->right;
        left->right = left->left;
        left->left = _meld(right, tmp);
    }
};