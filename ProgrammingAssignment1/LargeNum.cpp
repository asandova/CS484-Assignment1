/*
	File: LargeNum.cpp
	Author: August B. Sandoval
	Class: CS484
	Prurpose: Contains the class implemtation of the class LargeNum
*/
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "LargeNum.h"

using namespace std;

LargeNum& LargeNum::complement() const{
	//This function preformes 9's complement on the given largeNumber
	LargeNum complement = LargeNum();
	LargeNum copy = *this;
	matchLength(copy, complement);

	string::reverse_iterator numIter = copy.LN_Fraction.rbegin(), 
		compIter = complement.LN_Fraction.rbegin();
	for (; numIter != copy.LN_Fraction.rend(); ++compIter, ++numIter) {
		*compIter = '9' - *numIter + '0';
	}

	numIter = copy.LN_Integer.rbegin();
	compIter = complement.LN_Integer.rbegin();
	for (; numIter != copy.LN_Integer.rend(); ++compIter, ++numIter) {
		*compIter = '9' - *numIter + '0';
	}
	return complement;
}

LargeNum::LargeNum() {
	LN_Integer = "0";
	LN_Fraction = "0";
	negative = false;
}
LargeNum::LargeNum(int INum) {
	if (INum < 0) {
		negative = true;
	}
	else {
		negative = false;
	}
	char *temp;
	itoa(INum, temp, 10);
	LN_Integer = string(temp);
	LN_Fraction = "0";
}
LargeNum::LargeNum(string strNum) {
	if (!validStr(strNum)) {
		cout << "ERROR: Invalid Number" << endl;
		cout << "Exiting" << endl;
		exit(-1);
	}
	else {
		int decimalPointLoc = 0;
		negative = false;
		int numBegin = 0;
		for (decimalPointLoc; decimalPointLoc < strNum.size(); decimalPointLoc++) {
			if (strNum[decimalPointLoc] == '-' && decimalPointLoc == 0) {
				negative = true;
				numBegin++;
			}
			if (strNum[decimalPointLoc] == '.') {
				LN_Integer = strNum.substr(numBegin, decimalPointLoc);
				LN_Fraction = strNum.substr(decimalPointLoc + 1, strNum.size());
				break;
			}
		}
	}
}
LargeNum::LargeNum(float fnum) {
	ostringstream sfloat;
	if (fnum < 0) {
		negative = true;
		fnum *= -1;
	}
	sfloat << fnum;
	string fullFloat = string(sfloat.str());

	for(int i = 0; i < fullFloat.size(); i++){
		if(fullFloat[i] == '.'){
			LN_Integer = fullFloat.substr(0, i);
			LN_Fraction = fullFloat.substr(i+1, fullFloat.size());
			return;
		}
	}
}

LargeNum& LargeNum::pow( int n) const {
	//add code here
	LargeNum product = *this;
	for(int i = 1; i < n; i++){
		product = *this * product;
	}
	return product;
}

ostream& operator<<(ostream& out, LargeNum& num) {
	if (num.negative) {
		out << "-";
	}
	out << num.LN_Integer << "." << num.LN_Fraction;
	return out;
}
//Arithmatic operators

