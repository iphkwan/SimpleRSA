#ifndef RSA_H_
#define RSA_H_

#include <string>
#include <iostream>
#include "BigInt.h"
#include "Key.h"
using namespace std;

//通过getPublicKey把公钥取走，然后调用encrypt加密信息吧。
class RSA
{
private: 
    BigInt n,d;
	BigInt e;
public:
	RSA(int digNum=512)
	{
		Key key(digNum/2);
		key.getPrivateKey(n,d);
		key.getPublicKey(n,e);
	}
	BigInt encrypt(BigInt src)
	{
		return PowerMode(src,e,n);
	}
	BigInt decrypt(BigInt src)
	{
		return PowerMode(src,d,n);
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
};

#endif
