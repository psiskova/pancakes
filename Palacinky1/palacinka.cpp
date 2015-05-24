#include "palacinka.h"
#include "abstractSort.h"
#include <iostream>
using namespace std;

#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#include <random>
#include <array>
palacinka::palacinka(vector<int> nVector){
	setVector(nVector);
}


palacinka::~palacinka(){
}

void palacinka::doSort(){
	for (int i = pole.size(); i > 1; i--) {
		while ((find(pole.begin(), pole.end(), i) + 1) == pole.begin() + i && i > 1){
			i--;
		}
		if (i == 1) {
			break;
		}
		if ((find(pole.begin(), pole.end(), i) + 1) != pole.begin() + 1){
			reverse(pole.begin(), (find(pole.begin(), pole.end(), i)) + 1);
			actualFlips++;
		}
		reverse(pole.begin(), pole.end() - (pole.size() - i));
		actualFlips++;
	}
}