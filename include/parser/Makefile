CXX = g++
FLEX = flex
BISON = bison --defines=token.h
INCLUDE_DIR = ../
SCANNER_DIR = ../scanner
CXXFLAGS = -I$(INCLUDE_DIR)

all: music_parser

music_parser: parser.o scanner.o main.o
	$(CXX) scanner.o parser.o main.o -o music_parser

parser.o: parser.c
	$(CXX) $(CXXFLAGS) -c parser.c

parser.c: parser.bison
	$(BISON) -v --output parser.c parser.bison

token.h: parser.bison
	$(BISON) --defines=token.h --output=parser.c parser.bison

scanner.c: $(SCANNER_DIR)/scanner.flex token.h
	cp $(SCANNER_DIR)/scanner.flex .
	$(FLEX) -o scanner.c scanner.flex
	rm scanner.flex

scanner.o: token.h scanner.c
	$(CXX) $(CXXFLAGS) -c scanner.c

main.o: token.h main.c
	$(CXX) $(CXXFLAGS) -c main.c

.PHONY: clean test
clean:
	$(RM) *.o parser.c parser.output token.h scanner.c music_parser scanner.flex

test: music_parser
	./music_parser ../../test/parser/code.mus 