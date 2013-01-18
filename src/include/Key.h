#ifndef KEY_H_
#define KEY_H_

#include "BigInt.h"
#include "utils.h"

class Key
{
private:
    int digNum;
    BigInt n, e, d;
public:
    Key(): digNum(0) {};
    Key(const BigInt& n, const BigInt& e, const BigInt& d): n(n), e(e), d(d) {
        LOGLN("Key: 载入密钥");
        LOGLN("    公钥e: " << e);
        LOGLN("    公钥n: " << n);
        LOGLN("    私钥d: " << d);
    };
    Key(int digNum) {
        this->digNum = digNum; 
        generate(digNum);
    }
    void getPublicKey(BigInt& N, BigInt& E) const;
    void getPrivateKey(BigInt& N, BigInt& D) const;
    void generate(int);
};

#endif
