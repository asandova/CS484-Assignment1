
#include "Proability.h"
#include "LargeNum.h"
#include <vector>

using namespace std;

vector<LargeNum> Factorials = vector<LargeNum>();

LargeNum factorial(int n) {
	if (Factorials.empty()) {
		Factorials.push_back(LargeNum(1));
	}


	if (n == 0) {
		return Factorials[0];
	}
	else if (n < Factorials.size()) {
		return Factorials[n - 1];
	}
	else {
		expandFactorial(n);
		return Factorials.back();
	}

}

void expandFactorial(int n) {
	if (n < Factorials.size()) {
		return;
	}
	else {
		int dif = n - Factorials.size();
		int current = Factorials.size();
		for (int i = 0; i < dif; i++, current++) {
			LargeNum temp = Factorials[current - 2] * current;
			Factorials.push_back(temp);
		}

	}
}

LargeNum Binomial(int n, int x, float p) {
	LargeNum result;
	LargeNum trials = LargeNum(n);
	LargeNum successes = LargeNum(x);
	LargeNum proability = LargeNum(p);
	//Do something

	LargeNum fact, success, fail;

	fact = factorial(n) / (factorial(n - x)*factorial(x));
	success =success.pow(x);
	fail = (LargeNum(1) - successes);
	fail = fail.pow( n - x);

	return result;
}

LargeNum BinomialSum(int n, int x, float p) {
	LargeNum result = Binomial(n,0,p);
	//Do something
	for (int i = 1; i < x; i++) {
		result = result + Binomial(n, i, p);
	}
	return result;
}