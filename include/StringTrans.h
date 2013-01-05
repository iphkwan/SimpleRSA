#ifndef STRINGTRANS_H_
#define STRINGTRANS_H_

#include <string>
#include <vector>
#include "BigInt.h"
#include "OAEP.h"
#include "RSA.h"
using namespace std;

class StringTrans {
    private:
        string msg;
        int BitLen;
        vector<BigInt> code;
        
    public:
        StringTrans(string a, int b) : msg(a),BitLen(b){}

        void split() {
            int n = 0;
            int StrLen = BitLen / 2;
            do
            {
                code.push_back(BigInt());
                string segment = msg.substr(n * StrLen,StrLen);
                code[n].stringToBigInt(segment);
                code[n].BigIntToString();
                n++;
            }
            while (n * StrLen < msg.length());
        }
};

#endif
