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

LargeNum::LargeNum() {
	LN_Integer = "0";
	LN_Fraction = "0";
}
LargeNum::LargeNum(int INum) {
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
		for (decimalPointLoc; decimalPointLoc < strNum.size(); decimalPointLoc++) {
			if (strNum[decimalPointLoc] == '.') {
				LN_Integer = strNum.substr(0, decimalPointLoc);
				LN_Fraction = strNum.substr(decimalPointLoc + 1, strNum.size());
				break;
			}
		}
	}
}
LargeNum::LargeNum(float fnum) {
	ostringstream sfloat;
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


LargeNum LargeNum::pow(const LargeNum& num, int n) {
	//add code here
	LargeNum product = num;
	for(int i = 1; i < n; i++){
		product = num * product;
	}
	return product;
}

ostream& operator<<(ostream& out, LargeNum& num) {
	out << num.LN_Integer << "." << num.LN_Fraction;
	return out;
}
//Arithmatic operators
LargeNum operator+(const LargeNum& num1, const LargeNum& num2) {
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	LargeNum sum = LargeNum();
	LargeNum::matchLength(num1_copy, num2_copy);

	for

}
LargeNum operator-(const LargeNum& num1, const LargeNum& num2) {}
LargeNum operator*(const LargeNum& num1, const LargeNum& num2) {}
LargeNum operator/(const LargeNum& num1, const LargeNum& num2) {}

//boolean Operators
bool operator==(const LargeNum& num1, const LargeNum& num2) {
	//copies the two LargeNumber for comparison
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	//remove non-significant zeros from the copies
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	//gets a copy of the Integer and fraction part of the number to be used
	string num1_Int = num1_copy.getInteger();
	string num1_Frac = num1_copy.getFraction();
	string num2_Int = num1_copy.getInteger();
	string num2_Frac = num1_copy.getFraction();

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
bool operator<=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 < num2 || num1 == num2 ){
		return true;
	}else{
		return false;
	}
}
bool operator>=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 > num2 || num1 == num2){
		return true;
	}else{
		return false;
	}
}
bool operator!=(const LargeNum& num1, const LargeNum& num2) {
	if( num1 == num2 ){
		return false;
	}else{
		return true;
	}
}
bool operator>(const LargeNum& num1, const LargeNum& num2) {
	//copies the two LargeNumber for comparison
	LargeNum num1_copy = num1;
	LargeNum num2_copy = num2;
	//remove non-significant zeros from the copies
	num1_copy.removeZeros();
	num2_copy.removeZeros();
	//gets a copy of the Integer and fraction part of the number to be used
	string num1_Int = num1_copy.getInteger();
	string num1_Frac = num1_copy.getFraction();
	string num2_Int = num1_copy.getInteger();
	string num2_Frac = num1_copy.getFraction();



	return true;
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
int LargeNum::Size(){
	return LN_Integer.size() + LN_Fraction.size();
}