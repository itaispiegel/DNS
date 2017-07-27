CXX=g++
CFLAGS=-Wall -g -pedantic -std=c++11 -pthread
COMPILE=$(CXX) $(CFLAGS)

INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
TESTS=message_tests.o

BIN=bin/dns

GTEST=-lgtest -lgtest_main -lpthread

all: compile tests

compile:
	$(COMPILE) $(INCLUDE) $(SOURCES) main.cpp -o $(BIN)

tests: $(TESTS)
	bin/message_tests.o

%.o: test/%.cpp
	$(COMPILE) $(INCLUDE) $(SOURCES) $< $(GTEST) -o bin/$@

clean:
	rm -rf bin/*
