OBJS = BigInt.o Key.o OAEP.o PrimeGen.o RSA.o StringTrans.o
CFLAGS = -c -Iinclude

all: libRSA.a

libRSA.a: $(OBJS)
	ar crv $@ $^
	
%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@
	
BigInt.o: BigInt.cpp include/BigInt.h include/globalData.h

Key.o: Key.cpp include/Key.h include/BigInt.h include/PrimeGen.h include/globalData.h

OAEP.o: OAEP.cpp include/OAEP.h include/BigInt.h include/Key.h

PrimeGen.o: PrimeGen.cpp include/PrimeGen.h include/BigInt.h

RSA.o: RSA.cpp include/RSA.h include/Key.h 

StringTrans.o: StringTrans.cpp include/StringTrans.h include/OAEP.h include/RSA.h include/BigInt.h

clean:
	rm -f $(OBJS) libRSA.so
