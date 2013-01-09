#ifndef KEY_H_
#define KEY_H_
#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include "BigInt.h"
#include "PrimeGen.h"
#include "globalData.h"
using namespace std;
class Key
{
private:
    int digNum;
	BigInt p, q, n, e, t, d;
public:
	Key(int digNum)
	{
		this->digNum = digNum;
		srand((unsigned)time(NULL));
		cout << "********随机产生p,q********" << endl;
		cout << endl;
		p = GeneratePrime(digNum);
		cout << endl;
		cout << "产生p:" << endl;
		p.displayByHex();
		cout << endl;
		q = GeneratePrime(digNum);
		cout << endl;
		cout << "产生q:"<<endl;
		q.displayByHex();
		cout << endl;

		cout << "********密钥生成********" << endl;
		cout << endl;
		cout << "公钥e:" << endl;
		t = (p - 1) * (q - 1);
		BigInt x, y, temp;
		while (1)
		{
			e.Random(digNum);
			//产生与T互质的E
			while (!(Gcd(e,t) == 1))
				e.Random(digNum);
			temp = ExtendedGcd(e, t, x, y);
			temp = (e * x) % t;
			if (temp == 1)
				break;
		}
		e.displayByHex();
		cout << endl;

		cout << "公钥n:" << endl;
		n = p * q;
		n.displayByHex();
		cout << endl;

		cout << "私钥d:" << endl;	
		d = x;
		d.displayByHex();
		cout << endl;
	}

    // quick Generate Key, digNum1 = 256/384/512/1024, digNum2 no uses.
    Key(int digNum1, int digNum2) {
        this->digNum = digNum1;
		srand((unsigned)time(NULL));
        int i, j;
        i = rand() % 10;
        j = rand() % 10;
        while (j == i)
            j = rand() % 10;
        if (digNum1 == 256) {
            p.readHexNum(prime256[i]);
            q.readHexNum(prime256[j]);
        }
        else if (digNum1 == 384) {
            p.readHexNum(prime384[i]);
            q.readHexNum(prime384[j]);
        }
        else if (digNum1 == 512) {
            p.readHexNum(prime512[i]);
            q.readHexNum(prime512[j]);
        }
        else if (digNum1 == 1024) {
            p.readHexNum(prime1024[i]);
            q.readHexNum(prime1024[j]);
        }
		cout << "********密钥生成********" << endl;
		cout << endl;
		cout << "公钥e:" << endl;
		t = (p - 1) * (q - 1);
		BigInt x, y, temp;
		while (1)
		{
			e.Random(digNum);
			//产生与T互质的E
			while (!(Gcd(e,t) == 1))
				e.Random(digNum);
			temp = ExtendedGcd(e, t, x, y);
			temp = (e * x) % t;
			if (temp == 1)
				break;
		}
		e.displayByHex();
		cout << endl;

		cout << "公钥n:" << endl;
		n = p * q;
		n.displayByHex();
		cout << endl;

		cout << "私钥d:" << endl;	
		d = x;
		d.displayByHex();
		cout << endl;
    }

	void getPublicKey(BigInt& N, BigInt& E)
	{
		N = this->n;
		E = this->e;
	}
	void getPrivateKey(BigInt& N, BigInt& D)
	{
		N = this->n;
		D = this->d;
	}

    //This function should not exist. It just help us to demonstrate our work.
    void getDivNum(BigInt& P, BigInt& Q) {
        P = this->p;
        Q = this->q;
    }
};

#endif
