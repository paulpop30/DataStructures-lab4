#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	int currentPos;

	void move();

public:
	MultiMapIterator(const MultiMap& c);
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
