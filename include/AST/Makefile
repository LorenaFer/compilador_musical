CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I.

AST_SOURCES = ast_node_interface.cpp datatype.cpp declaration.cpp expression.cpp statement.cpp
AST_OBJECTS = $(AST_SOURCES:.cpp=.o)

DEMO_SOURCE = demo_c_function.cpp
DEMO_OBJECT = $(DEMO_SOURCE:.cpp=.o)

DEMO_EXECUTABLE = demo_music_ast

.PHONY: all clean

all: $(DEMO_EXECUTABLE)

$(DEMO_EXECUTABLE): $(AST_OBJECTS) $(DEMO_OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ast_node_interface.o: ast_node_interface.cpp ast_node_interface.hpp
datatype.o: datatype.cpp datatype.hpp ast_node_interface.hpp
declaration.o: declaration.cpp declaration.hpp ast_node_interface.hpp datatype.hpp expression.hpp
expression.o: expression.cpp expression.hpp ast_node_interface.hpp
statement.o: statement.cpp statement.hpp ast_node_interface.hpp declaration.hpp expression.hpp
demo_c_function.o: $(DEMO_SOURCE) ast_node_interface.hpp datatype.hpp declaration.hpp expression.hpp statement.hpp

clean:
	rm -f $(AST_OBJECTS) $(DEMO_OBJECT) $(DEMO_EXECUTABLE)

run: $(DEMO_EXECUTABLE)
	./$(DEMO_EXECUTABLE) 