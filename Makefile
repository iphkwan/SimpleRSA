CFLAGS = -c -Iinclude

all: simplersa 

src/libRSA.a: src/Makefile
	cd src/ && make
	
main.o: main.cpp src/include/*
	$(CXX) $(CFLAGS) $< -o $@
	
simplersa: main.o src/libRSA.a
	$(CXX) $^ -o $@
	
lib: src/Makefile
	cd src/ && make

clean:
	rm -f simplersa main.o
