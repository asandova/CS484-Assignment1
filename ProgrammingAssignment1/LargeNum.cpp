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
#include <iomanip>
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
	//smallIncroment.Exponent = complement.Exponent;
	smallIncroment.decimalLocation = complement.decimalLocation;
	smallIncroment.Numbers.back() = '1';

	return complement + smallIncroment;
}

//complete-working
LargeNum::LargeNum() {
	Numbers = "00";
	//Exponent = 0;
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
 	//Exponent = Numbers.size()-1;
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
				//Exponent = strNum.substr(numBegin, i-1).size();
				Numbers = strNum.substr(numBegin, i) + strNum.substr(i + 1, strNum.size());
				return;
			}
		}
		Numbers = strNum;
		decimalLocation = 1;
		//Exponent = 0;
	}
}
//complete-working
LargeNum::LargeNum(float fnum) {
	if (fnum == 0) {
		decimalLocation = 1;
		//Exponent = 0;
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
	//sfloat.precision(2);
	sfloat << fnum;
	string fullFloat = string(sfloat.str());

	for(int i = 0; i < fullFloat.size(); i++){
		if (fullFloat[i] == '.') {
			decimalLocation = i;
			//Exponent = fullFloat.substr(1,i-1).size();
			Numbers = fullFloat.substr(0, i) + fullFloat.substr(i + 1, fullFloat.size());
			return;
		}
	}
	Numbers = fullFloat + '0';
	//Exponent = 0;
	decimalLocation = fullFloat.size();
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

	if (num.decimalLocation > 0) {
		out << num.Numbers.substr(0, num.decimalLocation);
	}else{
		out << "0";
	}

	out << ".";
	if (num.Size() - num.decimalLocation > 0) {
		out << num.Numbers.substr(num.decimalLocation, num.Size());
	}
	else {
		out << "0";
	}

	return out;
}
//Arithmatic operators

//complete-working
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

	//sum.decimalLocation -= exponentDiff;
	//sum.Exponent = exponentMax;
	return sum;
}
//complete-working
LargeNum operator-(const LargeNum& num1, const LargeNum& num2) {
	//This substracts two large number objects.
	//This subtraction does sums the num1 and the complement (9's complement) of num2
	
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	LargeNum::matchLength(num1_copy, num2_copy);
	num2_copy = num2_copy.complement();
	LargeNum differnce = num1_copy + num2_copy;
	differnce.Numbers.erase(differnce.Numbers.begin());
	return differnce;

}

