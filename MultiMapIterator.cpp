#include "MultiMapIterator.h"
#include "MultiMap.h"

// Constructor
// Best Case: Theta(m), Worst Case: Theta(m), Average Case: O(m)
// Explanation: The constructor initializes the iterator with the given MultiMap
MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	currentPos = 0;
	move();
}

// Move function
// Best Case: Theta(1), Worst Case: Theta(m), Average Case: O(m)
// Explanation: The move function advances the iterator to the next valid position,
// which may take linear time if the next valid position is far away.
void MultiMapIterator::move() {
	while (currentPos < col.m && (col.hashtable[currentPos] == NULL_TELEM || col.hashtable[currentPos] == DELETED_TELEM)) {
		currentPos++;
	}
}

// First function
// Best Case: Theta(1), Worst Case: Theta(m), Average Case: O(m)
// Explanation: The first function resets the iterator to the first valid element,
// which may take linear time if the first valid position is far away.
void MultiMapIterator::first() {
	currentPos = 0;
	move();
}

// Next function
// Best Case: Theta(1), Worst Case: Theta(m), Average Case: O(m)
// Explanation: The next function advances the iterator to the next valid position,
// which may take linear time if the next valid position is far away.
void MultiMapIterator::next() {
	if (!valid())
		throw std::exception();
	currentPos++;
	move();
}

// GetCurrent function
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: O(1)
// Explanation: Returns the element at the current position, which takes constant time.
TElem MultiMapIterator::getCurrent() const {
	if (!valid())
		throw std::exception();
	return col.hashtable[currentPos];
}

// Valid function
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: O(1)
// Explanation: Checks if the current position is within bounds, which takes constant time.
bool MultiMapIterator::valid() const {
	return currentPos < col.m;
}
