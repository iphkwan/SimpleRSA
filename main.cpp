#include <iostream>
#include <cmath>
#include <string>
#include <string.h>
#include <cstdio>
#include "BigInt.h"
#include "PrimeGen.h"
#include "Key.h"
#include "RSA.h"
#include "OAEP.h"
#include "StringTrans.h"
#include <ctime>
using namespace std;

void test_BigInt();
void test_RSA();
void test_OAEP();
void test_stringTrans();
int main()
{
    cout << "Hello RSA project!\n";
    //test_BigInt();
    //test_RSA();
    //test_OAEP();
    test_stringTrans();
    return 0;
}

void test_stringTrans() {
    string str;
    getline(cin, str);
    StringTrans a(str, 16);
    a.split();
}

void test_BigInt() {
    // test BigInt
    cout << "------------------------\n";
    cout << "This is BigInt test.\n";
    cout << "------------------------\n";
    BigInt a, b, c;
    string tmp;
    cout << "please input a:\n";
    cin >> tmp;
    a.readBinaryNum(tmp);
    cout << "please input b:\n";
    cin >> tmp;
    b.readBinaryNum(tmp);
    cout << "a = ";
    cout << a << endl;
    cout << "b = ";
    cout << b << endl;
    cout << "a + b = ";
    c = a + b;
    cout << c << endl;
    cout << "a * b = ";
    c = a * b;
    cout << c << endl;
    cout << "a - b = ";
    c = a - b;
    cout << c << endl;
    cout << "a % b = ";
    c = a % b;
    cout << c << endl;
    cout << "a < b ? ";
    if (a < b)
        cout << "True!\n";
    else
        cout << "False!\n";
    cout << "please input binary positive number:\n";
    cin >> tmp;
    c.readBinaryNum(tmp);
    cout << "c = ";
    cout << c << endl;
    cout << "------------------------\n";
}

void test_RSA() {
    srand((unsigned) time(NULL));

    int digNum;
    cout << "input the model (512, 768, 1024? it's not less than 256):\n";
    cin >> digNum;
    if (digNum < 256) {
        cout << "It may leads error.\n";
        return;
    }
    RSA rsa(digNum);
    BigInt test, n, e;
    rsa.getPublicKey(n, e);
    cout << "Generating test message...\n";
    test.Random(digNum);
    while (!(test < n))
        test.Random(digNum);
    cout << "test message: ";
    test.displayByHex();

    BigInt encp = rsa.encrypt(test);
    cout << "after encrypt: ";
    encp.displayByHex();

    cout << "after decrypt: ";
    BigInt decp = rsa.decrypt(encp);
    decp.displayByHex();
}

void test_OAEP() {
    srand((unsigned) time(NULL));
    int digNum, k;
    cout << "input the msg Bit length(m>=512): \n";
    cin >> digNum;
    cout << "input oaep_K(k>=256): \n";
    cin >> k;

    printf("------------OAEP_SAMPLE(m = %d, k = %d)---------------\n", digNum, k);
    OAEP test(k, digNum);
    BigInt msg;
    msg.Random(digNum);
    cout << "the msg is: " << msg;
    msg = test.oaep_encode(msg);
    test.oaep_decode(msg);
    return;
}
