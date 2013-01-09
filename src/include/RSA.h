#ifndef RSA_H_
#define RSA_H_

#include "BigInt.h"

//通过getPublicKey把公钥取走，然后调用encrypt加密信息吧。
class RSA
{
    private: 
        BigInt n,d;
	    BigInt e;
        BigInt p, q;    // These two elements should not exist, just help us to demonstrate our work.
    public:
	    RSA(int digNum);
	    RSA(BigInt n, BigInt e, BigInt d);
	    BigInt encrypt(BigInt src);
	    BigInt decrypt(BigInt src);
	    void getPublicKey(BigInt& N, BigInt& E);
	    void getPrivateKey(BigInt& N,BigInt& D);
	    void getDivNum(BigInt& P, BigInt& Q);
};

#endif
