/*
	File: main.cpp
	Author: August B. Sandoval
	Class: CS484
	Date: 2018-9-11

	Purpose:
		This is the main file for the CS484 programming assignment 1.
		This assignment is to implementent our own Large Number class for computation
		This assignment will also support Factorial and Binomial formulas that work natively with the custom Large Number class
*/

#include <stdio.h>
#include "LargeNum.h"

using namespace std;

int main() {
	LargeNum t1 = LargeNum(155);
	LargeNum t2 = LargeNum(251.250f);
	LargeNum t3 = LargeNum("152.3256");

	cout << t1 << endl;
	cout << t2 << endl;
	cout << t3 << endl;
	LargeNum Sum = t1 + t2;
	cout << Sum << endl;
	return 0;
}