#ifndef KEY_H_
#define KEY_H_

#include "BigInt.h"

class Key
{
private:
    int digNum;
	BigInt p, q, n, e, t, d;
public:
	Key(int);
	Key(int, int);
	void getPublicKey(BigInt& N, BigInt& E);
	void getPrivateKey(BigInt& N, BigInt& D);
	void getDivNum(BigInt& P, BigInt& Q);
};

#endif
