#ifndef BIGINT_H_
#define BIGINT_H_
#include <iostream>
#include <string>
#include <stdlib.h>
#include "globalData.h"

using namespace std;

class BigInt {
public:
    BigInt();
    BigInt(const int&);
    BigInt(const BigInt&); 
    void readHexNum(string& str);     //从16进制字符串读入
    void readBinaryNum(string& buf); //从2进制字符串读入
    void stringToBigInt(string& buf);
    string BigIntToString();
    string TransformToHexString();
    void displayByHex() const;   //输出到屏幕

    BigInt& operator= (const BigInt&);
    BigInt& operator= (int& a) { Clear(); data[0]=a; return *this;}
    BigInt& operator>> (const int&);
    BigInt& operator<< (const int&);
    
    int GetBitLength() const; //返回大数的二进制长度
    int GetLength() const;    //返回大数的长度
    bool TestSign() {return sign;}   //判断大数的正负 
    void Clear();    //大数清0
    void Random(int digNum);   //产生一个随机大数,其二进制长度为digNum
    void Randomsmall(int digNum);  //产生一个随机大数,其二进制长度为digNum的1/4
    void Output(ostream& out) const;
    bool IsOdd() const {return (data[0]&1);}    //判断大数奇偶性
    int hexCharToInt(char c);
    char intToHexChar(int c);

    BigInt operator+ (const BigInt&) const;
    BigInt operator- (const BigInt&) const;
    BigInt operator- (const int&) const;
    BigInt operator* (const BigInt&) const;
    BigInt operator% (const BigInt&) const;
    int operator% (const int&) const;
    BigInt operator/ (const BigInt&) const;
    BigInt operator& (const BigInt&) const;
    BigInt operator^ (const BigInt&) const;
    BigInt operator| (const BigInt&) const;
    BigInt operator* (const unsigned int&) const;
    bool operator< (const BigInt&) const;
    bool operator> (const BigInt&) const;
    bool operator<= (const int&) const;
    bool operator== (const BigInt&) const;
    bool operator== (const int&) const;
    friend ostream& operator<< (ostream&, const BigInt&);
    
    static BigInt PowerMode (const BigInt& n, const BigInt& p, const BigInt& m);
    static BigInt Gcd(const BigInt& m,const BigInt& n);
	static BigInt Euc(BigInt& E,BigInt& A);
	static BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y);
	
    void GenPrime(BigInt& n,int digNum);
private:
	static const size_t _capacity = 128 + 1;
    unsigned int data[_capacity];
    bool sign;
};

#endif
