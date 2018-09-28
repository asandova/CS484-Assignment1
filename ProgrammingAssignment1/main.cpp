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
	bool test = false;
	bool active = false;
	bool idle = false;
	float Link;
	float user;
	string successProb;
	string failProb;
	string Total;
	string target;
	if (argc > 1) {
		int i = 0;
		while (i < argc) {
			if ( strcmp(argv[i], "-p") == 0 ) {
				successProb = string(argv[i + 1]);
				i++;
			}
			if( strcmp(argv[i], "-t") == 0) {
				Total = string(argv[i+1]);
				i++;
			}
			if (strcmp(argv[i], "-s") == 0) {
				target = string(argv[i + 1]);
				i++;
			}
			if(strcmp(argv[i], "-test") ==0){
				test = true;
			}
			if(strcmp(argv[i], "-active") == 0){
				if(idle){
					cout << "already genenerated active proability from idle value.\nIgnoring value" << endl;
				}else{
					successProb = string(argv[i + 1]);
					active = true;
					i++;
				}
			}
			if(strcmp(argv[i], "-idle") == 0){
				if(active){
					cout << "already genenerated idle proability from avtive value.\nIgnoring value" << endl;
				}else{
					failProb = string(argv[i + 1]);
					idle = true;
					i++;
				}
			}
			if(strcmp(argv[i], "-bwu") == 0){
				user = stof(argv[i + 1], nullptr);
				i++;
			}
			if(strcmp(argv[i], "-bwl") == 0){
				Link = stof(argv[i + 1], nullptr);
				i++;
			}

			i++;
		}
		if(test){
			if (successProb.empty() || Total.empty() || target.empty()) {
				cout << "insufficent data passed" << endl;
				exit(1);
			}else {
				int IntSuccess = stoi(target,nullptr,10);
				int IntTotal = stoi(Total,nullptr,10);
				float FloatProb = stof(successProb,nullptr);

				LargeNum resultSingle = Binomial(IntTotal, IntSuccess, FloatProb);
				cout << "The proablity of a single Success: " << resultSingle << endl;
				LargeNum resultSum = BinomialSum(IntTotal, IntSuccess, FloatProb);
				cout << "The proablity of a Cumlative Success(x<="<< target <<"): " << resultSum << endl;
				exit(0);
			}
		}
		else {
			//bandwidth of the link
			//bandwidth of for each user
			//Number of users = 
			//proabiliy of user idle = q
			//target number of users = IntegerSeccess
			LargeNum activeProb;
			if (active) {
				activeProb = LargeNum(successProb);
			}
			else {
				activeProb = LargeNum(1) - LargeNum(failProb);
			}
			int targetVal = stoi(target, nullptr, 10);
			int Totalval = stoi(Total, nullptr, 10);
			LargeNum result;
			result = BinomialSum( Totalval,targetVal-1,activeProb.toFloat());
			result = LargeNum(1) - result;
			cout << "The proabiliy of active users <=" << target <<": "<< result << endl;
		}
	}

	return 0;
}