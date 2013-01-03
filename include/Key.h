#ifndef KEY_H_
#define KEY_H_
#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include "BigInt.h"
using namespace std;
class Key
{
private:
    int digNum;
	BigInt p,q,n,e,t,d;
public:
	Key(int digNum)
	{
		this->digNum=digNum;
		srand((unsigned)time(NULL));
		cout<<"********随机产生p,q********"<<endl;
		cout<<endl;
		p=GeneratePrime();
		cout<<endl;
		cout<<"产生p:"<<endl;
		p.displayByHex();
		cout<<endl;
		q=GeneratePrime();
		cout<<endl;
		cout<<"产生q:"<<endl;
		q.displayByHex();
		cout<<endl;

		cout<<"********密钥生成********"<<endl;
		cout<<endl;
		cout<<"公钥e:"<<endl;
		t=(p-1)*(q-1);
		BigInt x,y,temp;
		while(1)
		{
			e.Random(digNum);
			//产生与T互质的E
			while(!(Gcd(e,t)==1))
				e.Random(digNum);
			temp=ExtendedGcd(e,t,x,y);
			temp=(e*x)%t;
			if(temp==1)
				break;
		}
		e.displayByHex();
		cout<<endl;

		cout<<"公钥n:"<<endl;
		n=p*q;
		n.displayByHex();
		cout<<endl;

		cout<<"私钥d:"<<endl;	
		d=x;
		d.displayByHex();
		cout<<endl;
	}
	void getPublicKey(BigInt& N,BigInt& E)
	{
		N=this->n;
		E=this->e;
	}
	void getPrivateKey(BigInt& N,BigInt& D)
	{
		N=this->n;
		D=this->d;
	}
	bool RobinMiller(const BigInt& n)
	{
		BigInt r,a,y;
		unsigned int s,j;
		r=n-1;
		s=0;

		//找到令N-1=2^S*R的S和R,R为奇数
		while(!r.IsOdd())
		{
			s++;
			r>>1;
		}

		//产生一个小于N-1的检测随机数
		a.Randomsmall(digNum);

		y=PowerMode(a,r,n);

		//检测J=2至J<S轮
		if((!(y==1))&&(!(y==(n-1))))
		{
			j=1;
			while((j<=s-1)&&(!(y==(n-1))))
			{
				y=(y*y)%n;
				if(y==1)
					return false;
				j++;
			}
			if(!(y==(n-1)))
				return false;
		}
		return true;
	}
	//产生一个素数
	BigInt GeneratePrime()
	{
		BigInt n;
		int i=0;
		while(i<5)
		{
			//产生一个待测素数
			GenPrime(n,digNum);
			i=0;
			//进行五轮ROBINMILLER测试,五轮全部通过则素数合格
			//理论素数合格率达99.9%
			for(;i<5;i++)
			{
				cout<<"进行第"<<i+1<<"轮RobinMiller测试"<<endl;
				if(!RobinMiller(n))
				{
					cout<<"测试失败!"<<endl;
					cout<<endl;
					break;
				}
			}
		}
		return n;
	}

	//求两个大数的最大公约数,采用辗转相除法
	BigInt Gcd(const BigInt& m,const BigInt& n)
	{
		//cout << "m: ";m.displayByHex(); cout << "n: ";n.displayByHex();cout << endl;
		//outfile << "m: ";outfile << m; outfile << "n: ";outfile << n;outfile << endl;
		if(n==0)
			return m;
		else
			return Gcd(n,m%n);
	}

	//用扩展欧几里德算法求乘法模逆
	BigInt ExtendedGcd(const BigInt& a, const BigInt& b,BigInt& x, BigInt& y)
	{
		//cout << "a: ";a.displayByHex(); cout << "b: ";b.displayByHex();cout << endl;
		//outfile << "a: ";outfile << a; outfile << "b: ";outfile << b;outfile << endl;
		BigInt t,d;   
		//如果一个操作数为零则无法进行除法运算
		if(b==0)   
		{
			x=1;
			y=0;
			return a;
		}
		BigInt tb=a%b;
		d=ExtendedGcd(b,tb,x,y);   
		t=x;   
		x=y;   
		y=t-((a/b)*y);   
		return d;   
	}
	BigInt Euc(BigInt& E,BigInt& A)
	{
		BigInt M,X,Y,I,J;
		int x,y;
		M=A;
		X=0;
		Y=1;
		x=y=1;
		while((E.GetLength()!=1)||!(E == 0))
		{
			I=M/E;
			J=M%E;
			M=(E);
			E=(J);
			J=(Y);
			Y=Y*I;
			if(x==y)
			{
				if(X>Y)Y=(X-Y);
				else{Y=(Y-X);y=0;}
			}
			else{Y=(X+Y);x=1-x;y=1-y;}
			X=J;
		}
		if(x==0)X=(A-(X));
		return X;
	}
};

#endif
