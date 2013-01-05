#ifndef BIGINT_H_
#define BIGINT_H_
#include <iostream>
#include <string>
#include <stdlib.h>
#include "globalData.h"
using namespace std;
const int size = 64 + 1;

class BigInt{
public:
    BigInt();
	BigInt(const int&);
	BigInt(const BigInt&); 
	void readHexNum(string& str);     //从16进制字符串读入
	void readBinaryNum(string& buf); //从2进制字符串读入
	void displayByHex() const;   //输出到屏幕

	BigInt& operator= (const BigInt&);
	BigInt& operator= (int& a) { Clear(); data[0]=a; return *this;}
	BigInt& operator>> (const int&);
    BigInt& operator<< (const int&);
    
    inline int GetBitLength() const; //返回大数的二进制长度
    inline int GetLength() const;    //返回大数的长度
	bool TestSign() {return sign;}   //判断大数的正负 
	void Clear();    //大数清0
	void Random(int digNum);   //产生一个随机大数,其二进制长度为digNum
    void Randomsmall(int digNum);  //产生一个随机大数,其二进制长度为digNum的1/4
	void Output(ostream& out) const;
	bool IsOdd() const {return (data[0]&1);}    //判断大数奇偶性
	int hexCharToInt(char c);
	char intToHexChar(int c);

	friend BigInt operator+ (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const int&);
	friend BigInt operator* (const BigInt&, const BigInt&);
	friend BigInt operator% (const BigInt&, const BigInt&);
	friend BigInt operator/ (const BigInt&, const BigInt&);
	friend BigInt operator& (const BigInt&, const BigInt&);
	friend BigInt operator^ (const BigInt&, const BigInt&);
	friend BigInt operator| (const BigInt&, const BigInt&);
	friend BigInt operator* (const BigInt&, const unsigned int&);
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const int&);
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator== (const BigInt&, const int&);
	friend ostream& operator<< (ostream&, const BigInt&);
	friend BigInt PowerMode (const BigInt& n, const BigInt& p, const BigInt& m);
	friend void GenPrime(BigInt& n,int digNum);
private:
	unsigned int data[size];
	bool sign;
};

BigInt operator+ (const BigInt&, const BigInt&);
BigInt operator- (const BigInt&, const BigInt&);
BigInt operator- (const BigInt&, const int&);
BigInt operator* (const BigInt&, const BigInt&);
BigInt operator/ (const BigInt&, const BigInt&);
BigInt operator% (const BigInt&, const BigInt&);
BigInt operator& (const BigInt&, const BigInt&);
BigInt operator^ (const BigInt&, const BigInt&);
BigInt operator| (const BigInt&, const BigInt&);

BigInt operator* (const BigInt&, const unsigned int&);
bool operator< (const BigInt&, const BigInt&);
bool operator> (const BigInt&, const BigInt&);
bool operator<= (const BigInt&, const int&);
bool operator== (const BigInt&, const BigInt&);
bool operator== (const BigInt&, const int&);
ostream& operator<< (ostream&, const BigInt&);
BigInt PowerMode (const BigInt& n, const BigInt& p, const BigInt& m);
BigInt Gcd(const BigInt& m,const BigInt& n);
BigInt Euc(BigInt& E,BigInt& A);

//默认构造函数,成员数据清0
BigInt::BigInt()
{
	for(int i=0 ;i<size ;i++)
		data[i]=0;
	sign=true; 
}


//用int初始化大数
BigInt::BigInt(const int& input)
{
	for(int i=0 ;i<size ;i++)
		data[i]=0;
	data[0]=input;
	if(input>=0)
		sign=true;
	else
		sign=false;
}

