CXX = g++
FLEX = flex
INCLUDE_DIR = ../
CXXFLAGS = -I$(INCLUDE_DIR)

all: scanner_test

# Generar token.h desde el parser
token.h:
	cd ../parser && $(MAKE) token.h
	cp ../parser/token.h .

scanner.c: scanner.flex token.h
	$(FLEX) -o scanner.c scanner.flex

scanner.o: scanner.c
	$(CXX) $(CXXFLAGS) -c scanner.c

main.o: main.c token.h
	$(CXX) $(CXXFLAGS) -c main.c

scanner_test: main.o scanner.o
	$(CXX) main.o scanner.o -o scanner_test

.PHONY: clean test
clean:
	$(RM) *.o scanner.c token.h scanner_test

test: scanner_test
	./scanner_test ../../test/parser/code.mus 