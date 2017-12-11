#pragma once

class IHeap {
    virtual void AddHeap(int key) = 0;
    virtual void Insert(int index, int key) = 0;
    virtual int GetMin(int index) = 0;
    virtual void ExtractMin(int index) = 0;
    virtual void Meld(int index1, int index2) = 0;
};