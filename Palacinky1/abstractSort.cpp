#include "abstractSort.h"

void abstractSort::startTimer(){
	start = GetTickCount();
}

void abstractSort::stopTimer(){
	time += (GetTickCount() - start);
	flips += actualFlips;
	if (actualFlips < min){
		min = actualFlips;
	}
	if (actualFlips > max){
		max = actualFlips;
	}
}