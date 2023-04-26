#pragma once
#include <set>
class IdProvider
{

	int counter = 0;

	std::set<int> frees;
public:
	int Next() {
		return ++counter;
	}

	int Free(int value){
		frees.insert({ value });
	}
};

