// Created: 2025-05-15
#include "MyUtils.hpp"

/*  */

//Below is the interface for Iterator, which is already defined for you.
// DO NOT modify the interface for Iterator.

class Iterator {
	struct Data;
	Data *data;

public:
	Iterator(const vector<int> &nums);
	Iterator(const Iterator &iter);

	// Returns the next element in the iteration.
	int next();

	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int> &nums) : Iterator(nums) {
		hasNext_val = Iterator::hasNext();
		if(hasNext_val) next_val = Iterator::next();
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.
	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return next_val;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		int temp = next_val;
		hasNext_val = Iterator::hasNext();
		if(hasNext_val) next_val = Iterator::next();
		return temp;
	}

	bool hasNext() const {
		return hasNext_val;
	}

private:
	int next_val;
	bool hasNext_val;
};

int main() { }