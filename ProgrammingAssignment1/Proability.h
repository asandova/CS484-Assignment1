#ifndef PROABILITY_H
#define PROABILITY_H

#include "LargeNum.h"
#include <vector>

extern std::vector<LargeNum> Factorials;

LargeNum factorial(int n);
void expandFactorial(int n);

LargeNum Binomial(int n, int x, float p);
LargeNum Binomial(LargeNum n, LargeNum x, LargeNum p);

LargeNum BinomialSum(int n, int x, float p);
LargeNum BinomialSum(LargeNum n, LargeNum x, LargeNum p);

#endif // !PROABILITY_H
