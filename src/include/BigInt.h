#ifndef BIGINT_H_
#define BIGINT_H_
#include <iostream>
#include <string>
#include <stdlib.h>
#include "globalData.h"

using namespace std;

class BigInt {
public:
    /**
     * 无参构造函数，默认为0
     */
    BigInt();

    /**
     * 用int类型参数初始化大数
     *
     * @param [in]  input 输入的int类型数据
     */
    BigInt(const int&);

    /**
     * 拷贝构造函数
     *
     * @param [in] input 另一个大数
     */
    BigInt(const BigInt&); 

    /**
     * 构造函数，从16进制字符串构造
     *
     * @param [in] str
     * @param [in] base 进制(2, 10, 16)
     */
    BigInt(string, int);
    /**
     * 从16进制字符串读入数据
     *
     * @param str 16进制字符串
     */
    void GenFromHexString(string str);

    /**
     * 从2进制字符串读入数据
     *
     * @param buf  2进制字符串
     */
    void GenFromBinString(string buf);

    /**
     * 从字节串读入数据
     *
     * @param buf  字节串
     */
    void GenFromByteString(const string& buf);

    /**
     * 把大数转换成10进制字符串
     *
     * @return 大数10进制字符串
     */
    string ToString() const;

    /**
     * 把大数转换成16进制字符串
     *
     * @return 大数16进制字符串
     */
    string ToHexString() const;

    /**
     * 赋值运算符（深拷贝）
     * 
     * @param input 另一个大数
     */
    BigInt& operator= (const BigInt&);

    /**
     * 赋值运算符，用int类型整数赋值
     *
     * @param a 整数
     */
    BigInt& operator= (int& a) { Clear(); data[0]=a; return *this;}

    /**
     * 位右移运算符
     *
     * @param a 右移位数
     */
    BigInt& operator>> (const int&);

    /**
     * 位左移运算符
     *
     * @param a 左移位数
     */
    BigInt& operator<< (const int&);

    /**
     * 返回大数的二进制长度
     *
     * @return 二进制长度
     */
    int GetBitLength() const;

    /**
     * 返回大数的长度（已占用的内部储存数组长度）
     *
     * @return 大数的长度
     */
    int GetLength() const;

    /**
     * 判断大数的正负
     *
     * @return true：正，false，负
     */
    bool TestSign() const {return sign;}

    /**
     * 清零
     */
    void Clear();

    /**
     * 产生随机大数
     *
     * @param digNum 二进制长度
     */
    void Random(int digNum);

    /**
     * 产生小的随机大数（长度为digNum的1/4）
     *
     * @param digNum 二进制长度
     */
    void Randomsmall(int digNum);
    
    /**
     * 判断大数的奇偶性
     *
     * return true：奇数，false：偶数
     */
    bool IsOdd() const {return (data[0]&1);}

    /* 四则运算符 */
    BigInt operator+ (const BigInt&) const;         /* 加法 */
    BigInt operator- (const BigInt&) const;         /* 减法 */
    BigInt operator- (const int&) const;
    BigInt operator* (const BigInt&) const;         /* 乘法 */
    BigInt operator* (const unsigned int&) const;
    BigInt operator% (const BigInt&) const;         /* 取余 */
    int operator% (const int&) const;

    /* 位运算符 */
    BigInt operator/ (const BigInt&) const;         /* 除法 */
    BigInt operator& (const BigInt&) const;         /* 位与 */
    BigInt operator^ (const BigInt&) const;         /* 异或 */
    BigInt operator| (const BigInt&) const;         /* 位或 */
    
    /* 逻辑运算符 */
    bool operator< (const BigInt&) const;           /* 小于 */
    bool operator> (const BigInt&) const;           /* 大于 */
    bool operator<= (const int&) const;             /* 小于等于 */
    bool operator== (const BigInt&) const;          /* 等于 */
    bool operator== (const int&) const;

    /**
     * 把大数输出到流
     *
     */
    friend ostream& operator<< (ostream&, const BigInt&);
    
    /**
     * 模冪运算 n ^ p mod m
     *
     * @param [in] n
     * @param [in] p
     * @param [in] m
     * @return n ^ p mod m 结果
     */
    static BigInt PowerMode (const BigInt& n, const BigInt& p, const BigInt& m);

    /**
     * 求两数的最大公约数
     *
     * @param [in] m
     * @param [in] n
     * @return m与n的最大公约数
     */
    static BigInt Gcd(const BigInt& m,const BigInt& n);

    /**
     * 欧几里得算法
     *
     * @param [in] E
     * @param [in] A
     * @return gcd(E, A)
     */
    static BigInt Euc(BigInt& E,BigInt& A);

    /**
     * 扩展欧几里得算法，求乘法模逆
     *
     * @param [in] a
     * @param [in] b
     * @param [out] x a mod b的乘法逆元
     * @param [out] y b mod a的乘法逆元
     * @return gcd(a, b)
     */
    static BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y);
private:
    static const size_t _capacity = 128 + 1;
    unsigned int data[_capacity];
    bool sign;
    /**
     * 将大数输出到输出流
     *
     * @param out 输出流
     */
    void _output(ostream& out) const;

    int _hexCharToInt(char c);
    char _intToHexChar(int c);
};

enum _STRING_TYPE {
    BIN_STRING = 2,
    HEX_STRING = 16,
    BYTE_STRING = 10
};

#endif
