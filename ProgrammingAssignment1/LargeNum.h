
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class LargeNum{
    private:
    string number;
    
    public:
        //constructors
        LargeNum();
        LargeNum(int Inum);
        LargeNum(string strNum);
        LargeNum(float fnum);

        LargeNum pow(const LargeNum& num2, int n);

        //print operator
        friend ostream& ostream(ostream& out, LargeNum& num);

        //Arithmatic operators
        LargeNum operator+(const LargeNum& num2);
        LargeNum operator-(const LargeNum& num2);
        LargeNum operator*(const LargeNum& num2);
        LargeNum operator/(const LargeNum& num2);
        
        //boolean Operators
        bool operator==(const LargeNum& num2);
        bool operator<=(const LargeNum& num2);
        bool operator>=(const LargeNum& num2);
        bool operator!=(const LargeNum& num2);

        //conversion methods
        LargeNum toLarge(int n);
        LargeNum toLarge(float n);
        int toInt();
        float toFloat();


};