//用大数给大数赋值
BigInt::BigInt(const BigInt& input)
{
	for(int i = 0; i < size; i++)
		data[i] = input.data[i];
	sign = input.sign;
}
void BigInt::readHexNum(string& str)
{
	Clear();
	int index = 0;
	while (str.length() > 8)
	{
		string seg = str.substr(str.length()-8, 8);
		str.erase(str.length()-8, 8);
		unsigned int cur = 0;
		for(int i = 0; i < 8; i++)
		{
			cur = cur * 16 + hexCharToInt(seg[i]);
		}
		data[index++] = cur;
	}
	unsigned int cur = 0;
	for (int i = 0; i < str.length(); i++)
		cur = cur*16+hexCharToInt(str[i]);
	data[index] = cur;
}
void BigInt::readBinaryNum(string& str)
{
	Clear();
	int index = 0;
	while (str.length() > 32)
	{
		string seg = str.substr(str.length()-32, 32);
		str.erase(str.length()-32, 32);
		unsigned int cur = 0;
		for (int i = 0; i < 32; i++)
		{
			cur = cur * 2 + (seg[i] - '0');
		}
		data[index++] = cur;
	}
	unsigned int cur = 0;
	for (int i = 0; i < str.length(); i++)
		cur = cur * 2 + (str[i] - '0');
	data[index] = cur;
}
//用大数给大数赋值
BigInt& BigInt::operator= (const BigInt& input)
{
	for (int i = 0; i < size; i++)
		data[i] = input.data[i];
	sign = input.sign;
    return *this;
}

//比较两个大数的大小,a<b,返回真,否则返回假
bool operator< (const BigInt& a, const BigInt& b)
{
	for (int i = size - 1; i > 0; i--)
	{
		if (a.data[i] < b.data[i])
			return true;
		if (a.data[i] > b.data[i])
			return false;
	}
	return a.data[0] < b.data[0];
}

//比较两个大数的大小,a>b,返回真,否则返回假
bool operator> (const BigInt& a, const BigInt& b)
{
	for (int i = size - 1; i >= 0; i--)
	{
		if (a.data[i] > b.data[i])
			return true;
		if (a.data[i] < b.data[i])
			return false;
	}
	return false;
}

