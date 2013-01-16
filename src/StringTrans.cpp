#include "StringTrans.h"
#include <string>
#include <vector>
#include "BigInt.h"
#include "OAEP.h"
#include "RSA.h"
#include "utils.h"
using namespace std;

StringTrans::StringTrans(const string& a, int b) {
    this->split(a, b);
}

void StringTrans::split(const string& msg, int BitLen) {
    int n = 0;
    int StrLen = BitLen / 8;
    (*this).clear();
    do
    {
        string segment = msg.substr(n * StrLen, StrLen);
        push_back(BigInt(segment, 10));
        n++;
    }
    while (n * StrLen < msg.length());
}

string StringTrans::toHexString() {
    int len = this->size();
    string res, tmp;
    for (int i = 0; i < len; i++) {
        tmp = (*this)[i].ToHexString();
        res = res + tmp;
    }
    return res;
}

string StringTrans::toString() {
    int len = this->size();
    string res, tmp;
    for (int i = 0; i < len; i++) {
        tmp = (*this)[i].ToString();
        res = res + tmp;
    }
    return res;
}
