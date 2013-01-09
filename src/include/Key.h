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
    Key(BigInt& n, BigInt& e, BigInt& d): n(n), e(e), d(d) {}
    Key(int digNum){this->digNum = digNum; generate(digNum);};
	void getPublicKey(BigInt& N, BigInt& E) const;
	void getPrivateKey(BigInt& N, BigInt& D) const;
	void getDivNum(BigInt& P, BigInt& Q) const;
    void generate(int);
    void quickGenerate(int);
};

#endif
