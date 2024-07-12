CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic
LDFLAGS =

# PROJECT RUN

all: compile

compile: main

run: main
	./main

vgr: main
	valgrind ./main

# PROJECT DEPENDENCIES

main: main.o CSupermarket.o CDate.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: main.cpp TTester.h CSupermarket.h CDate.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

CDate.o: CDate.cpp CDate.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

CSupermarket.o: CSupermarket.cpp CSupermarket.h CDate.h
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

clear: cl

cl:
	-rm -f a.out
	-rm -f *.o
	-rm -f main

ptcl:
	-rm -f progtest.cpp
	-rm -f progtest

clall: cl clpt

# PROJECT SANITIZER

fsall: CXXFLAGS += -fsanitize=address
fsall: LDFLAGS  += -fsanitize=address
fsall: all

fsrun: CXXFLAGS += -fsanitize=address
fsrun: LDFLAGS  += -fsanitize=address
fsrun: main
	./main

# PROGT

progt: assets/progt.sh
	assets/progt.sh ./assets/src.cpp ./

ptrun: progtest
	./progtest

ptvgr: progtest
	valgrind ./progtest

fsptrun: CXXFLAGS += -fsanitize=address
fsptrun: progtest
	./progtest

progtest: progtest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
	
# DOXYGEN

# Dunno, but &>/dev/null doesn't work
dox:
	doxygen doc/Doxyfile 1>/dev/null 2>/dev/null

doxpdf:
	make -C doc/latex 1>/dev/null 2>/dev/null
	-rm -f doc/refman.pdf
	cp doc/latex/refman.pdf doc/

doxall: dox doxpdf

doxclean:
	-rm -rdf doc/latex
	-rm -rdf doc/html
	-rm -rdf doc/refman.pdf