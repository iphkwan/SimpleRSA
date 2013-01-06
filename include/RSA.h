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
        BigInt p, q;    // These two elements should not exist, just help us to demonstrate our work.
    public:
	    RSA(int digNum = 512)
	    {
		    Key key(digNum / 2);
		    key.getPrivateKey(n, d);
		    key.getPublicKey(n, e);
            key.getDivNum(p, q);
	    }
        RSA(BigInt n, BigInt e, BigInt d) 
        {
            this->n = n;
            this->e = e;
            this->d = d;
        }
	    BigInt encrypt(BigInt src)
	    {
		    return PowerMode(src, e, n);
	    }
	    BigInt decrypt(BigInt src)
	    {
		    return PowerMode(src, d, n);
	    }
	    void getPublicKey(BigInt& N, BigInt& E)
	    {
		    N = this->n;
		    E = this->e;
	    }
	    void getPrivateKey(BigInt& N,BigInt& D)
	    {
		    N = this->n;
		    D = this->d;
	    }

        //should not exist
        void getDivNum(BigInt& P, BigInt& Q) {
            P = this->p;
            Q = this->q;
        }
};

#endif