LargeNum operator*(const LargeNum& num1, const LargeNum& num2) {
	if (num1 == LargeNum(0) || num2 == LargeNum(0)) {
		return LargeNum(0);
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
	int pos;
	for (int i = num1_copy.Size() - 1; i >=0; i--) {
		int carry = 0;
		int n1 = num1_copy.Numbers[i] - '0';
		num2Inx = 0;
		for (int j = num2_copy.Size() - 1; j >=0; j--) {
			int n2 = num2_copy.Numbers[j] - '0';
			pos = product.size()-1 - (num1Inx + num2Inx);
			int c = n1 * n2 + (product[pos]- '0') + carry;
			product[pos] = (c % 10) + '0';
			carry = c / 10;
			num2Inx++;
		}
		if (carry > 0) {
			int v = product[pos-1] - '0';
			product[pos-1] =  (v + carry) + '0' ;
		}
		num1Inx++;
	}
	LargeNum result = LargeNum();
	result.Numbers = product;
	result.decimalLocation = num1_copy.decimalLocation + num2_copy.decimalLocation;
	result.removeZeros();
	//result.Exponent = num1_copy.Exponent + num2_copy.Exponent;
	return result;
}

LargeNum operator/(const LargeNum& numerator, const LargeNum& divisor){
	if(divisor == LargeNum(0)){
		cout << "Cannot divide by zero" << endl;
		exit(-1);
	}
	if(divisor == LargeNum(1)){
		return numerator;
	}


	LargeNum Num = numerator;
	Num.Numbers.push_back('0');
	LargeNum Quotient = LargeNum();
	LargeNum NumSect = LargeNum(Num.Numbers.substr(0,1));
	for(int i = 1; i < Num.Size(); i++){
		int loops = 1;
		LargeNum temp = divisor * LargeNum(loops);
		while(temp < NumSect){
			temp = divisor * LargeNum(loops);
			loops++;
		}
		if(loops == 1){
			Quotient.Numbers.push_back('0');
		}
		if(loops > 1){
			Quotient.Numbers.push_back( loops + '0' );
			NumSect = NumSect - temp;
			if(NumSect == LargeNum(0)){
				//NumSect.Numbers[]
			}else{
				NumSect.Numbers.back() = Num.Numbers[i];
				NumSect.decimalLocation++;
			}
		}
	}
}

/*LargeNum operator/(const LargeNum& num, const LargeNum& div) {
	if (div == LargeNum(0)) {
		cout << "Cannot divide by zero" << endl;
		exit(-1);
	}
	if (div == LargeNum(1)) {
		return num;
	}
	LargeNum num_copy = num;
	num_copy.Numbers.push_back('0');
	LargeNum Quotient = LargeNum();
	LargeNum numSec = LargeNum(num.Numbers.substr(0, 1));
	for (int i = 1; i < num_copy.Size(); i++) {
		int loops = 1;
		int flag = 1;
		LargeNum LLoop;
		while (flag) {
			LLoop = LargeNum(loops);
			LargeNum fit = div * LLoop;
			fit.removeZeros();
			numSec.removeZeros();
			if (fit >= numSec) {
				if (fit > numSec) {
					loops -= 1;
					LLoop = LargeNum(loops);
				}
				flag = 0;
				break;
			}
			loops++;
		}
		if (loops == 0) {
			Quotient.Numbers.push_back('0');
			numSec.Numbers.push_back(num_copy.Numbers[i]);
			numSec.decimalLocation++;
			if (i + 1 == num_copy.Size() && numSec != LargeNum(0)) {
				num_copy.Numbers.push_back('0');
				numSec.decimalLocation--;
			}
		}
		else if (loops == 1) {
			Quotient.Numbers.push_back('1');
			LargeNum temp = div * LLoop;
			numSec = numSec - temp;
			numSec.Numbers[numSec.Size() - 1] = num_copy.Numbers[i];
			if (i + 1 == num_copy.Size() && numSec != LargeNum(0)) {
				num_copy.Numbers.push_back('0');
				numSec.decimalLocation++;
			}
		}
		else {
			Quotient.Numbers.push_back(loops + '0');
			LargeNum temp = div * LLoop;
			//cout << temp << endl;
			temp.removeZeros();
			numSec = numSec - temp;
			numSec.removeZeros();
			if (numSec == LargeNum(0)) {
				numSec = LargeNum(num_copy.Numbers[i] - '0');
			}
			else {
				//numSec.Numbers[numSec.Size() - 1] = num_copy.Numbers[i];
				numSec.Numbers.push_back(num_copy.Numbers[i]);
				numSec.decimalLocation+=3;
			}
		}
	}

	Quotient.decimalLocation = num.decimalLocation + div.decimalLocation+1;
	Quotient.removeZeros();
	return Quotient;
}*/

//boolean Operators
//complete
bool operator==(const LargeNum& num1, const LargeNum& num2) {
	//copies the two LargeNumber for comparison
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	//remove non-significant zeros from the copies
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	LargeNum::matchLength(num1_copy, num2_copy);
	//checks if the two number are the same length
	if (num1_copy.Size() == num2_copy.Size()) {
		if (num1_copy.decimalLocation == num2_copy.decimalLocation) {
			string::iterator num1Itr = num1_copy.Numbers.begin();
			string::iterator num2Itr = num2_copy.Numbers.begin();
			//checks if the integer part is the same
			for (; num1Itr != num1_copy.Numbers.end() || num2Itr != num2_copy.Numbers.end();
				++num1Itr, ++num2Itr) {
				if (*num1Itr != *num2Itr) {
					return false;
				}
			}
			return true;
		}
	}
	//if the two number are not the same
	return false;
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
	LargeNum::matchLength(num1_copy, num2_copy);
	string num1Sect = num1_copy.Numbers.substr(0, num1_copy.decimalLocation);
	string num2Sect = num2_copy.Numbers.substr(0, num2_copy.decimalLocation);
	
	//if (num1Sect.size() > num2Sect.size()) {
	//	return true;
	//}
	//else if (num1Sect.size() < num2Sect.size()) {
	//	return false;
	//}
	//else {
		string::iterator num1Iter = num1Sect.begin();
		string::iterator num2Iter = num2Sect.begin();
		//check if each individual character in the integer portion
		for (; num1Iter != num1Sect.end(); ++num1Iter, ++num2Iter) {
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
	//}

	num1Sect = num1_copy.Numbers.substr(num1_copy.decimalLocation, num1_copy.Size());
	num2Sect = num2_copy.Numbers.substr(num2_copy.decimalLocation, num2_copy.Size());
	num1Iter = num1Sect.begin();
	num2Iter = num2Sect.begin();
	//check if each individual character in the integer portion
	for (; num1Iter != num1Sect.end(); ++num1Iter, ++num2Iter) {
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
	return false;
}
bool operator<(const LargeNum& num1, const LargeNum& num2){
	if(num1 > num2 || num1 == num2){
		return false;
	}else{
	return true;
	}
}

int LargeNum::toInt() const{
	string ints;
	ints = Numbers.substr(0, decimalLocation);
	if(negative){
		ints = "-" + ints;
	}
	return stoi( ints ,nullptr,1);
}
float LargeNum::toFloat() const{
	string ints, decimals, sfloat;
	ints = Numbers.substr(0, decimalLocation);
	decimals = Numbers.substr(decimalLocation, Numbers.size());
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
	//string::reverse_iterator itr;
	if (Numbers.size() == decimalLocation) {
		return;
	}

	for(int i = Numbers.size()-1; i > 0 ; i--){
		if (Numbers[i] != '0' || i == decimalLocation) {
			Numbers = Numbers.erase(i+1, Numbers.size());
			return;
		}
	}
}

void LargeNum::removeLeadingZeros(){
	//Removes all non-signigicant zeros in the Fraction protion of the number
	//If the number has no significat digits then it ignores one zero after the decimal point
	for(int i = 0; i < Numbers.size(); i++){
		if(Numbers[i] != '0' || i+1 == decimalLocation){
			Numbers = Numbers.erase(0, i);
			decimalLocation -= i;
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
	decimalLocation += n;
}
void LargeNum::addZerostoEnd(int n){
	for(int i = 0; i < n; i++ ){
		Numbers.push_back('0');
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