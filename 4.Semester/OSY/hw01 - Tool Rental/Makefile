CXX=g++
LD=g++
AR=ar
CXXFLAGS=-std=c++17 -Wall -pedantic
SHELL:=/bin/bash
MACHINE=$(shell uname -m)-$(shell echo $$OSTYPE)

release: CXXFLAGS += -O2
release: test

sanitizer: CXXFlAGS += -fsanitize=address
sanitizer: LD += -fsanitize=address
sanitizer: test

all: CXXFLAGS += -ggdb
all: test

deps:
	g++ -MM *.cpp > Makefile.d

pt_all: pt_compile

pt_tinker:
	./src/assets/progt.sh ./src/assets/solution.cpp ./src

pt_compile: progtest.o sample_tester.o
	$(LD) $(CXXFLAGS) -o $@ $^ -L./$(MACHINE) -lprogtest_solver -lpthread

test: solution.o sample_tester.o COptimizer.o WorkerStation.o CompanyAgent.o ProblemPackWrapper.o Worker.o Deliverer.o Loader.o SolverManager.o
	$(LD) $(CXXFLAGS) -o $@ $^ -L./$(MACHINE) -lprogtest_solver -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

COptimizer.o: src/COptimizer.cpp src/COptimizer.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

WorkerStation.o: src/WorkerStation.cpp src/WorkerStation.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

CompanyAgent.o: src/CompanyAgent.cpp src/CompanyAgent.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ProblemPackWrapper.o: src/ProblemPackWrapper.cpp src/ProblemPackWrapper.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Worker.o: src/Worker.cpp src/Worker.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Loader.o: src/Loader.cpp src/Loader.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


Deliverer.o: src/Deliverer.cpp src/Deliverer.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


SolverManager.o: src/SolverManager.cpp src/SolverManager.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


lib: progtest_solver.o
	mkdir -p $(MACHINE)
	$(AR) cfr $(MACHINE)/libprogtest_solver.a $^

clean:
	rm -f *.o test *~ core sample.tgz Makefile.d
	rm -f progtest.cpp
	rm -f pt_compile
	
pack: clean
	rm -f sample.tgz
	tar zcf sample.tgz --exclude progtest_solver.cpp --exclude Makefile.mingw *
	

debug_aliases:
	alias psdebug='ps -Lo s,pid,lwp,nlwp,comm'





-include Makefile.d
