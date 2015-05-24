#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "palacinka.h"
#include "palacinkaGates.h"
#include "palacinkaGatesOpt.h"
#include "palacinkaGatesOpt2.h"
#include "twoDimensional.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>


using namespace std;
float pocet = 2500.0f;
int from = 0;
int to = 1000;

vector<int> generator(int size){
	vector<int> result;
	for (int i = 1; i <= size; i++){
		result.push_back(i);
	}
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	shuffle(result.begin(), result.end(), default_random_engine(seed));

	return result;
}
vector<vector<int>> generator2D(int x, int y){
	vector<vector<int>> result;
	vector<int> tmp;
	for (int i = 1; i <= (x*y); i++){
		tmp.push_back(i);
	}
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(tmp.begin(), tmp.end(), default_random_engine(seed));
	int index = 0;
	for (int i = 0; i < y; i++){
		result.push_back({});
		for (int j = 0; j < x; j++){
			result[i].push_back(tmp[index++]);
		}
	}
	return result;
}
int main() {

	// 1D test

	ofstream myfile1;
	ofstream myfile2;
	ofstream myfile3;
	ofstream myfile4;
	ofstream myfile5;
	ofstream myfile6;
	ofstream myfile7;
	ofstream myfile8;
	
	myfile1.open("palacinka.txt", fstream::out | fstream::app);
	myfile2.open("gates.txt", fstream::out | fstream::app);
	myfile3.open("optgates.txt", fstream::out | fstream::app);
	myfile4.open("optgates2.txt", fstream::out | fstream::app);

	myfile5.open("palacinkatimes.txt", fstream::out | fstream::app);
	myfile6.open("gatestimes.txt", fstream::out | fstream::app);
	myfile7.open("optgatestimes.txt", fstream::out | fstream::app);
	myfile8.open("optgatestimes2.txt", fstream::out | fstream::app);

	vector<float> palacinkaTimes;
	vector<float> gatesTimes;
	vector<float> optGatesTimes;
	vector<float> optGates2Times;

	vector<float> palacinkaFlips;
	vector<float> gatesFlips;
	vector<float> optGatesFlips;
	vector<float> optGates2Flips;
	
	vector<int> a = { 100, 500, 1000, 5000, 10000, 15000, 50000, 100000, 150000 };
	for each (int i in a){
		abstractSort* pal = new palacinka();
		abstractSort* gates = new palacinkaGates();
		abstractSort* opt = new palacinkaGatesOpt();
		abstractSort* opt2 = new palacinkaGatesOpt2();
		for (int j = 0; j < (int)pocet; j++){
			vector<int> pole = generator(i);
			pal->setVector(pole);
			gates->setVector(pole);
			opt->setVector(pole);
			opt2->setVector(pole);
			pal->sort();
			gates->sort();
			opt->sort();
			opt2->sort();
		}

		myfile1 << to_string(i) + " " + to_string((float)pal->getFlips() / (float)pocet) << endl;
		myfile2 << to_string(i) + " " + to_string((float)gates->getFlips() / (float)pocet) << endl;
		myfile3 << to_string(i) + " " + to_string((float)opt->getFlips() / (float)pocet) << endl;
		myfile4 << to_string(i) + " " + to_string((float)opt2->getFlips() / (float)pocet) << endl;

		myfile5 << to_string(i) + " " + to_string((float)pal->getTime() / (float)pocet) << endl;
		myfile6 << to_string(i) + " " + to_string((float)gates->getTime() / (float)pocet) << endl;
		myfile7 << to_string(i) + " " + to_string((float)opt->getTime() / (float)pocet) << endl;
		myfile8 << to_string(i) + " " + to_string((float)opt2->getTime() / (float)pocet) << endl;
	}

	// 2D test

	ofstream myfile9;
	
	myfile9.open("vysledky2D.txt", fstream::out | fstream::app);
	
	for (int j = 2; j < 11; j++){
		for (int k = 2; k < 11; k++){
			if ((j == 2 && k == 2) || (j == 4 && k == 4) || (j == 4 && k == 8) || (j == 8 && k == 4) || (j == 8 && k == 8)){
				continue;
			}
			int min = INT_MAX;
			int max = INT_MIN;
			int actualFlips = 0;
			for (int i = from; i < to; i++){
				abstractSort* twoDim = new twoDimensional(generator(j*k), j, k);
				twoDim->sort();
				actualFlips += twoDim->getActualFlips();
				if (twoDim->getActualFlips() < min){
					min = twoDim->getActualFlips();
				}
				if (twoDim->getActualFlips() > max){
					max = twoDim->getActualFlips();
				}
			}
			myfile9 << j << " " << k << " " << min << " " << max << " " << (actualFlips / to) << endl;
		}
	}


	system("pause");
	return 0;
}