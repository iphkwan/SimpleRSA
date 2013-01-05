#ifndef OAEP_H_
#define OAEP_H_

#include <iostream>
#include <string.h>
#include "BigInt.h"
#include "Key.h"
using namespace std;

class OAEP
{
    private:
        int K, M;
        BigInt k_to_m(const BigInt& cnt) {
            //cnt have k bits
            BigInt res(cnt), tmp(cnt);
            while (res.GetBitLength() < M) {
                tmp = (tmp << 1);
                res = (res ^ tmp);
            }
            return res;
        }
        BigInt m_to_k(const BigInt& cnt) {
            //the digits of cnt must more than k
            BigInt filter(1), res(0), tmp(cnt);
            for (int i = 0; i < K/16; i++)
                filter = (filter << 16);
            filter = (filter << (K % 16));
            filter = filter - 1;
            res = filter;
            filter = (filter >> 1);
            while (tmp.GetBitLength() >= K) {
                res = (filter & tmp) ^ res;
                tmp = (tmp >> 1);
            }
            return res;
        }
    public:
        OAEP(int k = 16, int m = 32) {
            this->K = k;
            this->M = m;
        }
        BigInt oaep_encode(const BigInt& cnt) {
            BigInt r, tmp, P1, P2;
            r.Random(K);
            cout << "the encode random number is " << r;
            tmp = k_to_m(r);
            P1 = cnt ^ tmp;

            tmp = m_to_k(P1);
            P2 = tmp ^ r;

            for (int i = 0; i < K/16; i++)
                P1 = (P1 << 16);
            P1 = (P1 << (K % 16));
            P1 = P1 | P2;
            cout << "encoded msg: " << P1;
            return P1;
        }
        BigInt oaep_decode(const BigInt& cnt) {
            BigInt r, tmp, P1(cnt), P2, res;
            BigInt filter(1);
            for (int i = 0; i < K/16; i++)
                filter = (filter << 16);
            filter = (filter << (K % 16));
            filter = filter - 1;

            P2 = (cnt & filter);
            
            for (int i = 0; i < K/16; i++)
                P1 = (P1 >> 16);
            P1 = (P1 >> (K % 16));
            tmp = m_to_k(P1);
            r = (tmp ^ P2);
            cout << "the decode random number is " << r;

            tmp = k_to_m(r);
            res = (tmp ^ P1);
            cout << "decoded msg: " << res;
            return res;
        }
};

#endif
