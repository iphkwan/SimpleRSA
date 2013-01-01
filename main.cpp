#include <iostream>
#include <cmath>
#include <string>
#include <string.h>
#include "BigInt.h"
#include "PrimeGen.h"
#include "Key.h"
#include "RSA.h"
#include "OAEP.h"
using namespace std;

int main()
{
    cout << "Hello RSA project!\n";

    // test BigInt
    BigInt a, b, c;
    string tmp;
    cout << "please input a:\n";
    cin >> tmp;
    a.read(tmp);
    cout << "please input b:\n";
    cin >> tmp;
    b.read(tmp);
    cout << "a = ";
    a.write();
    cout << "b = ";
    b.write();
    cout << "a + b = ";
    c = a + b;
    c.write();
    cout << "a * b = ";
    c = a * b;
    c.write();
    cout << "a - b = ";
    c = a - b;
    c.write();
    cout << "a % b = ";
    c = a % b;
    c.write();
    cout << "a < b ? ";
    if (a < b)
        cout << "True!\n";
    else
        cout << "False!\n";
    cout << "please input binary positive number:\n";
    cin >> tmp;
    c.readBinaryNum(tmp);
    cout << "c = ";
    c.write();
    return 0;
}
