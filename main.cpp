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
        printf("Usage: SimpleRSA [KeyLength]\n");
        exit(EXIT_FAILURE);
    }


    int keyLength = atoi(argv[1]);
    
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

    string msg;
    getline(cin, msg);

    StringTrans st(msg, keyLength - 19);
    cout << "Input Message: " << endl;
    cout << st.toString() << endl;

    RSA rsa(keyLength);
    OAEP oaep(16, keyLength - 19);   

    BigInt N, E;
    rsa.getPublicKey(N, E);

    StringTrans::iterator itr;
    for (itr = st.begin(); itr != st.end(); ++ itr)
        *itr = oaep.encode(*itr);
    cout << "OAEP Encoded Message: " << endl;
    cout << st.toHexString() << endl;

    for (itr = st.begin(); itr != st.end(); ++ itr)
        *itr = RSA::encrypt(*itr, N, E);

    cout << "Encrypted Message: " << endl;
    cout << st.toHexString() << endl;

    for (itr = st.begin(); itr != st.end(); ++ itr)
        *itr = rsa.decrypt(*itr);

    cout << "Decryped Message: " << endl;
    cout << st.toHexString() << endl;


    for (itr = st.begin(); itr != st.end(); ++ itr)
        *itr = oaep.decode(*itr);

    cout << "Decoded Message: " << endl;
    cout << st.toString() << endl;

    return 0;
}
