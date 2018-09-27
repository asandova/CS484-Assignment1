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
#include <cstring>
#include "LargeNum.h"
#include "Proability.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc > 1) {
		int i = 0;
		string successProb;
		string trials;
		string success;
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
			cout << "insufficent data passed" << endl;
			exit(1);
		}
		else {
			//bandwidth of the link
			//bandwidth of for each user
			//Number of users = 
			//proabiliy of user idle = q
			//target number of users = IntegerSeccess

			int IntSuccess = stoi(success,nullptr,10);
			int IntTrials = stoi(trials,nullptr,10);
			float FloatProb = stof(successProb,nullptr);

			LargeNum resultSingle = Binomial(IntTrials, IntSuccess, FloatProb);
			cout << "The proablity of a single Success: " << resultSingle << endl;
			LargeNum resultSum = BinomialSum(IntTrials, IntSuccess, FloatProb);
			cout << "The proablity of a Cumlative Success(x<="<< success <<"): " << resultSum << endl;
		}
	}
	else {
		
		LargeNum t1 = LargeNum(0.0123f);
		LargeNum t2 = LargeNum(2.1f);
		LargeNum t3 = LargeNum(12.47f);
		LargeNum t4 = LargeNum(5.3f);
		LargeNum t5 = LargeNum(0.25f);
		LargeNum t6 = LargeNum(0.2f);
		//LargeNum t3 = LargeNum("1.3");
		//LargeNum t3 = LargeNum("0.001");
		/*
		LargeNum Q;
		Q = t1 / t2;
		cout << Q << endl;
		Q = t3 / t4;
		cout << Q << endl;
		Q = t5 / t6;
		cout << Q << endl;
		*/
		//LargeNum diff = t1 - t2;
		//cout << diff << endl;
		
		LargeNum answer;
		answer = Binomial(10, 3, 0.8f);
		cout << answer << endl;
		answer = BinomialSum(10, 3, 0.8f);
		cout << answer << endl;
		
	}
	return 0;
}