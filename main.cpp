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
#include <vector>
using namespace std;

void test_BigInt();
void test_RSA();
void test_OAEP();
void test_stringTrans();
void test_example();

int main()
{
    cout << "Hello RSA project!\n";
    //test_BigInt();
    //test_RSA();
    //test_OAEP();
    //test_stringTrans();
    test_example();
    return 0;
}

void test_example() {
    cout << "-------------------example_demo---------------------\n";
    string sn = "D9AA0B3879C08D517DA6D06964FB75160D640107B3D840F0A7A9DF63481E22D1078DA38A26E463DCD0D8F1A8C553FEE005EDD3637B34FF9E444B7A3F9011CB7850BB8D368907DCA712F4627C7E61A94BA934AB3191FCA08366D738E2E853C041AE3C03C7C46C9F5B92A4F896629EA6CA1AE0C3BE7978C605155F08DDF7594CD3";
    string se = "92534F70144A397F8E319CB3A7B0A0B1B147D71624905496563AC09EB34416599472F9B0752513DA8AFB9F616E7A42409E0EBDEF64CFF67FE15945D9C9FEFDFB";
    string sd = "348B8B35B82D3A61C1147B3A57432D40EED96ABEF892EB141C638D04EB14CF15C746F906C4F536E350DA233B46BF4232E2E190BFCF5BC7E2E2B3DA8726F992E251493A799549D90CDD6179E4CCF06E933A596FE71AC165D3500D91D6F7C158F152244630497ED73A3FDEF1AED92531C37D39DCB551B1296975D973B41B4CF723";
    BigInt n, e, d;
    n.readHexNum(sn);
    e.readHexNum(se);
    d.readHexNum(sd);
    RSA rsa1024(n, e, d);

    sn = "AB7AFFB2F11A14E76757ECEB2B879DF87E714919480FB9A3EE3734A5C69D7A4E4C60B674A4B5FBB4CF2B9DAE20579158838766E643875A6F08BCB2EFE806BA98A0492252BD9AA48FCDA4247CBFF3B96C62AF981396A3F1B61ED9316C2A1E4553";
    se = "F8AE063CD67047F44EE5BB23A9FE26534C12A84342809FC5B6FB8FAED7C31BA0D3F2A250E84324E2DF34156466719C2B";
    sd = "29A294DC7D66B5F36BBA0294065F5A0E6390F53EC95C89B19054CEBE4322B73DBB3A9F39468B34A1C157138C9101520F08BD795FC3ED87A25FE408754CC8FF60087C819DAFD91BC6D4CDBA0CCA1D1D7E3045EA6D1A0E1FBD1285F4396F123353";
    n.readHexNum(sn);
    e.readHexNum(se);
    d.readHexNum(sd);
    RSA rsa768(n, e, d);

    sn = "F08D035BB07A47CCFFE0D0CB65B69E9DBDFBC1D22248610ABB9FFF9608F9B7A8C8374A008605C7F25C920620C811655D1DFB878A1FA746E37041241EB75B22F7";
    se = "BBE574A3028D32FF6CC64BDBBF22C9A9F818D25DABD52F1205D57884C3124743";
    sd = "18AA5C3A538525EB44E0B4213A016FDB0ABACA879661B5C6C13AC6684FAB5DEE10D5C5AF720C6BFD6C6B4AF7FCB9C6BF9283BAB84861738C1DA4A92565F6DADB";
    n.readHexNum(sn);
    e.readHexNum(se);
    d.readHexNum(sd);
    RSA rsa512(n, e, d);

    string msg;
    cout << "Please input the origin massage:\n";
    getline(cin, msg);

    int digNum;
    cout << "Please choose the RSA model(512, 768, 1024):\n";
    cin >> digNum;
    if (digNum != 512 && digNum != 768 && digNum != 1024) {
        cout << "model error!\n";
        return;
    }
    
    int m, k;
    OAEP cal;

    clock_t beg = clock();
    if (digNum == 512) {
        m = 500, k = 11;
        StringTrans tran(msg, m);
        vector<BigInt> v = tran.getCode();

        cal.changeMode(k, m);
        vector<BigInt> t;
        for (int i = 0; i < v.size(); i++) {
            t.push_back(cal.oaep_encode(v[i]));
            t[i] = rsa512.encrypt(t[i]);
        }
        cout << "--------------------encode-----------------------\n";
        for (int i = 0; i < t.size(); i++)
            cout << t[i];
        cout << "-------------------------------------------------\n";

        for (int i = 0; i < t.size(); i++) {
            t[i] = rsa512.decrypt(t[i]);
            t[i] = cal.oaep_decode(t[i]);
        }
        string decodeMsg = tran.genMassage(t);
        cout << "--------------------decode-----------------------\n";
        cout << decodeMsg << endl;
        cout << "-------------------------------------------------\n";
    }
    if (digNum == 768) {
        m = 700, k = 67;
        StringTrans tran(msg, m);
        vector<BigInt> v = tran.getCode();

        cal.changeMode(k, m);
        vector<BigInt> t;
        for (int i = 0; i < v.size(); i++) {
            t.push_back(cal.oaep_encode(v[i]));
            t[i] = rsa768.encrypt(t[i]);
        }
        cout << "--------------------encode-----------------------\n";
        for (int i = 0; i < t.size(); i++)
            cout << t[i];
        cout << "-------------------------------------------------\n";

        for (int i = 0; i < t.size(); i++) {
            t[i] = rsa768.decrypt(t[i]);
            t[i] = cal.oaep_decode(t[i]);
        }
        string decodeMsg = tran.genMassage(t);
        cout << "--------------------decode-----------------------\n";
        cout << decodeMsg << endl;
        cout << "-------------------------------------------------\n";
    }
    if (digNum == 1024) {
        m = 900, k = 123;
        StringTrans tran(msg, m);
        vector<BigInt> v = tran.getCode();

        cal.changeMode(k, m);
        vector<BigInt> t;
        for (int i = 0; i < v.size(); i++) {
            t.push_back(cal.oaep_encode(v[i]));
            t[i] = rsa1024.encrypt(t[i]);
        }
        cout << "--------------------encode-----------------------\n";
        for (int i = 0; i < t.size(); i++)
            cout << t[i];
        cout << "-------------------------------------------------\n";

        for (int i = 0; i < t.size(); i++) {
            t[i] = rsa1024.decrypt(t[i]);
            t[i] = cal.oaep_decode(t[i]);
        }
        string decodeMsg = tran.genMassage(t);
        cout << "--------------------decode-----------------------\n";
        cout << decodeMsg << endl;
        cout << "-------------------------------------------------\n";
    }

    clock_t cur = clock();
    printf("Time used: %.4lfs\n", (double)(cur - beg) / CLOCKS_PER_SEC);
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
