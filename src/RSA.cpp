#include "RSA.h"
#include "BigInt.h"
#include "Key.h"
#include "utils.h"

BigInt RSA::encrypt(const BigInt& src, const BigInt& N, const BigInt& E)
{
    return BigInt::PowerMode(src, E, N);
}
BigInt RSA::encrypt(const BigInt& src)
{
    BigInt N, E;
    key.getPublicKey(N, E);
    return RSA::encrypt(src, N, E);
}
BigInt RSA::decrypt(const BigInt& src, const BigInt& N, const BigInt& D)
{
    return BigInt::PowerMode(src, D, N);
}
BigInt RSA::decrypt(const BigInt& src) const
{
    BigInt N, D;
    key.getPrivateKey(N, D);
    return RSA::decrypt(src, N, D);
}
void RSA::getPublicKey(BigInt& N, BigInt& E) const 
{
    key.getPublicKey(N, E);
}
void RSA::getPrivateKey(BigInt& N,BigInt& D) const
{
    key.getPrivateKey(N, D);
}

//should not exist
void RSA::getDivNum(BigInt& P, BigInt& Q) const {
    key.getDivNum(P, Q);
}
