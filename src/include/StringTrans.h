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
        /**
         * 构造函数
         *
         * @param a 消息原文
         * @param b 每段的长度
         */
        StringTrans(string a, int b);
        /**
         * 改变容纳的消息
         *
         * @param str
         */
        void changeMessage(const string& str);
        /**
         * 手动设置message (需要手动调用split)
         *
         * @param a
         */
        void setMessage(string a);
        /**
         * 手动设置每段的长度 (需要手动调用split)
         *
         * @param num 长度
         */
        void setBitLen(int num);
        /**
         * 取得分段的字符串编码数值
         *
         * @return 每段BitLen的字符串编码
         */
        vector<BigInt> getCode();
        /**
         * 对储存的str进行分段，每段BitLen长
         *
         */
        void split();
        /**
         * 对于一个字符串编码分组，把它所有的分片重新组合成一个string
         * 
         * @param v 分组
         * @return 重新组合的string
         */
        static string genMessage(const vector<BigInt>& v);
};

#endif
