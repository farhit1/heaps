#include "base.h"
#include <vector>

class BinomialHeap : virtual IHeap {
public:
    const int INF = 1e9;

    class Node {
    public:
        int key;
        std::vector<Node*> children;

        Node() = default;
        Node(int key) :
                key(key),
                children(std::vector<Node*>(0)) {};
    };

    class Heap {
    public:
        std::vector<Node*> roots;

        Heap() = default;
        Heap(const std::vector<Node*>& list) {
            roots = list;
        }

        Heap(int key) :
                roots(std::vector<Node*>{new Node(key)}) {}
    };

    Node* _nxt(Node* l, Node* r) {
        if (l->key < r->key) {
            l->children.push_back(r);
            return l;
        } else {
            r->children.push_back(l);
            return r;
        }
    }

    Heap* _meld(Heap* l, Heap* r) {
        int maxsize = std::max(l->roots.size(), r->roots.size());
        while (l->roots.size() < maxsize)
            l->roots.push_back(NULL);
        while (r->roots.size() < maxsize)
            r->roots.push_back(NULL);

        while (maxsize > 0 && l->roots.back() == NULL && r->roots.back() == NULL) {
            maxsize--;
            l->roots.pop_back();
            r->roots.pop_back();
        }

        Node* remainder = NULL;
        for (int i = 0; i < maxsize; i++) {
            int notnull = 0;
            if (remainder != NULL)
                ++notnull;
            if (l->roots[i] != NULL)
                ++notnull;
            if (r->roots[i] != NULL)
                ++notnull;

            if (notnull == 0)
                continue;
            if (notnull == 1) {
                if (r->roots[i] != NULL)
                    l->roots[i] = r->roots[i];
                if (remainder != NULL) {
                    l->roots[i] = remainder;
                    remainder = NULL;
                }
                continue;
            }
            if (notnull == 2) {
                Node *n1, *n2;
                if (l->roots[i] == NULL) {
                    n1 = r->roots[i];
                    n2 = remainder;
                }
                if (r->roots[i] == NULL) {
                    n1 = l->roots[i];
                    n2 = remainder;
                }
                if (remainder == NULL) {
                    n1 = l->roots[i];
                    n2 = r->roots[i];
                }
                l->roots[i] = NULL;
                remainder = _nxt(n1, n2);
            }
            if (notnull == 3) {
                remainder = _nxt(r->roots[i], remainder);
            }
        }
        if (remainder != NULL)
            l->roots.push_back(remainder);

        return l;
    }

    std::vector<Heap*> heaps;

    void AddHeap(int key) {
        heaps.push_back(new Heap(key));
    }

    void Insert(int index, int key) {
        heaps[index] = _meld(heaps[index], new Heap(key));
    }

    int GetMin(int index) {
        int ret = INF;
        for (auto i : heaps[index]->roots)
            if (i != NULL)
                ret = std::min(ret, i->key);
        return ret;
    }

    void ExtractMin(int index) {
        int ret = INF, where;
        for (int i = 0; i < heaps[index]->roots.size(); i++)
            if (heaps[index]->roots[i] != NULL && ret > heaps[index]->roots[i]->key) {
                ret = heaps[index]->roots[i]->key;
                where = i;
            }

        Heap* tmp = new Heap(heaps[index]->roots[where]->children);
        heaps[index]->roots[where] = NULL;

        heaps[index] = _meld(heaps[index], tmp);
    }

    void Meld(int index1, int index2) {
        heaps[index1] = _meld(heaps[index1], heaps[index2]);
    }
};