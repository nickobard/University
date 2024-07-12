CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic

all: compile

compile: client

vgr: client	
	valgrind ./client

fs: CXXFLAGS += -fsanitize=address
fs: LDFLAGS += -fsanitize=address
fs: compile

frun: CXXFLAGS += -fsanitize=address
frun: LDFLAGS += -fsanitize=address
frun: client
	./client localhost 3999

run: client
	./client localhost 3999

client: client.o
	$(CXX) $^ -o $@ $(LDFLAGS)

client.o: client.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

cl:
	-rm -f a.out
	-rm -f *.o
	-rm -f client
	-rm -f main