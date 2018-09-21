/*
	File: LargeNum.cpp
	Author: August B. Sandoval
	Class: CS484
	Prurpose: Contains the class implemtation of the class LargeNum
*/
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include "LargeNum.h"

using namespace std;

LargeNum& LargeNum::complement() const{
	//This function preformes 9's complement on the given largeNumber
	LargeNum complement = LargeNum();
	LargeNum copy = *this;
	matchLength(copy, complement);

	string::reverse_iterator numIter = copy.Numbers.rbegin(), 
		compIter = complement.Numbers.rbegin();
	for (; numIter != copy.Numbers.rend(); ++compIter, ++numIter) {
		*compIter = '9' - *numIter + '0';
	}
	return complement;
}

//complete-working
LargeNum::LargeNum() {
	Numbers = "0.0";
	Exponent = 0;
	negative = false;
}
//complete-working
LargeNum::LargeNum(int INum) {
	if (INum < 0) {
		negative = true;
		INum *= -1;
	}
	else {
		negative = false;
	}
	ostringstream sInt;
	sInt << INum;
	Numbers = string(sInt.str());
	//sets the exponent to the length of the number string - 1
	//essentialy representing the number in scientific notation
	//i.e. 123456 -> 1.23456e5
 	Exponent = Numbers.size()-1;
}
//complete-working
LargeNum::LargeNum(string strNum) {
	if (!validStr(strNum)) {
		cout << "ERROR: Invalid Number" << endl;
		cout << "Exiting" << endl;
		exit(-1);
	}
	else {
		negative = false;
		int numBegin = 0;
		for (int i = 0; i < strNum.size(); i++) {
			if (strNum[i] == '-' && i == 0) {
				negative = true;
				numBegin++;
			}
			if (strNum[i] == '.') {
				Exponent = strNum.substr(numBegin, i-1).size();
				Numbers = strNum.substr(numBegin, i) + strNum.substr(i + 1, strNum.size());
				break;
			}
		}
	}
}
//complete-working
LargeNum::LargeNum(float fnum) {
	ostringstream sfloat;
	if (fnum < 0) {
		negative = true;
		fnum *= -1;
	}else{
		negative = false;
	}
	sfloat << fnum;
	string fullFloat = string(sfloat.str());

	for(int i = 0; i < fullFloat.size(); i++){
		if (fullFloat[i] == '.') {
			Exponent = fullFloat.substr(1,i-1).size();
			Numbers = fullFloat.substr(0, i) + fullFloat.substr(i + 1, fullFloat.size());
			break;
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

//Complete-working
ostream& operator<<(ostream& out, LargeNum& num) {
	//Prints the first 50 digits after the decimal
	if (num.negative) {
		out << "-";
	}
	out << num.Numbers[0] << ".";

	if(num.Numbers.size() < 51){
		out << num.Numbers.substr( 1, 51);
	}else{
	 out << num.Numbers.substr(1, num.Numbers.size());
	}
	out << "e^" << num.Exponent;

	return out;
}
//Arithmatic operators

//complete
LargeNum operator+(const LargeNum& num1, const LargeNum& num2) {
	//create copies
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	LargeNum::matchLength(num1_copy, num2_copy);
	//initialize the result
	LargeNum sum = LargeNum();
	LargeNum::matchLength(num1_copy, sum);
	int carry = 0;
	string::reverse_iterator num1Iter = num1_copy.Numbers.rbegin();
	string::reverse_iterator num2Iter = num2_copy.Numbers.rbegin();
	string::reverse_iterator sumIter = sum.Numbers.rbegin();
	//This loop through the fraction protion of the number
	for (; num1Iter != num1.Numbers.rend(); ++num1Iter, ++num2Iter, ++sumIter) {
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
	if(carry != 0){
		sum.Numbers = char(carry +'0') + sum.Numbers; 
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

LargeNum operator*(const LargeNum& num1, const LargeNum& num2) {
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	LargeNum product = LargeNum();
	LargeNum::matchLength(num1_copy, num2_copy);
	product.addZerostoFront(num1_copy.Size() * 2);

	int n1 = num1.Size();
	int n2 = num2.Size();
	if(n1 == 0 || n2 == 0){
		return LargeNum(0);
	}

	int num1Index = 0;
	int num2Index = 0;

	for(int i = n1-1; i >= 0; i--){
		int carry = 0;
		int n1 = num1_copy.Numbers[i] - '0';
		num2Index = 0;
		for(int j = n2-1; j >= 0; j--){
			int n2 = num2_copy.Numbers[j] - '0';
			int sum = n1 * n2 + product.Numbers[num1Index + num2Index] + carry;
			carry = sum/10;
			product.Numbers[num1Index + num2Index] = sum % 10 + '0';
			num2Index++;
		}
		if(carry > 0){
			product.Numbers[num1Index + num2Index] += carry;
		}
		num1Index++;
	}

	string::reverse_iterator num1Itr, num2Itr;
}

LargeNum operator/(const LargeNum& num, const LargeNum& div) {
	return LargeNum();
}
/*
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
*/
/*
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

}*/

int LargeNum::toInt() const{
	string ints;
	ints = Numbers.substr(0, Numbers.size()-Exponent);
	if(negative){
		ints = "-" + ints;
	}
	return stoi( ints ,nullptr,1);
}
float LargeNum::toFloat() const{
	string ints, decimals, sfloat;
	ints = Numbers.substr(0, Numbers.size()-Exponent);
	decimals = Numbers.substr(Exponent, Numbers.size());
	sfloat = ints + "." + decimals;
	if(negative){
		sfloat = "-" + sfloat;
	}
	return stof(sfloat);
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
}

void LargeNum::removeLeadingZeros(){
	//Removes all non-signigicant zeros in the Fraction protion of the number
	//If the number has no significat digits then it ignores one zero after the decimal point
	string::iterator itr;
	for(itr = Numbers.begin(); itr != Numbers.end(); ++itr){
		if(*itr != '0' ||  Numbers.size() < Exponent+1){
			return;
		}else{
			Numbers.erase(itr);
		}
	}
}

void LargeNum::matchLength(LargeNum& num1, LargeNum& num2){
	if(num1.Exponent > num2.Exponent){
		num1.Exponent = num2.Exponent;
	}else if( num1.Exponent < num2.Exponent ){
		num2.Exponent = num2.Exponent;
	}else{
		cout << "numbers are already the same exponent" << endl;
	}
}
void LargeNum::addZerostoFront(int n){
	string zeros = string(n,'0');
	Numbers = zeros + Numbers;
}
void LargeNum::addZerostoEnd(int n){
	for(int i = 0; i < n; i++ ){
		Numbers.push_back('0');
		Exponent++;
	}
}
int LargeNum::Size() const{
	return Numbers.size();
}