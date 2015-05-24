#pragma once
#include <iostream>
#include "abstractSort.h"
using namespace std;

#include <algorithm>
#include <array>
#include <random>
#include <chrono>

class palacinka : public abstractSort{
public:
	palacinka(vector<int> nVector);
	palacinka(){};
	void doSort();
	~palacinka();
};

