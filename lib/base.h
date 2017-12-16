#pragma once

#include <iostream>

class IHeap {
public:
    virtual void Insert(int key) = 0;
    virtual int GetMin() = 0;
    virtual void ExtractMin() = 0;
    virtual void Meld(IHeap& other) = 0;
    virtual ~IHeap() {} 
};