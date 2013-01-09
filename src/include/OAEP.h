#ifndef OAEP_H_
#define OAEP_H_

#include "BigInt.h"

class OAEP
{
    private:
        int K, M;
        BigInt k_to_m(const BigInt& cnt);
        BigInt m_to_k(const BigInt& cnt);
    public:
		OAEP(int k = 16, int m = 32);
		void changeMode(int k, int m);
		BigInt oaep_encode(const BigInt& cnt);
		BigInt oaep_decode(const BigInt& cnt);
};

#endif
