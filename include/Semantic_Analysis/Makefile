# Makefile para el módulo de análisis semántico del compilador musical

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -I.
LDFLAGS = 

# Archivos objeto
OBJS = ast_node_interface.o \
       datatype.o \
       declaration.o \
       expression.o \
       statement.o \
       symbol_table.o \
       demo_program.o

# Nombre del ejecutable
TARGET = musical_semantic_analyzer

# Regla principal
all: $(TARGET)

# Enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Reglas para archivos objeto individuales
ast_node_interface.o: ast_node_interface.cpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

datatype.o: datatype.cpp datatype.hpp ast_node_interface.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

declaration.o: declaration.cpp declaration.hpp ast_node_interface.hpp datatype.hpp expression.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

expression.o: expression.cpp expression.hpp ast_node_interface.hpp datatype.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

statement.o: statement.cpp statement.hpp ast_node_interface.hpp declaration.hpp expression.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

symbol_table.o: symbol_table.cpp symbol_table.hpp datatype.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

demo_program.o: demo_program.cpp datatype.hpp declaration.hpp expression.hpp statement.hpp symbol_table.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Ejecutar el análisis semántico de prueba
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para recompilar todo
rebuild: clean all

.PHONY: all clean rebuild run 