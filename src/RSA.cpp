#include "RSA.h"
#include "BigInt.h"
#include "Key.h"
#include "utils.h"
#include <cstdio>

BigInt RSA::encrypt(const BigInt& src, const BigInt& N, const BigInt& E)
{
    if (!(src < N)) {
        fprintf(stderr, "RSA Error: Encrypt source is bigger than N\n");
        exit(EXIT_FAILURE);
    }
    return BigInt::PowerMode(src, E, N);
}
BigInt RSA::encrypt(const BigInt& src) const
{
    BigInt N, E;
    key.getPublicKey(N, E);
    return RSA::encrypt(src, N, E);
}
BigInt RSA::decrypt(const BigInt& src, const BigInt& N, const BigInt& D)
{
    if (!(src < N)) {
        fprintf(stderr, "RSA Error: Encrypt source is bigger than N\n");
        exit(EXIT_FAILURE);
    }
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

