#include "PrimeGen.h"
#include "BigInt.h"
#include "utils.h"

//产生一个待测素数,保证此数为奇数,且不能被小于5000的素数整除
void GenPrime(BigInt& n, int digNum)
{
    cout << "产生一个待测素数" << endl;
    int i = 0;
    BigInt divisor;
    const int length = sizeof(prime) / sizeof(int);
    while (i != length)
    {
	    n.Random(digNum);
	    while (!n.IsOdd())
	        n.Random(digNum);
	    i = 0;
	    for ( ; i < length; i++)
	    {
	        divisor = prime[i];
	        if ((n % divisor) == 0)
		        break;
	    }
    }
    cout << "test_prime = " << n << endl;
}

bool RobinMiller(const BigInt& n, int digNum)
{
    BigInt r, a, y;
    unsigned int s, j;
    r = n - 1;
    s = 0;

    //找到令N-1=2^S*R的S和R,R为奇数
    while (!r.IsOdd())
    {
	    s++;
	    r >> 1;
    }

    //产生一个小于N-1的检测随机数
    a.Randomsmall(digNum);

    y = BigInt::PowerMode(a, r, n);

    //检测J=2至J<S轮
    if((!(y == 1)) && (!(y == (n - 1))))
    {
	    j = 1;
	    while ((j <= s - 1) && (!(y == (n - 1))))
	    {
	        y = (y * y) % n;
	        if (y == 1)
		        return false;
	        j++;
	    }
	    if (!(y == (n - 1)))
	        return false;
    }
    return true;
}

//产生一个素数
BigInt GeneratePrime(int digNum)
{
    BigInt n;
    int i = 0;
    while (i < 5)
    {
	    //产生一个待测素数
	    GenPrime(n, digNum);
	    i = 0;
	    //进行五轮ROBINMILLER测试,五轮全部通过则素数合格
	    //理论素数合格率达99.9%
	    for ( ; i < 5; i++)
	    {
	        cout << "进行第" << i + 1 << "轮RobinMiller测试" << endl;
	        if (!RobinMiller(n, digNum))
	        {
		        cout << "测试失败!"<< endl;
		        cout << endl;
		        break;
	        }
	    }
    }
    return n;
}