//complete
LargeNum operator+(const LargeNum& num1, const LargeNum& num2) {
	//create copyies
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	LargeNum::matchLength(num1_copy, num2_copy);
	//initialize the result
	LargeNum sum = LargeNum();
	LargeNum::matchLength(num1_copy, sum);

	string num1_string = num1_copy.LN_Fraction;
	string num2_string = num2_copy.LN_Fraction;
	string sum_string = sum.LN_Fraction;
	int carry = 0;
	string::reverse_iterator num1Iter = num1_string.rbegin;
	string::reverse_iterator num2Iter = num2_string.rbegin;
	string::reverse_iterator sumIter = sum_string.rbegin;
	//This loop through the fraction protion of the number
	for (; num1Iter != num1_string.rend(); ++num1Iter, ++num2Iter, ++sumIter) {
		//Sums the the current column of the number and adding the carry
		int c = (*num1Iter - '0') + (*num2Iter - '0') + carry;
		//tests if the sum of the column is greater then 9
		if (c > 9) {
			//if true, then the remainder is put into the sum column and the rest is put into carry
			*sumIter = c % 10;
			carry = c / 10;
		}
		else {
			//if not greater then 9 then it is put into sum column
			*sumIter = char(c + '0');
			carry = 0;
		}
	}

	num1_string = num1_copy.LN_Integer;
	num2_string = num2_copy.LN_Integer;
	sum_string = sum.LN_Integer;
	num1Iter = num1_string.rbegin;
	num2Iter = num2_string.rbegin;
	sumIter = sum_string.rbegin;
	//this loops thorugh the integer protion of the number
	for (; num1Iter != num1_string.rend(); ++num1Iter, ++num2Iter, ++sumIter) {
		//Sums the the current column of the number and adding the carry
		int c = (*num1Iter - '0') + (*num2Iter - '0') + carry;
		//tests if the sum of the column is greater then 9
		if (c > 9) {
			//if true, then the remainder is put into the sum column and the rest is put into carry
			*sumIter = c % 10;
			carry = c / 10;
		}
		else {
			//if not greater then 9 then it is put into sum column
			*sumIter = char(c + '0');
			carry = 0;
		}
	}
	if (carry != 0) {
		//appends the carry to the front if it was not zero
		sum.LN_Integer = (char)(carry + '0') + sum.LN_Integer;
	}
	return sum;
}
//complete
LargeNum operator-(const LargeNum& num1, const LargeNum& num2) {
	//This substracts two large number objects.
	//This subtraction does sums the num1 and the complement (9's complement) of num2
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2.complement();
	LargeNum::matchLength(num1_copy, num2_copy);
	return num1_copy + num2_copy;
}

LargeNum operator*(const LargeNum& num1, const LargeNum& num2) {}

LargeNum operator/(const LargeNum& num1, const LargeNum& num2) {}

