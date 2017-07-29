# C++ Compilation properties
CXX=g++
CFLAGS=-Wall -g -pedantic -std=c++11 -pthread
COMPILE=$(CXX) $(CFLAGS)

# What to compile
INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
TESTS=$(patsubst %.cpp,%.o,$(notdir $(wildcard test/*.cpp)))

# The executable file name
BIN=bin/dns

# GoogleTest linkage includes
GTEST=-lgtest -lgtest_main -lpthread

.PHONY: all compile run tests clean
# Compile and run the server
all: compile run

# Compile the server
compile: $(SOURCES)
	$(COMPILE) $(INCLUDE) $(SOURCES) main.cpp -o $(BIN)

run:
	$(BIN)

# Run the tests
tests: $(TESTS)
	$(addprefix bin/,$(TESTS))

# Compile the tests
%.o: test/%.cpp
	$(COMPILE) $(INCLUDE) $(SOURCES) $< $(GTEST) -o bin/$@

clean:
	rm -rf bin/*
