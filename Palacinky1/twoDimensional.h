#pragma once
#include "abstractSort.h"
#include <vector>
using namespace std;
struct coordinates
{
	int x;
	int y;
};

class twoDimensional: public abstractSort
{
	int x, y, k;
public:
	int getValue(coordinates c);
	int getIndex(coordinates c);
	coordinates getCoordinates(int index);
	void swap(coordinates c1, coordinates c2);
	bool firstSecondCol(coordinates c1, coordinates c2);
	bool firstLastCol(coordinates c1, coordinates c2);
	bool firstSecondRow(coordinates c1, coordinates c2);
	bool firstLastRow(coordinates c1, coordinates c2);
	bool areAdjacentInRow(coordinates c1, coordinates c2);
	bool areAdjacentInCol(coordinates c1, coordinates c2);
	bool sameRow(coordinates c1, coordinates c2);
	bool sameColumn(coordinates c1, coordinates c2);
	bool middle(coordinates c1, coordinates c2);
	bool evenMiddleRows(coordinates c1, coordinates c2);
	bool kOrKPlusOneRow(coordinates c1, coordinates c2);
	bool firstOrLastCol(coordinates c1, coordinates c2);
	bool firstOrLastRow(coordinates c1, coordinates c2);
	bool firstCol(coordinates c1, coordinates c2);
	bool lastCol(coordinates c1, coordinates c2);
	void doSort();
	void setVector(vector<int> nVector, int x, int y);
	twoDimensional(vector<int> nVector, int x, int y);
	twoDimensional(){};
	~twoDimensional();
};

