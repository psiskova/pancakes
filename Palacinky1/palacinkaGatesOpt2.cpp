#include "palacinkaGatesOpt2.h"
#include "abstractSort.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <random>
#include <array>

using namespace std;

palacinkaGatesOpt2::palacinkaGatesOpt2(vector<int> nVector){
	setVector(nVector);
}


palacinkaGatesOpt2::~palacinkaGatesOpt2(){
}

bool palacinkaGatesOpt2::isFree(vector<int>::iterator &pos){
	if (pos == pole.begin()) {
		return !(*(pos + 1) == *pos % pole.size() + 1 || *(pos + 1) == *pos - 1 || (*pos == 1 && *(pos + 1) == pole.size()));
	}
	if (pos == pole.end() - 1) {
		return !(*(pos - 1) == *pos % pole.size() + 1 || *(pos - 1) == *pos - 1 || (*pos == 1 && *(pos - 1) == pole.size()));
	}
	if (*(pos - 1) == *pos % pole.size() + 1 || *(pos - 1) == *pos - 1 || (*pos == 1 && *(pos - 1) == pole.size())){
		return false;
	}
	if (*(pos + 1) == *pos % pole.size() + 1 || *(pos + 1) == *pos - 1 || (*pos == 1 && *(pos + 1) == pole.size())){
		return false;
	}
	return true;
}

bool palacinkaGatesOpt2::isInBlock(vector<int>::iterator &pos){
	return !isFree(pos);
}

vector<int>::iterator palacinkaGatesOpt2::startOfBlock(vector<int>::iterator &pos){
	vector<int>::iterator pom = pos;
	int adjacency;
	while (pom != pole.begin()){
		adjacency = abs(*pom - *(pom - 1));
		if (adjacency == 1 || adjacency == pole.size() - 1){
			pom--;
		}
		else {
			break;
		}
	}
	return pom;
}

vector<int>::iterator palacinkaGatesOpt2::endOfBlock(vector<int>::iterator &pos){
	vector<int>::iterator pom = pos;
	int adjacency;
	while (pom != pole.end() - 1){
		adjacency = abs(*pom - *(pom + 1));
		if (adjacency == 1 || adjacency == pole.size() - 1){
			pom++;
		}
		else {
			break;
		}
	}
	return pom;
}

bool palacinkaGatesOpt2::inTheSameBlock(vector<int>::iterator &pos1, vector<int>::iterator &pos2){
	return startOfBlock(pos1) == startOfBlock(pos2);
}

