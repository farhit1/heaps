#include "gtest/gtest.h"
#include <time.h>
#include <algorithm>
#include <vector>

#define amount()        this->size()
#define heapsize(x)     this->_heapsize(x)
#define add()           this->_add();
#define push(x, y)      this->_push(x, y);
#define check(x)        ASSERT_EQ((*this)._get(x), (*this)._ans(x));
#define pop(x)          this->_pop(x);
#define meld(x, y)      this->_meld(x, y);
#define genval()        rnd(-1000000, 1000000)		

using testing::Types;

// returns [l; r]
int rnd(int l, int r) {
	int val = rand() % (r - l + 1);
	return l + val;
}

template<typename T>
class HeapTest : public ::testing::Test {
private:
	std::vector<T*> _heaps;
	std::vector<StlHeap*> _goodHeaps;

public:
	// returns number of heaps
	size_t size() {
		return _heaps.size();
	}

	// returns size of i-th heap
	size_t _heapsize(size_t i) {
		return _goodHeaps[i]->size();
	}

	// adds empty heap
	void _add() {
		_heaps.push_back(new T());
		_goodHeaps.push_back(new StlHeap());
	}

	// inserts key into i-th heap
	void _push(size_t i, int key) {
		_heaps[i]->Insert(key);
		_goodHeaps[i]->Insert(key);
	}

	// returns min of i-th heap
	int _get(size_t i) {
		return _heaps[i]->GetMin();
	}

	// returns what should be min of i-th heap
	int _ans(size_t i) {
		return _goodHeaps[i]->GetMin();
	}

	// pops min from i-th heap
	void _pop(size_t i) {
		_heaps[i]->ExtractMin();
		_goodHeaps[i]->ExtractMin();
	}

	// heap_ind1 <- heap_ind2
	void _meld(size_t ind1, size_t ind2) {
		_heaps[ind1]->Meld(*_heaps[ind2]);
		_goodHeaps[ind1]->Meld(*_goodHeaps[ind2]);
	}

	HeapTest() = default;

	~HeapTest() {
		for (auto i : _heaps)
			delete i;
		for (auto i : _goodHeaps)
			delete i;
	}
};

// TESTS

typedef ::testing::Types<BinomialHeap, LeftistHeap, SkewHeap> Implementations;
TYPED_TEST_CASE(HeapTest, Implementations);

// small tests

TYPED_TEST(HeapTest, small1) {
	add();
	push(0, 1);
	check(0);
	push(0, 2);
	check(0);
	push(0, -1);
	check(0);
	pop(0);
	check(0);
	pop(0);
	check(0);
}

TYPED_TEST(HeapTest, small2) {
	add();
	add();
	push(0, genval());
	check(0);
	push(0, genval());
	check(0);
	push(1, genval());
	check(1);
	push(1, genval());
	check(1);
	meld(0, 1);
	check(0);
	pop(0);
	check(0);
	pop(0);
	check(0);
	pop(0);
	check(0);
}

// large tests

TYPED_TEST(HeapTest, large1) {
	add();
	size_t sizeOfTest = rnd(100000, 200000);
	for (size_t i = 0; i < sizeOfTest; i++) {
		push(0, genval());
		check(0);
	}
	for (size_t i = 0; i < sizeOfTest; i++) {
		check(0);
		pop(0);
	}
}

TYPED_TEST(HeapTest, large2) {
	add();
	size_t sizeOfTest = rnd(100000, 200000);
	for (size_t i = 0; i < sizeOfTest; i++) {
		enum { PUSH = 1, CHECK, POP };
		int operationType = rnd(1, 3);
		if (heapsize(0) == 0)
			operationType = PUSH;
		switch (operationType) {
			case PUSH:
				push(0, genval());
				break;
			case CHECK:
				check(0);
				break;
			case POP:
				pop(0);
				break;
			default:
				break;
		}
	}
}

TYPED_TEST(HeapTest, large3) {
	add();
	add();
	size_t sizeOfTest = rnd(100000, 200000);
	for (size_t i = 0; i < sizeOfTest; i++) {
		enum { PUSH1 = 1, PUSH2, CHECK1, CHECK2, POP1, POP2, MELD12, MELD21 };
		int operationType = rnd(1, 8);
		if (heapsize(0) == 0)
			operationType = PUSH1;
		else if (heapsize(1) == 0)
			operationType = PUSH2;

		switch (operationType) {
			case PUSH1:
				push(0, genval());
				break;
			case PUSH2:
				push(1, genval());
				break;
			case CHECK1:
				check(0);
				break;
			case CHECK2:
				check(1);
				break;
			case POP1:
				pop(0);
				break;
			case POP2:
				pop(1);
				break;
			case MELD12:
				meld(0, 1);
				break;
			case MELD21:
				meld(1, 0);
				break;
			default:
				break;
		}
	}
}

TYPED_TEST(HeapTest, large4) {
	size_t sizeOfTest = rnd(100000, 200000);
	for (size_t i = 0; i < sizeOfTest; i++) {
		enum { MELD = -2, NEWHEAP };
		int operationType = rnd(-2, amount() - 1);
		if (amount() < 2)
			operationType = -1;

		if (operationType == MELD) {
			int ind1 = rnd(0, amount() - 1);
			int ind2 = rnd(0, amount() - 2);
			if (ind2 >= ind1)
				ind2++;
			meld(ind1, ind2);
		}
		else if (operationType == NEWHEAP) {
			add();
		}
		else {
			enum { PUSH = 1, CHECK, POP };
			int operation = rnd(1, 3);
			if (heapsize(operationType) == 0)
				operation = PUSH;
			switch (operation) {
				case PUSH:
					push(operationType, genval());
					break;
				case CHECK:
					check(operationType);
					break;
				case POP:
					pop(operationType);
					break;
				default:
					break;
			}
		}
	}
}
/*
TYPED_TEST(HeapTest, xlarge) {
	add();
	add();
	size_t sizeOfTest = rnd(10000000, 20000000);
	for (size_t i = 0; i < sizeOfTest; i++) {
		int operationType = rnd(1, 8);

		if (heapsize(0) == 0)
			operationType = 1;
		else if (heapsize(1) == 0)
			operationType = 2;
		if (operationType == 1 && heapsize(0) > 100000)
			operationType = 5;
		if (operationType == 2 && heapsize(1) > 100000)
			operationType = 6;

		switch (operationType) {
			case 1:
				push(0, genval());
				break;
			case 2:
				push(1, genval());
				break;
			case 3:
				check(0);
				break;
			case 4:
				check(1);
				break;
			case 5:
				pop(0);
				break;
			case 6:
				pop(1);
				break;
			case 7:
				meld(0, 1);
				break;
			case 8:
				meld(1, 0);
				break;
			default:
				break;
		}
	}
}*/