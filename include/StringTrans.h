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
        StringTrans(string a, int b) : msg(a),BitLen(b){
            this->split();
        }
        
        void changeMessage(const string& str) {
            msg = str;
            this->split();
        }
        
        void setMessage(string a) {
            this->msg = a;
        }
        void setBitLen(int num) {
            this->BitLen = num;
        }

        void split() {
            int n = 0;
            int StrLen = BitLen / 8 - 2;
            code.clear();
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

        vector<BigInt> getCode() {
            return code;
        }
        string genMessage(vector<BigInt>& v) {
            int len = v.size();
            string res, tmp;
            for (int i = 0; i < len; i++) {
                tmp = v[i].BigIntToString();
                res = res + tmp;
            }
            return res;
        }
};

#endif
