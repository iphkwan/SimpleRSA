#ifndef KEY_H_
#define KEY_H_

#include "BigInt.h"

class Key
{
private:
    int digNum;
	BigInt p, q, n, e, t, d;
public:
	Key():digNum(0) {};
    Key(int digNum){this->digNum = digNum; generate(digNum);};
	void getPublicKey(BigInt& N, BigInt& E);
	void getPrivateKey(BigInt& N, BigInt& D);
	void getDivNum(BigInt& P, BigInt& Q);
    void generate(int);
    void quickGenerate(int);
};

#endif