//boolean Operators
//complete
bool operator==(const LargeNum& num1, const LargeNum& num2) {
	//copies the two LargeNumber for comparison
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	//remove non-significant zeros from the copies
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	//gets a copy of the Integer and fraction part of the number to be used
	string num1_Int = num1_copy.LN_Integer;
	string num1_Frac = num1_copy.LN_Fraction;
	string num2_Int = num1_copy.LN_Integer;
	string num2_Frac = num1_copy.LN_Fraction;

	//checks if the two number are the same length
	if((num1_Int.size() == num2_Int.size() ) && (
		//if the two number are the same length then check of all digits are the same
		num1_Frac.size() == num2_Frac.size() )){
				string::iterator num1Itr = num1_Int.begin();
				string::iterator num2Itr = num2_Int.begin();
				//checks if the integer part is the same
				for(; num1Itr != num1_Int.end() || num2Itr != num2_Int.end();
					 ++num1Itr, ++num2Itr ){
					if( *num1Itr != *num2Itr){
						return false;
					}
				}
				num1Itr = num1_Frac.begin();
				num2Itr = num2_Frac.begin();
				//checks of the fraction part is the same
				for(; num1Itr != num1_Frac.end() || num2Itr != num2_Frac.end();
					 ++num1Itr, ++num2Itr){
					if(*num1Itr != *num2Itr){
						return false;
					}
				}
				return true;
	}else{
		//if the two number are not the same
		return false;
	}
}
//complete
bool operator<=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 < num2 || num1 == num2 ){
		return true;
	}else{
		return false;
	}
}
//complete
bool operator>=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 > num2 || num1 == num2){
		return true;
	}else{
		return false;
	}
}
//complete
bool operator!=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 == num2 ){
		return false;
	}else{
		return true;
	}
}
//complete
bool operator>(const LargeNum& num1, const LargeNum& num2) {
	//copies the two LargeNumber for comparison
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	//remove non-significant zeros from the copies
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	//gets a copy of the Integer and fraction part of the number to be used
	string num1_Int = num1_copy.LN_Integer;
	string num1_Frac = num1_copy.LN_Fraction;
	string num2_Int = num1_copy.LN_Integer;
	string num2_Frac = num1_copy.LN_Fraction;

	if (num1_copy.getIntegerSize() < num2_copy.getIntegerSize()) {
		//if the length of num1's integer protion is less then num2's integer portion
		//then we know num2 is greater
		return false;
	}
	if (num1_copy.getIntegerSize() == num2_copy.getIntegerSize() ) {
		string::iterator num1Iter = num1_copy.LN_Integer.begin();
		string::iterator num2Iter = num2_copy.LN_Integer.begin();
		//check if each intidudual character in the integer portion
		for (; num1Iter != num1_copy.LN_Integer.end(); ++num1Iter, ++num2Iter) {
			int c1 = *num1Iter - '0';
			int c2 = *num2Iter - '0';
			//if c1 is greater then c2 then we know the whole of num1 is greater then num2
			if (c1 > c2) {
				return true;
			}
			//if c2 is greater then c1 then we know the whole num2 is greater than num1
			else if (c1 < c2) {
				return false;
			}
		}

		num1Iter = num1_copy.LN_Fraction.begin();
		num2Iter = num2_copy.LN_Fraction.begin();
		//check if each intidudual character in the fraction portion
		for (; num1Iter != num1_copy.LN_Fraction.end(); ++num1Iter, ++num2Iter) {
			int c1 = *num1Iter - '0';
			int c2 = *num2Iter - '0';
			//if c1 is greater then c2 then we know the whole of num1 is greater then num2
			if (c1 > c2) {
				return true;
			}
			//if c2 is greater then c1 then we know the whole num2 is greater than num1
			else if (c1 < c2) {
				return false;
			}
		}
	}
	//else the two numbers are equal
	return false;
}
bool operator<(const LargeNum& num1, const LargeNum& num2){

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
LargeNum LargeNum::toLarge(float n) {

}

int LargeNum::toInt() {
	return stoi(LN_Integer,nullptr,1);
}
float LargeNum::toFloat() {
	string full_Num = LN_Integer + "." + LN_Fraction;
	return stof(full_Num);
}

bool LargeNum::validStr(string s) {
	int numberOfDecimalPoints = 0;
	string::iterator itr;
	for (itr = s.begin(); itr != s.end(); ++itr) {
		if (!isdigit(*itr)) {
			if (*itr == '-' && itr == s.begin()) {
				continue;
			}
			if (*itr == '.' && numberOfDecimalPoints < 1) {
				numberOfDecimalPoints++;
			}
			else {
				return false;
			}
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

void LargeNum::matchLength(LargeNum& num1, LargeNum& num2){
	int integerDiff, fractionDiff;
	if( num1.getIntegerSize() > num2.getIntegerSize() ){
		integerDiff = num1.getIntegerSize() - num2.getIntegerSize(); 
		num2.addZerostoFront(integerDiff);
	}
	else if( num1.getIntegerSize() < num2.getIntegerSize() ){
		integerDiff = num2.getIntegerSize() - num1.getIntegerSize(); 
		num1.addZerostoFront(integerDiff);
	}

	if( num1.getFractionSize() > num2.getFractionSize() ){
		fractionDiff = num1.getFractionSize() - num2.getFractionSize();
		num2.addZerostoEnd(fractionDiff);
	}
	else if( num1.getFractionSize() < num2.getFractionSize() ){
		fractionDiff = num2.getFractionSize() - num1.getFractionSize();
		num1.addZerostoEnd(fractionDiff);
	}
}
void LargeNum::addZerostoFront(int n){
	string zeros = string(n,'0');
	LN_Integer = zeros + LN_Integer;
}
void LargeNum::addZerostoEnd(int n){
	for(int i = 0; i < n; i++ ){
		LN_Fraction.push_back('0');
	}
}

string LargeNum::getInteger() {
	return LN_Integer;
}
string LargeNum::getFraction() {
	return LN_Fraction;
}

int LargeNum::getIntegerSize() const{
	return LN_Integer.size();
}
int LargeNum::getFractionSize() const{
	return LN_Fraction.size();	
}
int LargeNum::Size() const{
	return LN_Integer.size() + LN_Fraction.size();
}