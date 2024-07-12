# c++ -c options says to compile, but not link yet
# c++ -o option  says make compiled file with specified name
CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic
# LDFLAGS - used are used for the linker.
# ld - is the GNU linker command.
LDFLAGS =

doxinit:
	doxygen -g
doxup:
	doxygen -u doc/Doxyfile
doxgen:
	doxygen doc/Doxyfile

all: compile

compile: main

fs: CXXFLAGS += -fsanitize=address
fs: all

vgr: main
	valgrind ./main

run: main
	./main

progt: assets/progt.sh
	assets/progt.sh

ptrun: progtest
	./progtest

ptfs: CXXFLAGS += -fsanitize=address
ptfs: progtest
	./progtest

progtest.cpp: progt

progtest: progtest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
# $@ option takes the name of the file to be made,
# in this case it is `main` - what is befoire `:`
main: main.o CLinkedSet.o
	$(CXX) $^ -o $@ $(LDFLAGS)

# $*.cpp takes all dependencies with postfix .cpp
# alternative is to us $<, that also works
main.o: main.cpp TLinkedSetTester.h CLinkedSet.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
# we can use $? to use names of the changed dependends
# here it will be CLinkedSet.cpp, as well CLinkedSet.h etc,
# which is a problem.
# Solution like $@.cpp doesn't work, becuase it will be
# CLinkedSet.o.cpp, which is wrong name.
CLinkedSet.o: CLinkedSet.cpp CLinkedSet.h CLinkedSetTester.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

cl:
	-rm -f *.o
	-rm -f main
clpt:
	-rm -f progtest
	-rm -f progtest.cpp
