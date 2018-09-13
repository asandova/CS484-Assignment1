
#include <iostream>
#include <stdio.h>
#include "LargeNum.h"

using namespace std;


LargeNum::LargeNum() {
	LN_Integer = string();
	LN_Fraction = string();
}
LargeNum::LargeNum(int INum) {
	char *temp;
	itoa(INum, temp, 10);
	LN_Integer = string(temp);
	LN_Fraction = string();
}
LargeNum::LargeNum(string strNum) {
	if (!validStr(strNum)) {
		cout << "ERROR: Invalid Number" << endl;
		cout << "Exiting" << endl;
	}
	else {
		int decimalPointLoc = 0;
		for (decimalPointLoc; decimalPointLoc < strNum.size(); decimalPointLoc++) {
			
		}
	}
}
LargeNum::LargeNum(float fnum) {}


LargeNum LargeNum::pow(const LargeNum& num, int n) {
	//add code here
	return num;
}

ostream& operator<<(ostream& out, LargeNum& num) {
	out << num.LN_Integer;
	return out;
}
//Arithmatic operators
LargeNum LargeNum::operator+(const LargeNum& num2) {

}
LargeNum LargeNum::operator-(const LargeNum& num2) {}
LargeNum LargeNum::operator*(const LargeNum& num2) {}
LargeNum LargeNum::operator/(const LargeNum& num2) {}

//boolean Operators
bool LargeNum::operator==(const LargeNum& num2) {}
bool LargeNum::operator<=(const LargeNum& num2) {}
bool LargeNum::operator>=(const LargeNum& num2) {}
bool LargeNum::operator!=(const LargeNum& num2) {}


LargeNum LargeNum::toLarge(int n) {
	string Lnum = string();
	while (n > 0) {
		int temp = n % 10;
		n /= 10;
		Lnum += (char)('0' + temp);
	}
	return Lnum;
}
LargeNum LargeNum::toLarge(float n) {}
int LargeNum::toInt() {}
float LargeNum::toFloat() {}

bool LargeNum::validStr(string s) {
	int numberOfDecimalPoints = 0;
	string::iterator itr;
	for (itr = s.begin(); itr != s.end(); ++itr) {
		if (!isdigit(*itr)) {
			if (*itr == '.' && numberOfDecimalPoints < 1) {
				numberOfDecimalPoints++;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}