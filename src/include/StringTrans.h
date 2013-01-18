#ifndef STRINGTRANS_H_
#define STRINGTRANS_H_

#include "BigInt.h"
#include <vector>
using namespace std;

class StringTrans : public vector<BigInt> {
    private:
        /**
         * 对储存的str进行分段，每段BitLen长
         *
         */
        void split(const string&);
        int BitLen;

    public:
        /**
         * 构造函数
         *
         * @param a 消息原文
         * @param b 每段的长度
         */
        StringTrans(const string& a, int b);
        /**
         * 把它所有的分片重新组合成一个string
         * 
         * @return 重新组合的string
         */
        string toString();
        string toHexString();

        /**
         * 各种合并函数
         */
        void push_back(const string&);
        void push_back(const BigInt&);
        StringTrans& operator+= (const string&);
        StringTrans& operator+= (const BigInt&);
        StringTrans& operator+= (const StringTrans&);
};

#endif
