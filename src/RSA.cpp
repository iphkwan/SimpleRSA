#include "RSA.h"
#include <string>
#include <iostream>
#include "BigInt.h"
#include "Key.h"
using namespace std;

RSA::RSA(int digNum = 512)
{
    Key key(digNum / 2);
    key.getPrivateKey(n, d);
    key.getPublicKey(n, e);
    key.getDivNum(p, q);
}
RSA::RSA(BigInt n, BigInt e, BigInt d) 
{
    this->n = n;
    this->e = e;
    this->d = d;
}
BigInt RSA::encrypt(BigInt src)
{
    return BigInt::PowerMode(src, e, n);
}
BigInt RSA::decrypt(BigInt src)
{
    return BigInt::PowerMode(src, d, n);
}
void RSA::getPublicKey(BigInt& N, BigInt& E)
{
    N = this->n;
    E = this->e;
}
void RSA::getPrivateKey(BigInt& N,BigInt& D)
{
    N = this->n;
    D = this->d;
}

//should not exist
void RSA::getDivNum(BigInt& P, BigInt& Q) {
    P = this->p;
    Q = this->q;
}
