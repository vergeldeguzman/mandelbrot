CXX=g++
INC=-Isrc
CXXFLAGS=-std=c++14 -g -Wall -Werror $(INC)

SRCDIR=src
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(patsubst $(SRCDIR)/%.cpp, $(SRCDIR)/%.o, $(SRC))

TESTDIR=test
TESTSRC=$(wildcard $(TESTDIR)/*.cpp)
TESTOBJ=$(patsubst $(TESTDIR)/%.cpp, $(TESTDIR)/%.o, $(TESTSRC))

all: RunMandelbrot test

$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -Igtest_src -c -o $@ $<

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

RunMandelbrot: $(OBJ)
	$(CXX) -o $@ $^

gtest_src/gtest/gtest-all.o: gtest_src/gtest/gtest-all.cc
	$(CXX) $(CXXFLAGS) -Igtest_src -c -o $@ $<

.PHONY: clean test

test: $(TESTOBJ) $(filter-out $(SRCDIR)/RunMandelbrot.o,$(OBJ)) gtest_src/gtest/gtest-all.o
	$(CXX) -o $(TESTDIR)/runTests $^ -lpthread
	$(TESTDIR)/runTests

clean:
	rm -f RunMandelbrot runTests $(SRCDIR)/*.o $(TESTDIR)/*.o gtest_src/gtest/gtest-all.o *~ core
