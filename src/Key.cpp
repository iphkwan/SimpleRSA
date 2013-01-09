#include "Key.h"
#include "BigInt.h"
#include "PrimeGen.h"
#include "globalData.h"
#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include "utils.h"

using namespace std;

void Key::generate(int digNum) {
    this->digNum = digNum;
    srand((unsigned)time(NULL));
    LOGLN("===========Key===========");
    LOGLN("| 随机产生p,q");
    p = GeneratePrime(digNum);
    LOGLN("| \t产生p: " << p);
    q = GeneratePrime(digNum);
    LOGLN("| \t产生q: " << q);
    LOGLN("");

    LOGLN("| 密钥生成");
    t = (p - 1) * (q - 1);
    BigInt x, y, temp;
    while (1)
    {
        e.Random(digNum);
        //产生与T互质的E
        while (!(BigInt::Gcd(e,t) == 1))
            e.Random(digNum);
        temp = BigInt::ExtendedGcd(e, t, x, y);
        temp = (e * x) % t;
        if (temp == 1)
            break;
    }
    LOGLN("| \t公钥e: " << e);

    n = p * q;
    LOGLN("| \t公钥n: " << n);

    d = x;
    LOGLN("| \t私钥d: " << d);
    LOGLN("=========================");

}

void Key::quickGenerate(int digNum) {
    this->digNum = digNum;
    srand((unsigned)time(NULL));
    int i, j;
    i = rand() % 10;
    j = rand() % 10;
    while (j == i)
        j = rand() % 10;
    if (digNum == 256) {
        p.readHexNum(prime256[i]);
        q.readHexNum(prime256[j]);
    }
    else if (digNum == 384) {
        p.readHexNum(prime384[i]);
        q.readHexNum(prime384[j]);
    }
    else if (digNum == 512) {
        p.readHexNum(prime512[i]);
        q.readHexNum(prime512[j]);
    }
    else if (digNum == 1024) {
        p.readHexNum(prime1024[i]);
        q.readHexNum(prime1024[j]);
    }
    LOGLN("======Key QuickGenerate========");
    LOGLN("| 密钥生成");
    t = (p - 1) * (q - 1);
    BigInt x, y, temp;
    while (1)
    {
        e.Random(digNum);
        //产生与T互质的E
        while (!(BigInt::Gcd(e,t) == 1))
            e.Random(digNum);
        temp = BigInt::ExtendedGcd(e, t, x, y);
        temp = (e * x) % t;
        if (temp == 1)
            break;
    }
    LOGLN("|\t公钥e: " << e);

    n = p * q;
    LOGLN("|\t公钥n: " << n);

    d = x;
    LOGLN("|\t私钥d: " << d);
    LOGLN("===============================");

}

void Key::getPublicKey(BigInt& N, BigInt& E)
{
    N = this->n;
    E = this->e;
}
void Key::getPrivateKey(BigInt& N, BigInt& D)
{
    N = this->n;
    D = this->d;
}

//This function should not exist. It just help us to demonstrate our work.
void Key::getDivNum(BigInt& P, BigInt& Q) {
    P = this->p;
    Q = this->q;
}
