# c++ -c options says to compile, but not link yet
# c++ -o option  says make compiled file with specified name
CXX = g++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic
# LDFLAGS - used are used for the linker.
# ld - is the GNU linker command.
LDFLAGS =

# DOXYGEN MAKE
doxinit:
	doxygen -g
doxupdate:
	doxygen -u doc/Doxyfile
doxygen:
	doxygen doc/Doxyfile 1>/dev/null 2>/dev/null
doxpdf:
	make -C doc/latex 1>/dev/null 2>/dev/null
	rm -f doc/*.pdf
	cp doc/latex/refman.pdf doc/CFile.pdf
doxall: doxygen doxpdf

doxclean: 
	rm -rdf doc/latex
	rm -rdf doc/html
	rm -rdf doc/*.pdf

# PROG TINKER MAKE
progt: assets/progt.sh 
	assets/progt.sh ./assets/src.cpp  ./

ptrun: progtest
	./progtest

ptfs: CXXFLAGS += -fsanitize=address
ptfs: progtest
	./progtest

progtest.cpp: progt

progtest: progtest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# PROJECT MAKE
all: compile

compile: main 

fs: CXXFLAGS += -fsanitize=address
fs: LDFLAGS  += -fsanitize=address
fs: all

frun: CXXFLAGS += -fsanitize=address
frun: LDFLAGS  += -fsanitize=address
frun: main
	./main

vgr: main
	valgrind ./main

run: main
	./main
# $@ option takes the name of the file to be made,
# in this case it is `main` - what is befoire `:`
main: main.o CFile.o CVector.o CStack.o | Makefile.d
	$(CXX) $^ -o $@ $(LDFLAGS)

# $*.cpp takes all dependencies with postfix .cpp
# alternative is to us $<, that also works
# main.o: main.cpp CFile.h CStack.h CVector.h TFile.h TTester.h CSharedPtr.h \
# 				CSharedPtr.inl
# 	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
# # we can use $? to use names of the changed dependends
# # here it will be CLinkedSet.cpp, as well CLinkedSet.h etc,
# # which is a problem.
# # Solution like $@.cpp doesn't work, becuase it will be
# # CLinkedSet.o.cpp, which is wrong name.
# CFile.o: CFile.cpp CFile.h CStack.h CVector.h TFile.h
# 	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
# CVector.o: CVector.cpp CVector.h
# 	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
# CStack.o: CStack.cpp CStack.h TFile.h
# 	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

deps: Makefile.d

Makefile.d: *.cpp *.h *.inl
	$(CXX) -MM *.cpp > $@

cl:
	-rm -f a.out
	-rm -f *.o
	-rm -f main
clpt:
	-rm -f progtest.cpp
	-rm -f progtest
clall: cl clpt

-include Makefile.d