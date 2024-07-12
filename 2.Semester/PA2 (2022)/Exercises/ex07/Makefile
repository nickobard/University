CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic
LDFLAGS =

# PROGT

progt: assets/progt.sh
	assets/progt.sh ./assets/src.cpp ./

ptrun: progtest
	./progtest

progtest: progtest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# PROJECT RUN

all: compile

compile: main

run: main
	./main

vgr: main
	valgrind ./main

# PROJECT SANITIZER

fsall: CXXFLAGS += -fsanitize=address
fsall: LDFLAGS  += -fsanitize=address
fsall: all

fsrun: CXXFLAGS += -fsanitize=address
fsrun: LDFLAGS  += -fsanitize=address
fsrun: main
	./main

# PROJECT DEPENDENCIES

main: main.o CEFaceMask.o CContact.o CTimeStamp.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: main.cpp CEFaceMask.h TTester.h CTimeStamp.h CContact.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
CEFaceMask.o: CEFaceMask.cpp CEFaceMask.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
CContact.o: CContact.cpp CContact.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
CTimeStamp.o: CTimeStamp.cpp CTimeStamp.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

clear: cl

cl:
	-rm -f a.out
	-rm -f *.o
	-rm -f main

clpt:
	-rm -f progtest.cpp
	-rm -f progtest

clall: cl clpt

	
