#include "twoDimensional.h"
using namespace std;

twoDimensional::twoDimensional(vector<int> nVector, int x, int y)
{
	setVector(nVector, x, y);
	if (x % 2 == 0) {
		k = (x - 2) / 4;
	}
	else {
		k = (x - 1) / 2;
	}	
}

int twoDimensional::getValue(coordinates c){
	return pole[getIndex(c)];
}

int twoDimensional::getIndex(coordinates c){
	return (c.x )*y + c.y ;
}

coordinates twoDimensional::getCoordinates(int index){
	coordinates co;
	co.x = (int) index/ y;
	co.y = index % y;
	return co;
}

void twoDimensional::swap(coordinates c1, coordinates c2){
	int tmp = getValue(c1);
	pole[getIndex(c1)] = pole[getIndex(c2)];
	pole[getIndex(c2)] = tmp;
}

bool twoDimensional::firstSecondCol(coordinates c1, coordinates c2){
	return (c1.y == 0 && c2.y == 1) || (c1.y == 1 && c2.y == 0);
}
bool twoDimensional::firstLastCol(coordinates c1, coordinates c2){
	return (c1.y == 0 && c2.y == y - 1) || (c1.y == y - 1 && c2.y == 0);
}
bool twoDimensional::firstSecondRow(coordinates c1, coordinates c2){
	return (c1.x == 0 && c2.x == 1) || (c1.x == 1 && c2.x == 0);
}
bool twoDimensional::firstLastRow(coordinates c1, coordinates c2){
	return (c1.x == 0 && c2.x == x - 1) || (c1.x == x - 1 && c2.x == 0);
}
bool twoDimensional::areAdjacentInRow(coordinates c1, coordinates c2){
	return abs(c1.y - c2.y) == 1;
}
bool twoDimensional::areAdjacentInCol(coordinates c1, coordinates c2){
	return abs(c1.x - c2.x) == 1;
}
bool twoDimensional::sameRow(coordinates c1, coordinates c2){
	return c1.x == c2.x;
}
bool twoDimensional::sameColumn(coordinates c1, coordinates c2){
	return c1.y == c2.y;
}
bool twoDimensional::firstOrLastCol(coordinates c1, coordinates c2){
	return c1.y == 0 || c1.y == y-1;
}
bool twoDimensional::firstOrLastRow(coordinates c1, coordinates c2){
	return c1.x == 0 || c1.x == x - 1;
}
bool twoDimensional::firstCol(coordinates c1, coordinates c2){
	return c1.y == 0;
}

bool twoDimensional::lastCol(coordinates c1, coordinates c2){
	return c1.y == y - 1;
}

bool twoDimensional::middle(coordinates c1, coordinates c2){
	return c1.y == (y/2) - 1 || c1.y == y/2;
}

bool twoDimensional::evenMiddleRows(coordinates c1, coordinates c2){
	return (c1.x == 2 * k && c2.x == 2 * k + 1) || (c2.x == 2 * k && c1.x == 2 * k + 1);
}

bool twoDimensional::kOrKPlusOneRow(coordinates c1, coordinates c2){
	return (c1.x == 2 * k && c2.x == 2 * k) || (c2.x == 2 * k + 1 && c1.x == 2 * k + 1);
}

void twoDimensional::setVector(vector<int> nVector, int x, int y){
	abstractSort::setVector(nVector);
	this->x = x;
	this->y = y;
}

