
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
	out << num.LN_Integer << "." << num.LN_Fraction;
	return out;
}
//Arithmatic operators
LargeNum LargeNum::operator+(const LargeNum& num1, const LargeNum& num2) {

}
LargeNum LargeNum::operator-(const LargeNum& num1, const LargeNum& num2) {}
LargeNum LargeNum::operator*(const LargeNum& num1, const LargeNum& num2) {}
LargeNum LargeNum::operator/(const LargeNum& num1, const LargeNum& num2) {}

//boolean Operators
bool LargeNum::operator==(const LargeNum& num1, const LargeNum& num2) {
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	if((num1_copy.LN_Integer.size() == num2_copy.LN_Integer.size() ) && (
		num1_copy.LN_Fraction.size() == num2_copy.LN_Fraction.size() )){
				string::iterator num1Itr = num1_copy.LN_Integer.begin();
				string::iterator num2Itr = num2_copy.LN_Integer.begin();
				for(; num1Itr != num1_copy.LN_Integer.end() || num2Itr != num2_copy.LN_Integer.end();
					 ++num1Itr, ++num2Itr ){
					if( *num1Itr != *num2Itr){
						return false;
					}
				}
				num1Itr = num1_copy.LN_Fraction.begin();
				num2Itr = num2_copy.LN_Fraction.begin();
				for(; num1Itr != LN_Fraction.end() || num2Itr != num2_copy.LN_Fraction.end();
					 ++num1Itr, ++num2Itr){
					if(*num1Itr != *num2Itr){
						return false;
					}
				}
				return true;
	}else{
		return false;
	}
}
bool LargeNum::operator<=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 < num2 || num1 == num2 ){
		return true;
	}else{
		return false;
	}
}
bool LargeNum::operator>=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 > num2 || num1 == num2){
		return true;
	}else{
		return false;
	}
}
bool LargeNum::operator!=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 == num2 ){
		return false;
	}else{
		return true;
	}
}
bool LargeNum::operator>(const LargeNum& num1, const LargeNum& num2) {
	if(num1.LN_Integer.size() > num2.LN_Integer.size()){


	}
	return true;
}
bool LargeNum::operator<(const LargeNum& num2){

	return true;
}

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
void LargeNum::removeZeros(){
	//Remove all non-significant zeros from both Integer and Fraction portion
	removeLeadingZeros();
	removeTailingZeros();
}

void LargeNum::removeTailingZeros(){
	//Removes all non-significant zeros in the Integer portion of the number
	//If the number has no significant digits then it ignore one zeros before the decimal point
	while(LN_Integer.front() != '0' && LN_Integer.size() > 1){
		LN_Integer.erase(0,1);
	}
}

void LargeNum::removeLeadingZeros(){
	//Removes all non-signigicant zeros in the Fraction protion of the number
	//If the number has no significat digits then it ignores one zero after the decimal point 
	while(LN_Fraction.back() != '0' && LN_Fraction.size() > 1){
		LN_Fraction.erase(LN_Fraction.size()-1, 1);
	}
}