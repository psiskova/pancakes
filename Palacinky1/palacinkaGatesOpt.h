#pragma once
#include <iostream>
#include "abstractSort.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

using namespace std;

class palacinkaGatesOpt : public abstractSort{
	vector<int>::iterator plusOne;
	vector<int>::iterator minusOne;
public:
	palacinkaGatesOpt(vector<int> nVector);
	palacinkaGatesOpt(){};
	bool isFree(vector<int>::iterator &pos);
	bool isInBlock(vector<int>::iterator &pos);
	vector<int>::iterator startOfBlock(vector<int>::iterator &pos);
	vector<int>::iterator endOfBlock(vector<int>::iterator &pos);
	bool inTheSameBlock(vector<int>::iterator &pos1, vector<int>::iterator &pos2);
	void doSort();
	~palacinkaGatesOpt();
};