//判断两个大数是否相等,相等返回真,否则返回假
bool operator== (const BigInt& a, const BigInt& b)
{
	for (int i = 0; i < size; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

//判断一个大数和一个int值是否相等,相等返回真,否则返回假
bool operator== (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++) {
		if (a.data[i] != 0)
			return false;
	}
	return a.data[0] == b;
}

//计算两个大数的和,采用竖式相加法
BigInt operator+ (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	unsigned long long sum;    
	//carry为进位标志,sub为当两数符号相异时,存放每两位数相减的临时差
	unsigned int carry = 0, sub;  
	//取a,b中长度较长的长度
	int length = (a.GetLength() >= b.GetLength()? a.GetLength() : b.GetLength());	

	//当两数符号相同时,进行加法运算
	if (a.sign == b.sign)
	{
		//每一位进行竖式相加
		for (int i = 0; i < length; i++)
		{
			sum = (unsigned long long)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum的高位为进位
			carry = (sum >> 32);
		}

		result.sign = a.sign;
		return result;
	}

	//两数符号不同时,进行减法运算
	else
	{
		BigInt tempa, tempb;

		//取出a,b中绝对值较大的作为被减数
		if (a < b)
		{
			tempa = b;
			tempb = a;
		}
		else
		{
			tempa = a;
			tempb = b;
		}

		//每一位进行竖式减
		for (int i = 0; i < length; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				//借位减
				result.data[i] = (unsigned long long)tempa.data[i] + (unsigned long long)(1<<32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
}

//计算两个大数的差,采用竖式相减法
BigInt operator- (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	unsigned long long sum;
	//carry为进位标志,sub为当两数符号相异时,存放每两位数相减的临时差
	unsigned int carry = 0, sub;

	//符号相同时,进行减法运算
	if (a.sign == b.sign)
	{
		BigInt tempa, tempb;

		//取出a,b中绝对值较大的作为被减数
		if (a < b)
		{
			tempa = b;
			tempb = a;
			tempa.sign = !tempa.sign;
		}
		else
		{
			tempa = a;
			tempb = b;
		}

		//每一位进行竖式减
		for (int i = 0; i < size; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				//借位减
				result.data[i] = (unsigned long long)tempa.data[i] + (unsigned long long)(1<<32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}

	//两数符号不同时,进行加法运算
	else
	{
		//每一位进行竖式相加
		for (int i = 0; i < size; i++)
		{
			sum = (unsigned long long)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum的高位为进位
			carry = (sum >> 32);
		}
		result.sign = a.sign;
		return result;
	}
}

//大数减一个int数
BigInt operator- (const BigInt& a, const int& b)
{
	BigInt temp(b);
	BigInt result = a - temp;
	return result;
}


//大数乘以一个INT数
BigInt operator* (const BigInt& a, const unsigned int& b)
{
	BigInt result;
	//存放B乘以A的每一位的临时积
	unsigned long long sum;
	//存放进位
	unsigned int carry = 0;

	for (int i = 0; i < size; i++)
	{
		sum = ((unsigned long long)a.data[i]) * b + carry;
		result.data[i] = (unsigned int)sum;
		//进位在SUM的高位中
		carry = (sum>>32);
	}
	result.sign = a.sign;
	return result;
}

//大数相乘,采用竖式乘
BigInt operator* (const BigInt& a, const BigInt& b)
{
	//last存放竖式上一行的积,temp存放当前行的积
	BigInt result, last, temp;    
	//sum存放当前行带进位的积
	unsigned long long sum;
	//存放进位
	unsigned int carry;

	//进行竖式乘
	for (int i = 0; i < b.GetLength(); i++)
	{
		carry = 0;
		//B的每一位与A相乘
		for (int j = 0; j < a.GetLength() + 1; j++)
		{
			sum = ((unsigned long long)a.data[j]) * b.data[i] + carry;
			if ((i + j) < size)
				temp.data[i + j] = (unsigned int)sum;
			carry = (sum>>32);
		}
		result = (temp + last);
		last = result;
		temp.Clear();
	}

	//判断积的符号
	if (a.sign == b.sign)
		result.sign = true;
	else
		result.sign = false;

	return result;
}

//大数除,采用试商除法,采用二分查找法优化
BigInt operator/ (const BigInt& a, const BigInt& b)
{
	//mul为当前试商,low,high为二分查找试商时所用的标志
	unsigned int mul, low, high;
	//sub为除数与当前试商的积,subsequent为除数与下一试商的积
	//dividend存放临时被除数
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,直接返回0
	if (a < b)
	{
		if (a.sign == b.sign)
			quotient.sign = true;
		else
			quotient.sign = false;
		return quotient;
	}

	//把被除数按除数的长度从高位截位
	for (int i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (int i = lengtha - lengthb; i >= 0; i--)
	{
		//如果被除数小于除数,再往后补位
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		//二分查找法查找试商
		while (low < high)
		{
			mul = (((unsigned long long)high) + low) / 2;			
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}

		//试商结果保存到商中去
		quotient.data[i] = mul;
		//临时被除数变为被除数与试商积的差
		dividend = dividend - sub;

		//临时被除数往后补位
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//判断商的符号
	if (a.sign == b.sign)
		quotient.sign = true;
	else
		quotient.sign = false;
	return quotient;
}

//大数求模运算,与除法运算类似
BigInt operator% (const BigInt& a, const BigInt& b)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,返回被除数为模
	if (a < b)
	{
		dividend = a;
		//余数的商永远与被除数相同
		dividend.sign = a.sign;
		return dividend;
	}

	//进行除法运算
	for (int i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (int i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		while (low <= high)
		{
			mul = (((unsigned long long)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{	
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}

		quotient.data[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//临时被除数即为所求模
	dividend.sign = a.sign;
	return dividend;
}

BigInt operator& (const BigInt& a, const BigInt& b) {
    int len = max(a.GetLength(), b.GetLength());
    BigInt res;
    for (int i = 0; i < len; i++)
        res.data[i] = (a.data[i] & b.data[i]);
    res.sign = (a.sign & b.sign);
    return res;
}

BigInt operator^ (const BigInt& a, const BigInt& b) {
    int len = max(a.GetLength(), b.GetLength());
    BigInt res;
    for (int i = 0; i < len; i++)
        res.data[i] = (a.data[i] ^ b.data[i]);
    res.sign = (a.sign ^ b.sign);
    return res;
}

BigInt operator| (const BigInt& a, const BigInt& b) {
    int len = max(a.GetLength(), b.GetLength());
    BigInt res;
    for (int i = 0; i < len; i++)
        res.data[i] = (a.data[i] ^ b.data[i]);
    res.sign = (a.sign ^ b.sign);
    return res;
}

//将大数以16进制显示到屏幕上
void BigInt::displayByHex() const
{
	unsigned int temp, result;
	unsigned int filter = 0xf0000000;
	string resStr;
	for (int i = GetLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & filter;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				resStr += (result + '0');
			else
			{
				switch (result)
				{
				case 10:
					resStr += 'A';
					break;
				case 11:
					resStr += 'B';
					break;
				case 12:
					resStr += 'C';
					break;
				case 13:
					resStr += 'D';
					break;
				case 14:
					resStr += 'E';
					break;
				case 15:
					resStr += 'F';
					break;
				}			
			}
		}
	}
	while (resStr[0] == '0')
	{
		resStr.erase(0,1);
	}
	cout << resStr;
	cout<<endl;
}

//将大数输出到输入输出流
void BigInt::Output(ostream& out) const
{
	unsigned int temp, result;
	unsigned int filter = 0xf0000000;
	string resStr;
	for(int i = GetLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & filter;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				resStr += (result + '0');
			else
			{
				switch (result)
				{
				case 10:
					resStr += 'A';
					break;
				case 11:
					resStr += 'B';
					break;
				case 12:
					resStr += 'C';
					break;
				case 13:
					resStr += 'D';
					break;
				case 14:
					resStr += 'E';
					break;
				case 15:
					resStr += 'F';
					break;
				}			
			}
		}
	}
	while (resStr[0] == '0')
	{
		resStr.erase(0,1);
	}
	out << resStr << endl;
}

//重载输出操作符
ostream& operator<< (ostream& out, const BigInt& x)
{
	x.Output(out);
	return out;
}

//大数置0
void BigInt::Clear()
{
	for (int i = 0; i < size; i++)
		data[i] = 0;
}

//返回大数长度
inline int BigInt::GetLength() const
{
	int length = size;
	for (int i = size - 1; i >= 0; i--)
	{
		//第一位不为0即为LENGTH
		if (data[i] == 0)
			length--;
		else
			break;
	}
	if (length == 0)
		length = 1;
	return length;
}

inline int BigInt::GetBitLength() const {
    int len = GetLength();
    int res = (len - 1) * 32;
    unsigned int tmp = data[len - 1];
    while (tmp > 0) {
        res ++;
        tmp = (tmp >> 1);
    }
    return res;
}

//重载移位操作符,向右移a(a < 32)位
BigInt& BigInt::operator>> (const int& a)
{
	unsigned int bit, filter;
    filter = (1 << a) - 1;
	data[0] = (data[0] >> a);
	for (int i = 1; i < GetLength(); i++)
	{
		//先将每一位的低a位移到BIT中
		bit = data[i] & filter;
		//再把BIT移到上一位的高位中
		bit = bit << (32 - a);
		data[i - 1] = data[i - 1] | bit;
		data[i] = (data[i] >> a);
	}
    return *this;
}
//重载移位操作符,向左移a位
BigInt& BigInt::operator<< (const int& a) {
    unsigned int bit, filter;
    filter = (1 << a) - 1;
    filter = (filter << (32 - a));
    int len = GetLength();
    for (int i = len - 1; i >= 0; i--) {
        bit = data[i] & filter;
        bit = bit >> (32 - a);
        data[i + 1] = data[i + 1] | bit;
        data[i] = (data[i] << a);
    }
    return *this;
}

//判断大数和一个INT的大小
bool operator<= (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	if (a.data[0] <= b)
		return true;
	else 
		return false;
}


//模幂运算,采用蒙格马利快速模幂算法
BigInt PowerMode (const BigInt& n, const BigInt& p, const BigInt& m)
{
	BigInt temp = p;
	BigInt r = n % m;
	BigInt k(1);
	while ( !(temp <= 1) )
	{		
		if (temp.IsOdd())
		{
			k = (k * r) % m;
		}
		r = (r * r) % m;
		temp >> 1;
	}
	return ( r * k ) % m;
}

char BigInt::intToHexChar(int n)
{
	char c;
	if (n >= 0 && n <= 9)
		c = '0' + n;
	else switch (n)
	{
	    case 10:
		    c = 'A';
            break;
	    case 11:
		    c = 'B';
            break;
	    case 12:
		    c = 'C';
            break;
	    case 13:
		    c = 'D';
            break;
	    case 14:
		    c = 'E';
            break;
	    case 15:
		    c = 'F';
            break;
	default:
		break;
	}
	return c;
}
int BigInt::hexCharToInt(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else switch (c)
	{
	    case 'a':
	    case 'A':
		    return 10;
	    case 'b':
	    case 'B':
		    return 11;
	    case 'c':
	    case 'C':
		    return 12;
	    case 'd':
	    case 'D':
		    return 13;
	    case 'e':
	    case 'E':
		    return 14;
	    case 'f':
	    case 'F':
		    return 15;
	    default:
		    break;
	}
	cout << "error" << endl;
	exit(0);
}

//产生一个随机大数,其二进制长度为digNum
void BigInt::Random(int digNum)
{
    for (int i = 0; i < digNum / 32; i++) {
	    //由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
	    //3次RAND()操作
	    data[i] = ((rand() % 0x7FFFF) << 17 ) + ( (rand() % 0x7FFFF) << 2 )+ rand() % 4;
    }
    data[digNum/32-1] = data[digNum/32-1] | 0x80000000;
}


//产生一个较小的随机大数,其二进制长度为digNum的1/4;
void BigInt::Randomsmall(int digNum)
{
    for (int i = 0; i < digNum / 128; i++) {
	    //由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
	    //3次RAND()操作
	    data[i] = (rand() << 17 ) + ( rand() << 2 )+ rand() % 4;
    }
    data[digNum/128-1] = data[digNum/32-1] | 0x80000000;
}

//求两个大数的最大公约数,采用辗转相除法
BigInt Gcd(const BigInt& m, const BigInt& n)
{
	//cout << "m: ";m.displayByHex(); cout << "n: ";n.displayByHex();cout << endl;
	//outfile << "m: ";outfile << m; outfile << "n: ";outfile << n;outfile << endl;
	if (n == 0)
		return m;
	else
		return Gcd(n, m%n);
}

//用扩展欧几里德算法求乘法模逆
BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	//cout << "a: ";a.displayByHex(); cout << "b: ";b.displayByHex();cout << endl;
	//outfile << "a: ";outfile << a; outfile << "b: ";outfile << b;outfile << endl;
	BigInt t, d;   
	//如果一个操作数为零则无法进行除法运算
	if (b == 0)   
	{
		x = 1, y = 0;
		return a;
	}
	BigInt tb = a % b;
	d = ExtendedGcd(b, tb, x, y);   
	t = x;   
	x = y;   
	y = t - ((a / b) * y);   
	return d;   
}

BigInt Euc(BigInt& E,BigInt& A)
{
	BigInt M, X, Y, I, J;
	int x, y;
	M = A;
	X = 0;
	Y = 1;
	x = y = 1;
	while ((E.GetLength() != 1) || !(E == 0))
	{
		I = M / E;
		J = M % E;
		M = E;
		E = J;
		J = Y;
		Y = Y * I;
		if (x == y)
		{
			if (X > Y)
                Y = X - Y;
			else
            {
                Y = Y - X;
                y = 0;
            }
		}
		else
        {
            Y = X + Y;
            x = 1 - x;
            y = 1 - y;
        }
		X = J;
	}
	if (x == 0)
        X = A - X;
	return X;
}

#endif
