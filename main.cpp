#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "BigInt.h"
#include "StringTrans.h"
#include "RSA.h"
#include "OAEP.h"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: SimpleRSA [KeyLength|fastTest]\n");
        exit(EXIT_FAILURE);
    }

    int keyLength;
    if (string(argv[1]) != "fastTest") {
        keyLength = atoi(argv[1]);
        
        if (keyLength < 256) {
            fprintf(stderr, "KeyLength must bigger than 256\n");
            exit(EXIT_FAILURE);
        }

        switch (keyLength) {
            case 512:
            case 768:
            case 1024:
            case 2048:
                break;
            default:
                fprintf(stderr, "KeyLength must be 512, 768, 1024, 2048\n");
                exit(EXIT_FAILURE);
        }
    }
    else if (string(argv[1]) == "fastTest") {
        keyLength = -1;
    }
    else {
        fprintf(stderr, "Invalid Argument %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    string msg;
    getline(cin, msg);

    RSA *rsa;
    if (keyLength != -1) {
        rsa = new RSA(keyLength);
    }
    else {
        BigInt strN("838BB8FFAFF51B40E52DF0DB1F0C3466EE14C46A37C973BBD1718A15023F55EA683D0A6B93F3DD0155E9658B6A413D6715E7B8C1E85BC4167CB9914F5E2137C9", 16);
        BigInt strE("ACC86137DDC424D1C24331E10BF9239A49001F34B16BE4B80E39F8D00CD6FA99", 16);
        BigInt strD("39E75F3757C1A40A87493AA67EDB38B7BD31954FF184BD24698A66309CED1B7A0C423D0799D42B96815D7A8009EC5F4CB66628E9657004995FDFB5865B10C3F9", 16);
        rsa = new RSA(strN, strE, strD);
    }
    BigInt N, E;
    rsa->getPublicKey(N, E);

    StringTrans st(msg, N.GetBitLength() - 17);
    cout << "Input Message: " << endl;
    cout << st.toString() << endl;

    OAEP oaep(16, N.GetBitLength() - 17);

    oaep.encode(st);
    cout << "OAEP Encoded Message: " << endl;
    cout << st.toHexString() << endl;

    RSA::encrypt(st, N, E);
    cout << "Encrypted Message: " << endl;
    cout << st.toHexString() << endl;

    rsa->decrypt(st);
    cout << "Decryped Message: " << endl;
    cout << st.toHexString() << endl;

    oaep.decode(st);
    cout << "Decoded Message: " << endl;
    cout << st.toString() << endl;

    return 0;
}
