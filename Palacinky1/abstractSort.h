#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <Windows.h>

using namespace std;

class abstractSort{
protected:
	long int flips = 0;
	long int actualFlips = 0;
	int time = 0;
	long int max = INT_MIN;
	long int min = INT_MAX;
	long int start;
	void startTimer();
	void stopTimer();
	virtual void doSort() = 0;
	void isSorted(){
		if (!is_sorted(pole.begin(), pole.end())){
			cout << "nie je usortene" << endl;
			vypis();
			system("pause");
		}
	}
public:
	vector<int> pole;
	void sort() {
		actualFlips = 0;
		startTimer();
		doSort();
		stopTimer();
		isSorted();
	}
	void setVector(vector<int> NPole){
		pole.clear();
		for (int i = 0; i < NPole.size(); i++){
			pole.push_back(NPole[i]);
		}
	}
	long int getFlips(){ return flips; }
	long int getActualFlips(){ return actualFlips; }
	int getTime(){ return time; }
	long int getMin(){ return min; }
	long int getMax(){ return max; }
	void vypis(){
		for (int& x : pole){
			cout << ' ' << x;
		}
		cout << endl;
	};
};

