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

LargeNum LargeNum::complement() const{
	//This function preformes 10's complement on the given largeNumber
	LargeNum complement = *this;
	
	//calculates 9's complement
	string::reverse_iterator compIter = complement.Numbers.rbegin();
	for (; compIter != complement.Numbers.rend(); ++compIter) {
		*compIter = ('9' - *compIter) + '0';
	}
	//cout << complement << endl;
	LargeNum smallIncroment = LargeNum("0.0");
	matchLength(complement, smallIncroment);
	smallIncroment.Exponent = complement.Exponent;
	smallIncroment.decimalLocation = complement.decimalLocation;
	smallIncroment.Numbers.back() = '1';

	return complement + smallIncroment;
}

//complete-working
LargeNum::LargeNum() {
	Numbers = "00";
	Exponent = 0;
	//this reperesents the location of the decimal point
	//The number mean that the decimal is before the number at index n
	decimalLocation = 1; 
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
	decimalLocation = Numbers.size();
	Numbers = Numbers + '0';
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
				decimalLocation = i;
				Exponent = strNum.substr(numBegin, i-1).size();
				Numbers = strNum.substr(numBegin, i) + strNum.substr(i + 1, strNum.size());
				return;
			}
		}
		decimalLocation = 1;
		Exponent = 0;
	}
}
//complete-working
LargeNum::LargeNum(float fnum) {
	if (fnum == 0) {
		decimalLocation = 1;
		Exponent = 0;
		Numbers = "00";
		negative = false;
		return;
	}
	ostringstream sfloat;
	if (fnum < 0) {
		negative = true;
		fnum *= -1;
	}else{
		negative = false;
	}
	sfloat.precision(2);
	sfloat << fixed << fnum;
	string fullFloat = string(sfloat.str());

	for(int i = 0; i < fullFloat.size(); i++){
		if (fullFloat[i] == '.') {
			decimalLocation = i;
			Exponent = fullFloat.substr(1,i-1).size();
			Numbers = fullFloat.substr(0, i) + fullFloat.substr(i + 1, fullFloat.size());
			break;
		}
	}
}

LargeNum LargeNum::pow( int n) const {
	//add code here
	if (n == 1) {
		return *this;
	}
	if (n == 0) {
		return LargeNum(1);
	}
	if (n < 0) {
		cout << "Does not support negative powers" << endl;
		exit(2);
	}
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

	if(num.Numbers.size() > 51){
		out << num.Numbers.substr( 1, 51);
	}else{
	 out << num.Numbers.substr(1, num.Numbers.size()) + "0";
	}
	if(num.Exponent+num.decimalLocation-1 > 0)
		out << "e^" << num.Exponent+num.decimalLocation-1;

	return out;
}
//Arithmatic operators

