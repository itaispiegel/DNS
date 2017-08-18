# C++ Compilation properties
CXX=g++
CFLAGS=-Wall -pedantic -std=c++11 -pthread
COMPILE=$(CXX) $(CFLAGS)

# What to compile
INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
TESTS=$(patsubst %.cpp,%.o,$(notdir $(wildcard test/*.cpp)))

# The executable file name
BIN=bin/dns

# GoogleTest linkage includes
GTEST=-lgtest -lgtest_main -lpthread

.PHONY: all install-dependencies compile run tests clean
all: compile run

debug: CFLAGS += -DDEBUG -g
debug: compile
	gdb $(BIN)

install-dependencies:
	sudo yum install -y gtest-devel

compile: $(SOURCES)
	$(COMPILE) $(INCLUDE) $(SOURCES) main.cpp -o $(BIN)

run:
	@$(BIN)

tests: $(TESTS)
	$(addprefix bin/,$(TESTS))

%.o: test/%.cpp
	$(COMPILE) $(INCLUDE) $(SOURCES) $< $(GTEST) -o bin/$@

clean:
	rm -rf bin/*
