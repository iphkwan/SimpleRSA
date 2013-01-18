#ifndef RSA_H_
#define RSA_H_

#include "BigInt.h"
#include "Key.h"
#include "StringTrans.h"

//通过getPublicKey把公钥取走，然后调用encrypt加密信息吧。
class RSA
{
    private: 
        Key key;
    public:
        /**
         * 构造函数
         *
         * @param digNum 密钥长度
         * @param fast 是否采取快速生成素数
         */
        RSA(int digNum = 512) : key(digNum / 2) {};
        
        /**
         * 已知n, e, d
         *
         * @param key
         */
        RSA(const Key& key) :key(key) {};

        /**
         * 已知n, e, d
         *
         * @param N
         * @param E
         * @param D
         */
        RSA(const BigInt& N, const BigInt& E, const BigInt& D): key(N, E, D) {}

        /**
         * 对消息进行加密
         *
         * @param [in] src 明文消息
         * @return 加密后的消息
         */
        static BigInt encrypt(const BigInt& src, const BigInt& N, const BigInt& E);
        BigInt encrypt(const BigInt& src) const;
        static void encrypt(StringTrans& st, const BigInt& N, const BigInt& E);

        /**
         * 对消息进行解密
         *
         * @param [in] src 接收的加密消息
         * @return 明文
         */
        static BigInt decrypt(const BigInt& src, const BigInt& N, const BigInt& D);
        BigInt decrypt(const BigInt& src) const;
        void decrypt(StringTrans& st);

        /**
         * 取公钥
         *
         * @param [out] N
         * @param [out] E
         */
        void getPublicKey(BigInt& N, BigInt& E) const ;

        /**
         * 取私钥
         *
         * @param [out] N
         * @param [out] D
         */
        void getPrivateKey(BigInt& N,BigInt& D) const ;

};
#endif
