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
    
    BigInt p(GeneratePrime(digNum));
    BigInt q(GeneratePrime(digNum));

    LOGLN("Key: 密钥生成");
    BigInt t = (p - 1) * (q - 1);
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
    LOGLN("    公钥e: " << e);

    n = p * q;
    LOGLN("    公钥n: " << n);

    d = x;
    LOGLN("    私钥d: " << d);

}

void Key::quickGenerate(int digNum) {
    this->digNum = digNum;
    srand((unsigned)time(NULL));
    int i, j;
    i = rand() % 10;
    j = rand() % 10;
    while (j == i)
        j = rand() % 10;

    BigInt *p, *q;

    if (digNum == 256) {
        p = new BigInt(prime256[i], 16);
        q = new BigInt(prime256[j], 16);
    }
    else if (digNum == 384) {
        p = new BigInt(prime384[i], 16);
        q = new BigInt(prime384[j], 16);
    }
    else if (digNum == 512) {
        p = new BigInt(prime512[i], 16);
        q = new BigInt(prime512[j], 16);
    }
    else if (digNum == 1024) {
        p = new BigInt(prime1024[i], 16);
        q = new BigInt(prime1024[j], 16);
    }
    LOGLN("QuickKey: 密钥生成");
    BigInt t = ((*p) - 1) * ((*q) - 1);
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
    LOGLN("    公钥e: " << e);

    n = *p * *q;
    LOGLN("    公钥n: " << n);

    d = x;
    LOGLN("    私钥d: " << d);

    delete p;
    delete q;
}

void Key::getPublicKey(BigInt& N, BigInt& E) const 
{
    N = this->n;
    E = this->e;
}
void Key::getPrivateKey(BigInt& N, BigInt& D) const
{
    N = this->n;
    D = this->d;
}
