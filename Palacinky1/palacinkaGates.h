#pragma once
#include <iostream>
#include "abstractSort.h"
using namespace std;

#include <algorithm>
#include <array>
#include <random>
#include <chrono>

class palacinkaGates : public abstractSort{
	vector<int>::iterator plusOne;
	vector<int>::iterator minusOne;
public:
	palacinkaGates(vector<int> nVector);
	palacinkaGates(){};
	bool isFree(vector<int>::iterator pos);
	bool isInBlock(vector<int>::iterator pos);
	vector<int>::iterator startOfBlock(vector<int>::iterator pos);
	vector<int>::iterator endOfBlock(vector<int>::iterator pos);
	bool inTheSameBlock(vector<int>::iterator pos1, vector<int>::iterator pos2);
	void doSort();
	~palacinkaGates();
};