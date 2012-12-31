SimpleRSA
=========

A simple version of RSA algorithm implementation.

> No voice, but big deal.

## Requirement
Write a Java or C program that demostrates RSA encryption and decryption algorithm.
* The program should support 512, 768, 1024 and 2048 bits key size.
* You are free to use any C++ package or Java class to handle big integers.
* We adapt the convention that Bob is the party who will announce the public keys and Alice the one who will send Bob message encrypted with the public keys.
* You can refer to RSA-Tool and the following interface, and you are encouraged to implement RSA-OAEP(RFC 3447 or PKCS #1 V2.1) or other special functions to demonstrate your work.
* Please include comments in your code, the test files and the sample output.

## Algorithm Analysis

### RSA algorithm
* 数据生成过程
> (n,e)为公钥，(n,d)为私钥，要求n的二进制长度分别为512，768，1024和2048(bits)
```
step.1. 找出两个大素数p和q
step.2. 计算 n = p * q, t = (p - 1) * (q - 1)
step.3. 任取一个数e，要求满足e < t并且e与t互素
step.4. 计算d (d < t)，满足d * e % t == 1
```
* 加密解密过程
```
step.1. 将信息流分段，每段可一一映射到一个数M(M < n)
step.2. 计算 c = (M^d) % n, c作为密文发送
step.3. 计算 m = (c^e) % n, 则 m == M，从而完成对c的解密
step.4. 将m重新整合，还原信息流并显示
```
详细描述可以参考[这里](http://zh.wikipedia.org/wiki/RSA%E5%8A%A0%E5%AF%86%E6%BC%94%E7%AE%97%E6%B3%95)
### OAEP（最优非对称加密填充）
> 在RSA加密前进行OAEP过程
> M: 填充信息(m-bit)，P：明文（P1 || P2）(m+k bits)，C：密文(m+k bits)
> r: 一次性随机数(k-bit)，G(x)：公共函数(k-bit to m-bit)，H(x)：公共函数(m-bit to k-bit)
* 加密过程
```
step.1. 生成一个k-bit的随机数r
step.2. 运算生成明文 P1 = M ^ G(r)
step.3. 计算明文的第二部分 P2 = H(P1) ^ r
step.4. 合成出明文P，并用RSA加密，得密文C
```
* 解密过程
```
step.1. 利用RSA，解密C，得明文P，并按m+k bits分段成(P1 || P2)
step.2. 作运算 H(P1) ^ P2 = H(P1) ^ (H(P1) ^ r) = r，还原出随机数r
step.3. 作运算 G(r) ^ P1 = G(r) ^ (M ^ G(r)) = M，还原出信息流，并显示
```
详细信息可以参考[这里](http://book.51cto.com/art/200901/105944.htm)
