#ifndef STRINGTRANS_H_
#define STRINGTRANS_H_

#include <string>
#include "BigInt.h"
#include "OAEP.h"
#include "RSA.h"
using namespace std;

class StringTrans {
    private:
        string msg;
        int BitLen;
        
    public:
        StringTrans(string a, int b) {
            msg = a;
            BitLen = b;
        }
        void output() {
            BigInt a;
            a.stringToBigInt(msg);
            a.BigIntToString();
        }
};

#endif
