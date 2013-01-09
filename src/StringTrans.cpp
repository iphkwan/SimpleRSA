#include "StringTrans.h"
#include <string>
#include <vector>
#include "BigInt.h"
#include "OAEP.h"
#include "RSA.h"
#include "utils.h"
using namespace std;

StringTrans::StringTrans(string a, int b) : msg(a),BitLen(b){
    this->split();
}

void StringTrans::changeMessage(const string& str) {
    msg = str;
    this->split();
}

void StringTrans::setMessage(string a) {
    this->msg = a;
}
void StringTrans::setBitLen(int num) {
    this->BitLen = num;
}

void StringTrans::split() {
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

vector<BigInt> StringTrans::getCode() {
    return code;
}
string StringTrans::genMessage(vector<BigInt>& v) {
    int len = v.size();
    string res, tmp;
    for (int i = 0; i < len; i++) {
        tmp = v[i].BigIntToString();
        res = res + tmp;
    }
    return res;
}
