#ifndef PROABILITY_H
#define PROABILITY_H

#include "LargeNum.h"
#include <vector>

extern std::vector<LargeNum> Factorials;

LargeNum factorial(int);
void expandFactorial(int n);

LargeNum Binomial(int n, int x, float p);

LargeNum BinomialSum(int n, int x, float p);

#endif // !PROABILITY_H
