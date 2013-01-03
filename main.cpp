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
    return 0;
}
