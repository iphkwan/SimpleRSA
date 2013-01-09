#ifndef PRIMEGEN_H_
#define PRIMEGEN_H_

#include "BigInt.h"

void GenPrime(BigInt& n, int digNum);
bool RobinMiller(const BigInt& n, int digNum);
BigInt GeneratePrime(int digNum);


#endif