//complete-working
LargeNum operator+(const LargeNum& num1, const LargeNum& num2) {
	//create copies
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	int exponentDiff = 0;
	int exponentMax = num1.Exponent;
	if( num1.Exponent > num2.Exponent ){
		exponentMax = num1.Exponent;
		exponentDiff = num1.Exponent - num2.Exponent;
		num1_copy.Exponent = num2.Exponent;
		//num1_copy.decimalLocation += exponentDiff;
	}else if(num1.Exponent < num2.Exponent){
		exponentMax = num2.Exponent;
		exponentDiff = num2.Exponent - num1.Exponent;
		num2_copy.Exponent = num1.Exponent;
		//num2_copy.decimalLocation += exponentDiff;
	}
	LargeNum::matchLength(num1_copy, num2_copy);
	//initialize the result
	LargeNum sum = LargeNum();
	LargeNum::matchLength(num1_copy, sum);
	int carry = 0;
	string::reverse_iterator num1Iter = num1_copy.Numbers.rbegin();
	string::reverse_iterator num2Iter = num2_copy.Numbers.rbegin();
	string::reverse_iterator sumIter = sum.Numbers.rbegin();
	//This loop through the fraction protion of the number
	for (; num1Iter != num1_copy.Numbers.rend(); ++num1Iter, ++num2Iter, ++sumIter) {
		//Sums the the current column of the number and adding the carry
		int c = (*num1Iter - '0') + (*num2Iter - '0') + carry;
		//tests if the sum of the column is greater then 9
		if (c > 9) {
			//if true, then the remainder is put into the sum column and the rest is put into carry
			*sumIter = (c % 10) + '0';
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
	sum.decimalLocation -= exponentDiff;
	sum.Exponent = exponentMax;
	return sum;
}
//complete-working
LargeNum operator-(const LargeNum& num1, const LargeNum& num2) {
	//This substracts two large number objects.
	//This subtraction does sums the num1 and the complement (9's complement) of num2
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2.complement();
	//LargeNum::matchLength(num1_copy, num2_copy);
	LargeNum differnce = num1_copy + num2_copy;
	differnce.Numbers.erase(differnce.Numbers.begin());
	return differnce;

}

/*
LargeNum operator*(const LargeNum& num1, const LargeNum& num2) {
	if (num1 == LargeNum() || num2 == LargeNum()) {
		return LargeNum();
	}
	if (num1 == LargeNum(1)) {
		return num2;
	}
	if (num2 == LargeNum(1)) {
		return num1;
	}

	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	LargeNum product = LargeNum();
	LargeNum step = LargeNum();
	LargeNum::matchLength(num1_copy, num2_copy);
	product.addZerostoFront(num1_copy.Size() * 2);
	step.addZerostoFront(num1_copy.Size() * 2);

	string::reverse_iterator num1Itr;
	string::reverse_iterator num2Itr;
	string::reverse_iterator stepLoopItr = step.Numbers.rbegin();
	string::reverse_iterator stepItr;
	int carry = 0;

	for (num2Itr = num2_copy.Numbers.rbegin(); 
			num2Itr != num2_copy.Numbers.rend(); ++num2Itr, ++stepLoopItr) {
		stepItr = stepLoopItr;
		for (num1Itr = num1_copy.Numbers.rbegin(); 
				num1Itr != num1_copy.Numbers.rend(); ++num1Itr, ++stepItr) {
			int c = (*num2Itr - '0') * (*num1Itr - '0') + carry;
			if (c > 9) {
				*stepItr = (c % 10) + '0'; 
				carry = c / 10;
			}
			else {
				*stepItr = c + '0';
				carry = 0;
			}
		}
		if (carry > 0) {
			//++stepItr;
			if (stepItr != step.Numbers.rend()) {
				*stepItr = carry + '0';
				carry = 0;
			}
			else {
				step.Numbers = (char)(carry + '0') + step.Numbers;
				stepLoopItr = step.Numbers.rbegin();
			}
		}
		product = product + step;
		step.clear();
	}
	if (carry > 0) {
		product.Numbers = (char)(carry + '0') + product.Numbers;
		product.Exponent++;
		carry = 0;
	}
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	product.Exponent = num1.Exponent + num2.Exponent;
	product.decimalLocation = num1_copy.decimalLocation + num2.decimalLocation;
	product.removeZeros();
	return product;
}*/

LargeNum operator*(const LargeNum& num1, const LargeNum& num2) {
	if (num1 == LargeNum() || num2 == LargeNum()) {
		return LargeNum();
	}
	if (num1 == LargeNum(1)) {
		return num2;
	}
	else if (num2 == LargeNum(1)) {
		return num1;
	}
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	string product = string( num1_copy.Size() + num2_copy.Size(), '0');

	int num1Inx = 0;
	int num2Inx = 0;

	for (int i = 0; i < num1_copy.Size() - 1; i++) {
		int carry = 0;
		int n1 = num1_copy.Numbers[i] - '0';
		num2Inx = 0;
		for (int j = 0; i < num2_copy.Size() - 1; j++) {
			int n2 = num2_copy.Numbers[j] - '0';
			int c = n1 * n2 + (product[num1Inx + num2Inx]- '0') + carry;
			product[num1Inx + num2Inx] = (c % 10) + '0';
			carry = c / 10;
			num2Inx++;
		}
		if (carry > 0) {
			int v = product[num1Inx + num2Inx] - '0';
			product[num1Inx + num2Inx] =  (v + carry) + '0' ;
		}
		num1Inx++;
	}
	LargeNum result = LargeNum();

	result.Numbers = product;
	result.Exponent = num1_copy.Exponent + num2_copy.Exponent;
	result.decimalLocation = num1_copy.decimalLocation + num2_copy.decimalLocation;
	return result;
}

LargeNum operator/(const LargeNum& num, const LargeNum& div) {
	if (div == LargeNum(0)) {
		cout << "Cannot divide by zero" << endl;
		exit(-1);
	}
	if (div == LargeNum(1)) {
		return num;
	}
	LargeNum num_copy = num;
	LargeNum Quotient = LargeNum();
	
	for (int i = 1; i < num.Size(); i++) {
		int loops = 1;
		string numSec = num.Numbers.substr(0,i);
		LargeNum sec = LargeNum(numSec);
		int flag = 1;
		LargeNum LLoop;
		while ( flag ) {
			LLoop = LargeNum(loops);
			LargeNum fit = sec * LLoop;
			if ( fit >= num_copy) {
				flag = 0;
				break;
			}
			loops++;
		}
		Quotient.Numbers.push_back(loops + '0');
		num_copy = num_copy - (sec * LLoop);
	}

	Quotient.Exponent = num.Exponent - div.Exponent;
	Quotient.removeZeros();
	return Quotient;
}

//boolean Operators
//complete
bool operator==(const LargeNum& num1, const LargeNum& num2) {
	//copies the two LargeNumber for comparison
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	//remove non-significant zeros from the copies
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	//checks if the two number are the same length
	if(num1_copy.Exponent == num2_copy.Exponent ){
		if (num1_copy.Size() != num2_copy.Size()) {
			return false;
		}
		string::iterator num1Itr = num1_copy.Numbers.begin();
		string::iterator num2Itr = num2_copy.Numbers.begin();
		//checks if the integer part is the same
		for(; num1Itr != num1_copy.Numbers.end() || num2Itr != num2_copy.Numbers.end();
				++num1Itr, ++num2Itr ){
			if( *num1Itr != *num2Itr){
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

	if (num1_copy == num2_copy) {
		return false;
	}
	else if (num1_copy.Exponent < num2_copy.Exponent) {
		//if the length of num1's integer protion is less then num2's integer portion
		//then we know num2 is greater
		return false;
	}
	else if (num1_copy.Exponent > num2_copy.Exponent) {
		return true;
	}
	if (num1_copy.Exponent == num2_copy.Exponent ) {
		string::iterator num1Iter = num1_copy.Numbers.begin();
		string::iterator num2Iter = num2_copy.Numbers.begin();
		//check if each intidudual character in the integer portion
		for (; num1Iter != num1_copy.Numbers.end(); ++num1Iter, ++num2Iter) {
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
	if(num1 > num2 || num1 == num2){
		return false;
	}else{
	return true;
	}
}

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
	string::reverse_iterator itr;
	for(itr = Numbers.rbegin(); itr != Numbers.rend(); ++itr){
		if(*itr != '0' ||  Numbers.size() < Exponent+decimalLocation){
			return;
		}else{
			Numbers.pop_back();
		}
	}
}

void LargeNum::removeLeadingZeros(){
	//Removes all non-signigicant zeros in the Fraction protion of the number
	//If the number has no significat digits then it ignores one zero after the decimal point
	for(int i = 0; i < Numbers.size(); i++){
		if(Numbers[i] != '0'){
			Numbers = Numbers.erase(0, i);
			return;
		}
	}
}

void LargeNum::matchLength(LargeNum& num1, LargeNum& num2){

	//Finds where the current decimal point is then add the exponent to find
	//the total numbers of integer and decimals in the number

	int num1Ints = num1.Numbers.substr(0,num1.decimalLocation).size();
	int num1Decimals = num1.Numbers.substr(num1.decimalLocation-1,num1.Size()).size();
	int num2Ints = num2.Numbers.substr(0,num2.decimalLocation ).size();;
	int num2Decimals = num2.Numbers.substr(num2.decimalLocation-1, num2.Size()).size();;


	//once found add zeros to the frond and back to make the two number the same length
	if(num1Ints > num2Ints){
		num2.addZerostoFront(num1Ints - num2Ints);
	}else if (num1Ints < num2Ints){
		num1.addZerostoFront(num2Ints - num1Ints);
	}

	if(num1Decimals > num2Decimals){
		num2.addZerostoEnd(num1Decimals - num2Decimals);
	}else if(num1Decimals > num2Decimals){
		num1.addZerostoEnd(num2Decimals - num1Decimals);
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

void LargeNum::clear() {
	//clears the number to 0
	string::iterator sItr = Numbers.begin();
	for (; sItr != Numbers.end(); ++sItr) {
		*sItr = '0';
	}
}