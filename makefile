CFLAGS = -c -Iinclude

all: simplersa

simplersa: main.o
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $^ -o $@

main.o: main.cpp 

clean:
	rm -f simplersa main.o
