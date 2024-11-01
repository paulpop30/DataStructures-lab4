#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Constructor
// Best Case: Theta(m), Worst Case: Theta(m), Average Case: O(m)
// Explanation: The constructor initializes the hashtable with m elements, setting each to NULL_TELEM.
// The number of operations is directly proportional to the size of the hashtable.
MultiMap::MultiMap() {
    this->nbElems = 0;
    this->m = 16;
    this->hashtable = new TElem[16];
    for (int i = 0; i < 16; i++)
        this->hashtable[i] = NULL_TELEM;
    this->c1 = 0.5; // coefficient c1 for the hash function
    this->c2 = 0.5; // coefficient c2 for the hash function
}

// Resize function
// Best Case: Theta(n + m), Worst Case: Theta(n + m), Average Case: O(n + m)
// Explanation: The resize operation involves creating a new hashtable of size 2 * m (which is O(m)),
// and rehashing all the current elements (which is O(n)). Since n can be close to m in a densely
// populated hashtable, the complexity is expressed as O(n + m).
void MultiMap::resize() {
    int newCap = this->m * 2;
    //cout << "Resize to " << newCap << endl;
    TElem* newArr = new TElem[newCap];
    for (int i = 0; i < newCap; i++)
        newArr[i] = NULL_TELEM;

    int oldM = this->m;
    this->m = newCap;
    for (int i = 0; i < oldM; i++) {
        if (this->hashtable[i] != NULL_TELEM && this->hashtable[i] != DELETED_TELEM) {
            int j = 0;
            int hValue = hFunction(this->hashtable[i].first, j);
            while (newArr[hValue] != NULL_TELEM) {
                j++;
                hValue = hFunction(this->hashtable[i].first, j); // Quadratic probing
            }
            newArr[hValue] = this->hashtable[i];
        }
    }

    delete[] hashtable;
    this->hashtable = newArr;
}

// Add function
// Best Case: Theta(1), Worst Case: Theta(m), Average Case: O(1)
// Explanation: In the best case, the target slot is empty on the first probe, so the element is added immediately.
// In the worst case, all slots may need to be probed , and if resize() is called, this also contributes to the worst-case complexity.

void MultiMap::add(TKey c, TValue v) {
    int j = 0;
    int hValue = hFunction(c, j);
    while (this->hashtable[hValue] != NULL_TELEM && this->hashtable[hValue] != DELETED_TELEM && j < m) {
        j++;
        hValue = hFunction(c, j); // Quadratic probing
    }

    if (j == m) {
        resize();
        add(c, v); // Retry add after resizing
    }
    else {
        this->hashtable[hValue] = TElem(c, v);
        this->nbElems++;
    }
}

// Remove function
// Best Case: Theta(1), Worst Case: Theta(m), Average Case: O(1)
// Explanation: In the best case, the element is found on the first probe, so it can be removed immediately.
// In the worst case, it might probe through the entire table due to hash collisions or the element being
// at the end of the probing sequence.
bool MultiMap::remove(TKey c, TValue v) {
    bool found = false;
    int j = 0;
    int hValue = hFunction(c, j);
    int posToDeleteFrom = -1;

    while (this->hashtable[hValue] != NULL_TELEM && !found && j < m) {
        if (this->hashtable[hValue].first == c && this->hashtable[hValue].second == v) {
            posToDeleteFrom = hValue;
            found = true;
        }
        else {
            j++;
            hValue = hFunction(c, j); // Quadratic probing
        }
    }

    if (found) {
        this->hashtable[posToDeleteFrom] = DELETED_TELEM;
        this->nbElems--;
    }

    return found;
}

// Search function
// Best Case: Theta(1), Worst Case: Theta(m), Average Case: O(1)
// Explanation: In the best case, the element is found on the first probe.
// In the worst case, it might probe through the entire table if the element does not exist or hash collisions occur.
vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> result;
    int j = 0;
    int hValue = hFunction(c, j);

    while (this->hashtable[hValue] != NULL_TELEM) {
        if (this->hashtable[hValue].first == c && this->hashtable[hValue] != DELETED_TELEM) {
            result.push_back(this->hashtable[hValue].second);
        }
        j++;
        hValue = hFunction(c, j); // Quadratic probing
    }

    return result;
}

// Size function
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: O(1)
// Explanation: Simply returns the nbElems member variable.
int MultiMap::size() const {
    return this->nbElems;
}

// IsEmpty function
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: O(1)
// Explanation: Simply checks if nbElems is zero.
bool MultiMap::isEmpty() const {
    return this->nbElems == 0;
}


MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

// Destructor
// Best Case: Theta(m), Worst Case: Theta(m), Average Case: O(m)
// Explanation: Deletes the hashtable array, which takes time proportional to m.
MultiMap::~MultiMap() {
    delete[] hashtable;
}

// Hash function
// Best Case: Theta(1), Worst Case: Theta(1), Average Case: O(1)
// Explanation: The hash function performs a fixed number of operations regardless of the input.
int MultiMap::hFunction(int x, int i) const {
    if (x < 0)
        x = -x;
    int secondPart = (this->c1 * i + this->c2 * i * i);
    return (x % m + secondPart) % m;
}
