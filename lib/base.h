#pragma once

#include <iostream>

class IHeap {
    virtual void Insert(int key) = 0;
    virtual int GetMin() = 0;
    virtual void ExtractMin() = 0;
};