void twoDimensional::doSort(){
	// even number of rows
	if (x % 2 == 1) {
		for (int i = 0; i < pole.size(); i++){
			if (pole.at(i) == (i + 1)) {
				continue;
			}
			int indexInVector = find(pole.begin(), pole.end(), i + 1) - pole.begin();
			coordinates actualCoordinates = getCoordinates(i);
			coordinates newCoordinates = getCoordinates(indexInVector);
			if (sameRow(actualCoordinates, newCoordinates)) {
				// elements on the first and second column
				if (firstSecondCol(actualCoordinates, newCoordinates)){
					actualFlips += 32 * k + 1;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				// elements on the same row - adjacent
				if (areAdjacentInRow(actualCoordinates, newCoordinates)){
					actualFlips += 32 * k + 3;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				//  elements on the same row - not adjacent
				// the first and the last column - exception: -2 flips
				if (firstLastCol(actualCoordinates, newCoordinates)){
					actualFlips += 32 * k + 9;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				actualFlips += 32 * k + 11;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			if (sameColumn(actualCoordinates, newCoordinates)) {
				// duals
				if (y % 2 == 1) {
					// elements on the first and second row
					if (firstSecondRow(actualCoordinates, newCoordinates)){
						actualFlips += 32 * k + 1;
						swap(actualCoordinates, newCoordinates);
						continue;
					}
					// elements on the same column - adjacent
					if (areAdjacentInCol(actualCoordinates, newCoordinates)){
						actualFlips += 32 * k + 3;
						swap(actualCoordinates, newCoordinates);
						continue;
					}
					//  elements on the same column - not adjacent
					// the first and the last row - exception: -2 flips
					if (firstLastRow(actualCoordinates, newCoordinates)){
						actualFlips += 32 * k + 9;
						swap(actualCoordinates, newCoordinates);
						continue;
					}
					actualFlips += 32 * k + 11;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				// even number of columns
				if (middle(actualCoordinates, newCoordinates)){
					actualFlips += 32 * k + 37;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				if (firstOrLastCol(actualCoordinates, newCoordinates)){
					actualFlips += 32 * k + 43;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				actualFlips += 32 * k + 45;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			if (firstSecondCol(actualCoordinates, newCoordinates)){
				actualFlips += 32 * k + 33;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			if (areAdjacentInCol(actualCoordinates, newCoordinates)){
				actualFlips += 32 * k + 35;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			//  elements - not adjacent
			// the first and the last col - exception: -2 flips
			if (firstLastCol(actualCoordinates, newCoordinates)){
				actualFlips += 32 * k + 41;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			actualFlips += 32 * k + 43;
			swap(actualCoordinates, newCoordinates);
			continue;
		}
	}
	if ((x % 2 == 0) && (x % 4 != 0)){
		for (int i = 0; i < pole.size(); i++){
			if (pole.at(i) == (i + 1)) {
				continue;
			}
			int indexInVector = find(pole.begin(), pole.end(), i + 1) - pole.begin();
			coordinates actualCoordinates = getCoordinates(i);
			coordinates newCoordinates = getCoordinates(indexInVector);
			if (sameColumn(actualCoordinates, newCoordinates)) {
				// 2k + 1, 2k + 2 row - index from 0, so 2k, 2k+1 rows
				if (evenMiddleRows(actualCoordinates, newCoordinates)){
					// first column
					if (firstCol(actualCoordinates, newCoordinates)){
						actualFlips += 92 * k + 1;
						swap(actualCoordinates, newCoordinates);
						continue;
					}
					// other column
					actualFlips += 92 * k + 3;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				// first and last row
				if (firstLastRow(actualCoordinates, newCoordinates)){
					if (lastCol(actualCoordinates, newCoordinates)){
						actualFlips += 92 * k + 5;
						swap(actualCoordinates, newCoordinates);
						continue;
					}
					actualFlips += 92 * k + 7;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				actualFlips += 92 * k + 11;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			if (sameRow(actualCoordinates, newCoordinates)) {
				// 2k+1 or 2k+2 row
				if (kOrKPlusOneRow(actualCoordinates, newCoordinates)){
					// one element in first column
					if (actualCoordinates.y == 0 || newCoordinates.y == 0){
						actualFlips += 92 * k + 35;
						swap(actualCoordinates, newCoordinates);
						continue;
					}
					actualFlips += 92 * k + 37;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				// first or last row
				if (firstOrLastRow(actualCoordinates, newCoordinates)){
					actualFlips += 92 * k + 37;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				actualFlips += 92 * k + 45;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			if (evenMiddleRows(actualCoordinates, newCoordinates)){
				if (actualCoordinates.y == 0 || newCoordinates.y == 0){
					actualFlips += 92 * k + 33;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				actualFlips += 92 * k + 35;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			if (firstLastRow(actualCoordinates, newCoordinates)){
				if (actualCoordinates.y == y - 1 || newCoordinates.y == y - 1){
					actualFlips += 92 * k + 37;
					swap(actualCoordinates, newCoordinates);
					continue;
				}
				actualFlips += 92 * k + 39;
				swap(actualCoordinates, newCoordinates);
				continue;
			}
			actualFlips += 92 * k + 43;
			swap(actualCoordinates, newCoordinates);
			continue;
		}
	}
	cout << endl; 
	for (int j = 0; j < 30; j++){
		cout << pole.at(j) << " ";
		if ((j + 1) % 5 == 0){
			cout << endl;
		}
	}
	cout << actualFlips << endl;
}


twoDimensional::~twoDimensional()
{
}
