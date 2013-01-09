#ifndef RSA_H_
#define RSA_H_

#include "BigInt.h"
#include "Key.h"

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
         */
	    RSA(int digNum = 512) : key(digNum / 2) {};
        
        /**
         * 已知n, e, d
         *
         * @param n
         * @param e 公钥
         * @param d 私钥
         */
	    RSA(BigInt& n, BigInt& e, BigInt& d)
            :key(n, e, d) {};

        /**
         * 对消息进行加密
         *
         * @param [in] src 明文消息
         * @return 加密后的消息
         */
	    static BigInt encrypt(const BigInt& src, const BigInt& N, const BigInt& E);
        BigInt encrypt(const BigInt& src);

        /**
         * 对消息进行解密
         *
         * @param [in] src 接收的加密消息
         * @return 明文
         */
	    static BigInt decrypt(const BigInt& src, const BigInt& N, const BigInt& D);
        BigInt decrypt(const BigInt& src) const;

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

        /**
         *
         */
	    void getDivNum(BigInt& P, BigInt& Q) const ;
};
#endif
