#ifndef STRINGTRANS_H_
#define STRINGTRANS_H_

#include "BigInt.h"
#include <vector>
using namespace std;

class StringTrans {
    private:
        string msg;
        int BitLen;
        vector<BigInt> code;
        
        void split();
    public:
        StringTrans(string a, int b);
        void changeMessage(const string& str);
        void setMessage(string a);
        void setBitLen(int num);
        vector<BigInt> getCode();
        static string genMessage(const vector<BigInt>& v);
};

#endif
