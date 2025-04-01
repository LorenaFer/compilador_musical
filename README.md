# Compilador de Música

Este proyecto implementa un compilador que traduce un lenguaje de dominio específico (DSL) para notación musical a una representación estructurada mediante un Árbol de Sintaxis Abstracta (AST).

## Estructura del Proyecto

```
.
├── scanner/            # Versión 1 (antigua) del analizador léxico (solo informativo)
├── parser/             # Scanner actualizado (v4) con funcionalidades nuevas
│   ├── *.bison         # Gramática formalizada del lenguaje musical 
│   └── expression.c    # Archivos que separan la lógica del analizador sintáctico
├── include/            # Archivos de cabecera e implementación
│   └── AST/            # Implementación del Árbol de Sintaxis Abstracta
│       ├── ast_node_interface.hpp  # Interfaz base para todos los nodos del AST
│       ├── declaration.hpp/cpp     # Implementa declaraciones (tempo, compás, etc.)
│       ├── expression.hpp/cpp      # Implementa expresiones (alteraciones, etc.)
│       ├── statement.hpp/cpp       # Implementa sentencias
│       └── datatype.hpp/cpp        # Define los tipos de datos musicales
└── test/               # Archivos de prueba y ejemplos del lenguaje musical (.mus)
    └── parser/         # Ejemplos específicos para probar el analizador sintáctico
```

## Definiciones Musicales
¿Qué es una tonalidad?

La tonalidad establece un "centro de gravedad" musical, una nota principal llamada tónica. Todas las demás notas y acordes de la canción se relacionan con esta tónica, creando una sensación de cohesión y unidad.

Marco armónico:
Define qué notas "suenan bien" juntos en una canción. La tonalidad establece una escala, una secuencia específica de notas, que sirve como base para la melodía y la armonía.

¿Qué hacen las alteraciones?

Las alteraciones permiten a los músicos tocar notas que no están en la escala diatónica básica
Hacen que una nota sea más aguda (más alta) o más grave (más baja)

Tipos principales de alteraciones:

Sostenido (#):
Eleva la altura de una nota en un semitono.
Por ejemplo, Do# es un semitono más alto que Do.
Bemol (b):
Reduce la altura de una nota en un semitono.
Por ejemplo, Reb es un semitono más bajo que Re.

## Compilación y Ejecución

### Compilación
Para compilar el proyecto, utilice el Makefile en la raíz:

Esto generará el ejecutable principal en la carpeta `bin/`.

### Ejecución
Para ejecutar el parser ubicarse en include/parser:

```bash
make all
make test_all
```

Para ver la representación del AST generado, ubicarse en include/AST:

```bash
make all
make run
```

### Ejemplos
La carpeta `/test/parser/` contiene varios ejemplos que muestran diferentes características del lenguaje musical:


## Sintaxis del Lenguaje Musical
```
// Estructura general del lenguaje

Estandares denifidos
tempo 120
compas 4/4

// - Palabras reservadas - 

Tonalidad
Tempo 
Compas
M = Mayor -> 0
m = menor -> 1
# : Sostenido -> +1/2
♭ -> b : Bemol -> -1/2

// Notas musicales
Do  -> C
Re  -> D
Mi  -> E
Fa  -> F
Sol -> G
La  -> A
Si  -> B

// Duracion

Figura                    Midi
______________________________
Blanca       ->  1/2   -> 960
Negra        ->  1/4   -> 480
Corchea      ->  1/8   -> 240
Semicorchea  ->  1/16  -> 120

//Notas y Duraciones
Cada nota se escribe con su letra asignada correspondiente (C, D, E), su octava (4 , 5) y su duracion (Negra, blanca, corchea).
```

## Ejemplos de Uso

### Ejemplo 1: Notas Básicas y Alteraciones
```mus
// Configuración inicial del compás
Tempo 120
Compas 4/4

// Definición de tonalidad
Tonalidad Do M

// Secuencia de notas con diferentes duraciones
Do4 Negra
Re4 Corchea
Mi4 Blanca
Fa4 Semicorchea
Sol4 Negra
La4 Corchea
Si4 Blanca

// Notas con alteraciones
Do#4 Negra
Reb4 Corchea
Mi♭4 Blanca

// Usando notación alternativa (inglesa)
C4 Negra
D4 Corchea
E4 Blanca
F#4 Negra
Gb4 Corchea 
```

### Ejemplo 2: Compases y Tonalidades
```mus
// Prueba de diferentes compases y tempos
Tempo 80
Compas 3/4

// Cambio de tonalidad a menor
Tonalidad La m

// Secuencia rápida de semicorcheas
Do4 Semicorchea
Re4 Semicorchea
Mi4 Semicorchea
Fa4 Semicorchea
Sol4 Semicorchea
La4 Semicorchea
Si4 Semicorchea
Do5 Semicorchea

// Mezcla de duraciones
Do4 Blanca
Re4 Negra
Mi4 Corchea
Fa4 Semicorchea

// Prueba de alteraciones consecutivas
Do#4 Negra
Do#4 Corchea
Reb4 Negra
Mib4 Blanca
Fa#4 Corchea
Sol♭4 Semicorchea

// Mezcla de notación latina e inglesa
Do4 Negra
D4 Negra
Mi4 Negra
F4 Negra
Sol4 Negra
A4 Negra
Si4 Negra 
```

## Arquitectura del Compilador

El compilador se organiza en tres componentes principales:

1. **Analizador Léxico (Scanner)**: Convierte el texto de entrada en tokens.
   - La versión actual (v4) está en la carpeta `/parser/`
   - La versión antigua (v1) se mantiene en `/scanner/` solo con fines informativos

2. **Analizador Sintáctico (Parser)**: Procesa los tokens y construye el AST.
   - Utiliza Bison para definir la gramática formal
   - La lógica de procesamiento está separada en archivos como `expression.c`

3. **Árbol de Sintaxis Abstracta (AST)**: Representa la estructura del programa musical.
   - Implementado en la carpeta `/include/AST/`
   - Permite la representación estructurada de la composición musical

## Equipo
- Lorena Fernandez
- Julio Vasquez