void palacinkaGatesOpt2::doSort(){
	while (true){
		plusOne = find(pole.begin(), pole.end(), (pole.at(0) % pole.size() + 1));
		minusOne = find(pole.begin(), pole.end(), pole.at(0) == 1 ? pole.size() : pole.at(0) - 1);
		// t is the first element
		// 1. t is free and t + 1 (t - 1) is free 
		// 2. t is free and t + 1 (t - 1) is the first element of a block
		if (isFree(pole.begin())){
			if (isFree(plusOne) || startOfBlock(plusOne) == plusOne){
				reverse(pole.begin(), plusOne);
				actualFlips++;
				continue;
			}
			if (isFree(minusOne) || startOfBlock(minusOne) == minusOne){
				reverse(pole.begin(), minusOne);
				actualFlips++;
				continue;
			}
			// 3. t is free and both (t+1) and (t-1) are the last elements of blocks
			if (isInBlock(plusOne) && endOfBlock(plusOne) == plusOne && isInBlock(minusOne) && endOfBlock(minusOne) == minusOne){
				if (plusOne < minusOne){
					reverse(pole.begin(), (plusOne + 1));
					actualFlips++;
					reverse(pole.begin(), plusOne);
					actualFlips++;
					reverse(pole.begin(), (minusOne + 1));
					actualFlips++;
					reverse(pole.begin(), startOfBlock(plusOne));
					actualFlips++;
					continue;
				}
				else {
					reverse(pole.begin(), (minusOne + 1));
					actualFlips++;
					reverse(pole.begin(), minusOne);
					actualFlips++;
					reverse(pole.begin(), (plusOne + 1));
					actualFlips++;
					reverse(pole.begin(), startOfBlock(minusOne));
					actualFlips++;
					continue;
				}
			}
		}
		// 4. t is in a block and t+1 (t-1) is free
		// 5. t is in a block and t+1 (t-1) is the first element of block (startOfBlock(plusOne) == plusOne)
		if (isInBlock(pole.begin())){
			if (startOfBlock(plusOne) == plusOne || isFree(plusOne)){
				reverse(pole.begin(), plusOne);
				actualFlips++;
				continue;
			}
			if (startOfBlock(minusOne) == minusOne || isFree(minusOne)){
				reverse(pole.begin(), minusOne);
				actualFlips++;
				continue;
			}
			// 6 and 7 
			if (!inTheSameBlock(pole.begin(), plusOne)){
				// 7. t is in block with last element x, t+1 (t-1) is the last element of another block and x+1 is in block
				vector<int>::iterator blockElem = find(pole.begin(), pole.end(), *endOfBlock(pole.begin()) == 1 ? pole.size() : *endOfBlock(pole.begin()) - 1);
				if (isInBlock(blockElem)){
					if (blockElem == startOfBlock(blockElem)) {
						reverse(pole.begin(), endOfBlock(pole.begin()) + 1);
						actualFlips++;
						reverse(pole.begin(), blockElem);
						actualFlips++;
						continue;
					}
					else {
						reverse(pole.begin(), blockElem + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) % pole.size() + 1));
						actualFlips++;
						continue;
					}
				}

				// 6. t is in a block with last element x, t+1 (t-1) is the last element of another block and x+1 (x-1) is free
				vector<int>::iterator singleElem = find(pole.begin(), pole.end(), *endOfBlock(pole.begin()) == 1 ? pole.size() : *endOfBlock(pole.begin()) - 1);
				if (isFree(singleElem)){
					if (singleElem < plusOne) {
						reverse(pole.begin(), singleElem + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) % pole.size() + 1));
						actualFlips++;
						reverse(pole.begin(), plusOne + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) == 1 ? pole.size() : pole.at(0) - 1));
						actualFlips++;
						continue;
					}
					else {
						int firstValue = pole.at(0);
						reverse(pole.begin(), singleElem + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) % pole.size() + 1));
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), firstValue) + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) % pole.size() + 1));
						actualFlips++;
						continue;
					}
				}
			}
			if (!inTheSameBlock(pole.begin(), minusOne)){
				// 7. t is in block with last element x, t+1 (t-1) is the last element of another block and x+1 is in block
				vector<int>::iterator blockElem = find(pole.begin(), pole.end(), *endOfBlock(pole.begin()) % pole.size() + 1);
				if (isInBlock(blockElem)){
					if (blockElem == startOfBlock(blockElem)) {
						reverse(pole.begin(), endOfBlock(pole.begin()) + 1);
						actualFlips++;
						reverse(pole.begin(), blockElem);
						actualFlips++;
						continue;
					}
					else {
						reverse(pole.begin(), blockElem + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) == 1 ? pole.size() : pole.at(0) - 1));
						actualFlips++;
						continue;
					}
				}
				// 6
				vector<int>::iterator singleElem = find(pole.begin(), pole.end(), *endOfBlock(pole.begin()) % pole.size() + 1);
				if (isFree(singleElem)){
					if (singleElem < minusOne) {
						reverse(pole.begin(), singleElem + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) == 1 ? pole.size() : pole.at(0) - 1));
						actualFlips++;
						reverse(pole.begin(), minusOne + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) % pole.size() + 1));
						actualFlips++;
						continue;
					}
					else {
						int firstValue = pole.at(0);
						reverse(pole.begin(), singleElem + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) == 1 ? pole.size() : pole.at(0) - 1));
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), firstValue) + 1);
						actualFlips++;
						reverse(pole.begin(), find(pole.begin(), pole.end(), pole.at(0) == 1 ? pole.size() : pole.at(0) - 1));
						actualFlips++;
						continue;
					}
				}
			}
		}
		break;
	}
	if (!(pole.at(0) == 1 && pole.at(pole.size() - 1) == pole.size())){
		if (find(pole.begin(), pole.end(), 1) < find(pole.begin(), pole.end(), pole.size())){
			reverse(pole.begin(), pole.end());
			actualFlips++;
		}
		if (find(pole.begin(), pole.end(), 1) > find(pole.begin(), pole.end(), pole.size())){
			reverse(pole.begin(), find(pole.begin(), pole.end(), pole.size()) + 1);
			actualFlips++;
			reverse(pole.begin(), pole.end());
			actualFlips++;
			reverse(pole.begin(), find(pole.begin(), pole.end(), 1) + 1);
			actualFlips++;
		}
	}
}