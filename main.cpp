#include <iostream>
#include <cmath>
#include <string>
#include <string.h>
#include "BigInt.h"
#include "PrimeGen.h"
#include "Key.h"
#include "RSA.h"
#include "OAEP.h"
#include <ctime>
using namespace std;

void test_BigInt();
void test_RSA();
int main()
{
    cout << "Hello RSA project!\n";
    //test_BigInt();
    test_RSA();
    return 0;
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
    cout << "input the model (512, 768, 1024?):\n";
    cin >> digNum;
    RSA rsa(digNum);
    BigInt test, n, e;
    rsa.getPublicKey(n, e);

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
