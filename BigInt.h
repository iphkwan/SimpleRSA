#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <string.h>
using namespace std;

const int base = 10000;
const int width = 4;
const int N = 1000;

class BigInt
{
    private:
        int ln, v[N];
    public:
        BigInt (int r = 0) {
            for (ln = 0; r > 0; r /= base)
                v[ln++] = r % base;
        }
        BigInt& operator = (const BigInt& r) {
            memcpy(this, &r, (r.ln + 1) * sizeof(int));
            return *this;
        }
        friend bool operator < (const BigInt& a, const BigInt& b);
        friend bool operator <= (const BigInt& a, const BigInt& b);
        friend bool operator == (const BigInt& a, const BigInt& b);
        friend BigInt operator + (const BigInt& a, const BigInt& b);
        friend BigInt operator - (const BigInt& a, const BigInt& b);
        friend BigInt operator * (const BigInt& a, const BigInt& b);
        friend BigInt operator % (const BigInt& a, const BigInt& b);

        int digitCount() {
            if (ln == 0)
                return 0;
            int res = (ln - 1) * width;
            for (int t = v[ln - 1]; t; ++res, t /= 10);
            return res;
        }

        bool read(string buf) {
            int w, u, len = buf.length();
            memset(this, 0, sizeof(BigInt));
            if (len == 1 && buf[0] == '0')
                return 1;
            bool is_positive = true;
            if (buf[0] == '-') {
                is_positive = false;
                len --;
                buf.erase(buf.begin());
            }
            for (w = 1, u = 0; len; ) {
                u += (buf[--len] - '0') * w;
                if (w * 10 == base) {
                    v[ln++] = u;
                    u = 0, w = 1;
                }
                else
                    w *= 10;
            }
            if (w != 1)
                v[ln++] = u;
            if (!is_positive)
                v[ln - 1] = - v[ln - 1];
            return 1;
        }
        bool readBinaryNum(string buf) {
            // Require Positive Number !!!
            int i, len = buf.length();
            memset(this, 0, sizeof(BigInt));
            if (len == 1 && buf[0] == '0')
                return 1;
            BigInt p(1), res(0), bs(2);
            for (i = len - 1; i >= 0; i--) {
                if (buf[i] == '1')
                    res = res + p;
                p = p * bs;
            }
            *this = res;
            return 1;
        }

        void write() {
            int i;
            printf("%d", ln == 0? 0: v[ln - 1]);
            for (i = ln - 2; i >= 0; i--)
                printf("%04d", v[i]);
            printf("\n");
        }
};

bool operator < (const BigInt& a, const BigInt& b) {
    int i;
    if (a.ln == 0) {
        if (b.ln == 0)
            return false;
        return b.v[0] > 0;
    }
    if (b.ln == 0) {
        if (a.ln == 0)
            return false;
        return a.v[0] < 0;
    }
    if (a.ln != b.ln)
        return a.ln < b.ln;
    for (i = a.ln - 1; i >= 0 && a.v[i] == b.v[i]; i--);
    return i < 0 ? 0 : a.v[i] < b.v[i];
}

bool operator <= (const BigInt& a, const BigInt& b) {
    return !(b < a);
}

bool operator == (const BigInt& a, const BigInt& b) {
    if (a.ln != b.ln)
        return false;
    for (int i = a.ln - 1; i >=0; i--)
        if (a.v[i] != b.v[i])
            return false;
    return true;
}

BigInt operator + (const BigInt& a, const BigInt& b) {
    BigInt res;
    int i, cy = 0;
    for (i = 0; i < a.ln || i < b.ln || cy > 0; i++) {
        if (i < a.ln)
            cy += a.v[i];
        if (i < b.ln)
            cy += b.v[i];
        res.v[i] = cy % base;
        cy /= base;
    }
    res.ln = i;
    return res;
}

BigInt operator - (const BigInt& a, const BigInt& b) {
    BigInt res;
    if (a < b){
        res = b - a;
        res.v[res.ln - 1] = - res.v[res.ln - 1];
        return res;
    }
    int i, cy = 0;
    for (res.ln = a.ln, i = 0; i < res.ln; i++) {
        res.v[i] = a.v[i] - cy;
        if (i < b.ln)
            res.v[i] -= b.v[i];
        if (res.v[i] < 0)
            cy = 1, res.v[i] += base;
        else
            cy = 0;
    }
    while (res.ln > 0 && res.v[res.ln - 1] == 0)
        res.ln --;
    return res;
}

BigInt operator * (const BigInt& a, const BigInt& b) {
    BigInt res;
    res.ln = 0;
    if (0 == b.ln) {
        res.v[0] = 0;
        return res;
    }
    int i, j, cy;
    for (i = 0; i < a.ln; i++) {
        for (j = cy = 0; j < b.ln || cy > 0; j++, cy /= base) {
            if (j < b.ln)
                cy += a.v[i] * b.v[j];
            if (i + j < res.ln)
                cy += res.v[i + j];
            if (i + j >= res.ln)
                res.v[res.ln++] = cy % base;
            else
                res.v[i + j] = cy % base;
        }
    }
    return res;
}

BigInt operator % (const BigInt& aa, const BigInt& b) {
    // b > 0
    if (b == BigInt(1)) {
        BigInt res(1);
        return res;
    }
    BigInt a = aa;
    while (a < BigInt(0))
        a = a + b;
    BigInt tmp, mod, res;
    BigInt bs = BigInt(base);
    int i, lf, rg, mid;
    mod.v[0] = mod.ln = 0;
    for (i = a.ln - 1; i >= 0; i--) {
        mod = mod * bs + BigInt(a.v[i]);
        for (lf = 0, rg = base - 1; lf < rg; ) {
            mid = (lf + rg + 1) / 2;
            if (b * BigInt(mid) <= mod)
                lf = mid;
            else
                rg = mid - 1;
        }
        res.v[i] = lf;
        mod = mod - b * BigInt(lf);
    }
    mod.ln = a.ln;
    while (mod.ln > 0 && mod.v[mod.ln - 1] == 0)
        mod.ln--;
    return mod;
}
#endif
