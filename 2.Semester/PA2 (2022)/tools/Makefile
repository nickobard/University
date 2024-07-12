CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic
LD = g++
LDFLAGS =

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
INLINES = $(wildcard *.inl)
	
OBJS = $(SOURCES:.cpp=.o)

EXEFILE = test

# PROJECT RUN

all: compile

compile: $(EXEFILE)

run: $(EXEFILE)
	./$(EXEFILE)

vgr: $(EXEFILE)
	valgrind ./$(EXEFILE)

# PROJECT DEPENDENCIES

deps: Makefile.d

Makefile.d: $(SOURCES) $(HEADERS) $(INLINES)
	g++ -MM $(SOURCES) > Makefile.d

include Makefile.d

# COMPILING

$(EXEFILE): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# CLEANING

clean: cl

cl:
	-rm -f a.out
	-rm -f *.o
	-rm -f $(EXEFILE)

#======================OWN TARGETS=======================

clpt:
	-rm -f ./assets/progtest.cpp
	-rm -f ./assets/progtest
	-rm -f ./progtest.cpp
	-rm -f ./progtest

clall: cl clpt


# PROJECT SANITIZER

fsall: CXXFLAGS += -fsanitize=address
fsall: LDFLAGS  += -fsanitize=address
fsall: all

fsrun: CXXFLAGS += -fsanitize=address
fsrun: LDFLAGS  += -fsanitize=address
fsrun: $(EXEFILE)
	./$(EXEFILE)

# PROGT

progt: assets/progt.sh
	assets/progt.sh ./assets/src.cpp ./
	mv progtest.cpp ./assets

ptrun: assets/progtest
	./assets/progtest

ptvgr: progtest
	valgrind ./assets/progtest

fsptrun: CXXFLAGS += -fsanitize=address
fsptrun: progtest
	./assets/progtest

progtest: ./assets/progtest.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	mv $@ ./assets/
	
# DOXYGEN

# Dunno, but &>/dev/null doesn't work
dox: 
	doxygen doc/Doxyfile 1>/dev/null 2>/dev/null

doxpdf:
	make -C doc/latex 1>/dev/null 2>/dev/null
	-rm -f doc/refman.pdf
	-rm cp doc/latex/refman.pdf doc/

doxall: doc docpdf

doxclean:
	-rm -rdf doc/latex
	-rm -rdf doc/html
	-rm -rdf doc/refman.pdf

# NDEBUG AND OPTIMIZATIONS

nd_cmpl: CXXFLAGS += -D NDEBUG
nd_cmpl: compile

ndo_cmpl: CXXFLAGS = g++ -std=c++17 -Wall -pedantic -O3 -D NDEBUG
ndo_cmpl: compile
