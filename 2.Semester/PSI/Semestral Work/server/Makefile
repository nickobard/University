CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic

all: compile

compile: server

vgr: server	
	valgrind ./server

fs: CXXFLAGS += -fsanitize=address
fs: LDFLAGS += -fsanitize=address
fs: compile

frun: CXXFLAGS += -fsanitize=address
frun: LDFLAGS += -fsanitize=address
frun: server
	./server 3999

run: server
	./server 3999

server: server.o CServer.o CClientConn.o CClientConnRobot.o
	$(CXX) $^ -o $@ $(LDFLAGS)

server.o: server.cpp CServer.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
CServer.o: CServer.cpp CServer.h CClientConn.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
CClientConn.o: CClientConn.cpp CClientConn.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
CClientConnRobot.o: CClientConnRobot.cpp CClientConn.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

cl:
	-rm -f a.out
	-rm -f *.o
	-rm -f server
	-rm -f main