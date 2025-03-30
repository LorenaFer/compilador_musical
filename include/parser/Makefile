# Compilador y flags
CC = g++
CFLAGS = -g -Wall -std=c++17

# Nombres de los archivos generados
PARSER = parser.tab.c
PARSER_HEADER = parser.tab.h
SCANNER = lex.yy.c

# Rutas
TEST_DIR = ../../test/parser

# Target por defecto
all: parser

# Compilación del parser
$(PARSER) $(PARSER_HEADER): parser.bison
	bison -d -o $(PARSER) parser.bison

# Compilación del scanner
$(SCANNER): scanner.flex $(PARSER_HEADER)
	flex -o $(SCANNER) scanner.flex

# Compilación del programa principal
parser: $(SCANNER) $(PARSER) expression.cpp main.cpp
	$(CC) $(CFLAGS) -o parser $(SCANNER) $(PARSER) expression.cpp main.cpp

# Limpieza
clean:
	rm -f parser $(SCANNER) $(PARSER) $(PARSER_HEADER) *.o
	rm -rf parser.dSYM

# Ejecución de pruebas simple
test: parser
	./parser $(TEST_DIR)/code.mus

# Ejecutar todas las pruebas
test_all: test_valid test_invalid

# Ejecutar todas las pruebas válidas
test_valid: parser
	@echo "\n\n======= CASOS VÁLIDOS =======\n"
	@for file in $(TEST_DIR)/valid_*; do \
		echo "\n----- Probando: $${file} -----"; \
		./parser $${file} || echo "❌ Error al procesar $${file}"; \
	done

# Ejecutar todas las pruebas inválidas
test_invalid: parser
	@echo "\n\n======= CASOS INVÁLIDOS =======\n"
	@for file in $(TEST_DIR)/invalid_*; do \
		echo "\n----- Probando: $${file} -----"; \
		result=`./parser $${file} 2>&1`; \
		if [ $$? -eq 0 ]; then \
			echo "❌ Error: $${file} debería fallar pero pasó"; \
		else \
			echo "✅ Test de invalidez exitoso"; \
		fi; \
	done

.PHONY: all clean test test_all test_valid test_invalid 