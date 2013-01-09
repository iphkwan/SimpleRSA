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
        
    public:
		StringTrans(string a, int b);
		void changeMessage(const string& str);
		void setMessage(string a);
		void setBitLen(int num);
		void split();
		vector<BigInt> getCode();
		string genMessage(vector<BigInt>& v);
};

#endif
