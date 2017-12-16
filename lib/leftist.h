#include "leftistskew.h"

class LeftistHeap :
    virtual IHeap,
    virtual public ILeftistSkewHeap
{
protected:
    Node* _meld(Node* l, Node* r) {
        if (l == NULL)
            return r;
        if (r == NULL)
            return l;
        if (l->key > r->key)
            std::swap(l, r);
        l->r = _meld(l->r, r);
        if (dist(l->r) > dist(l->l))
            std::swap(l->l, l->r);
        l->dist = std::min(dist(l->l), dist(l->r)) + 1;
        return l;
    }
};