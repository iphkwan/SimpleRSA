all:
	g++ main.cpp BigInt.h Key.h PrimeGen.h RSA.h OAEP.h -o a.out
clean:
	rm a.out
