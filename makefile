CFLAGS = -c -Isrc/include

all: simplersa 

src/libRSA.a: src/Makefile
	cd src/ && make

simplersa: main.o src/libRSA.a
	$(CXX) $^  -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $^ -o $@

main.o: main.cpp 

clean:
	rm -f simplersa
