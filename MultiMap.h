#pragma once
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int, int>(-111111, -111111)
#define DELETED_TVALUE -999999
#define DELETED_TELEM pair<int, int>(-999999, -999999)

class MultiMapIterator;

class MultiMap {
    friend class MultiMapIterator;

private:
    TElem* hashtable;
    int nbElems, m;
    float c1, c2; // coefficients for the hash function

    // Helper function for hash function
    int hFunction(int x, int i) const;

public:
    MultiMap();
    ~MultiMap();

    void resize();

    void add(TKey c, TValue v);
    bool remove(TKey c, TValue v);
    vector<TValue> search(TKey c) const;

    int size() const;
    bool isEmpty() const;
    MultiMapIterator iterator() const;
};
