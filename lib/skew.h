#include "leftistskew.h"

class SkewHeap :
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

        Node* tmp = l->r;
        l->r = l->l;
        l->l = _meld(r, tmp);

        return l;
    }
};