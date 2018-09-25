/*
	File: main.cpp
	Author: August B. Sandoval
	Class: CS484
	Date: 2018-9-11

	Purpose:
		This is the main file for the CS484 programming assignment 1.
		This assignment is to implementing our own Large Number class for computation
		This assignment will also support Factorial and Binomial formulas that work natively with the custom Large Number class
*/

#include <stdio.h>
#include "LargeNum.h"
#include "Proability.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc > 1) {
		int i = 0;
		string successProb = string();
		string trials = string();
		string success = string();
		while (i < argc) {
			if ( strcmp(argv[i], "-p") == 0 ) {
				successProb = string(argv[i + 1]);
				i++;
			}
			if( strcmp(argv[i], "-t") == 0) {
				trials = string(argv[i+1]);
				i++;
			}
			if (strcmp(argv[i], "-s") == 0) {
				success = string(argv[i + 1]);
				i++;
			}
			i++;
		}
		if (successProb.empty() || trials.empty() || success.empty()) {
			cout << "insufficent data passed";
			exit(1);
		}
		else {
			LargeNum result = BinomialSum(trials, success, successProb);
			cout << result << endl;
		}
	}
	else {
		LargeNum t1 = LargeNum(0.02f);
		LargeNum t2 = LargeNum(2.0f);
		//LargeNum t3 = LargeNum("1.3");
		//LargeNum t3 = LargeNum("0.001");
		//cout << t3 << endl;

		LargeNum Q = t1 / t2;
		cout << Q << endl;
		//LargeNum diff = t1 - t2;
		//cout << diff << endl;
		LargeNum answer = Binomial(10, 2, 0.5f);
		cout << answer << endl;
	}
	return 0;
}