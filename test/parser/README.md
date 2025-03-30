# Casos de Prueba para el Parser Musical

Este directorio contiene casos de prueba para verificar el funcionamiento del parser musical.

## Casos Válidos

Los siguientes archivos deberían ser procesados correctamente por el parser:

1. `valid_01_basic.mus`: Configuración básica con notas simples sin alteraciones.
2. `valid_02_alterations.mus`: Notas con alteraciones (sostenidos y bemoles).
3. `valid_03_different_octaves.mus`: Notas en diferentes octavas (graves, medias y agudas).
4. `valid_04_minor_key.mus`: Uso de tonalidad menor con progresiones típicas.
5. `valid_05_complex_time_signature.mus`: Compás complejo (7/8) con patrones rítmicos diversos.

## Casos Inválidos

Los siguientes archivos contienen errores que deberían ser detectados por el parser:

1. `invalid_01_missing_tempo.mus`: Falta la configuración obligatoria de tempo.
2. `invalid_02_negative_tempo.mus`: Tempo con valor negativo (debe ser positivo).
3. `invalid_03_zero_denominator.mus`: Denominador del compás igual a cero (debe ser positivo).
4. `invalid_04_missing_tonality.mus`: Falta la configuración obligatoria de tonalidad.
5. `invalid_05_syntax_error.mus`: Diversos errores de sintaxis en las notas.

## Ejecución

Para probar estos archivos, utilice el comando:

```bash
cd include/parser
make test
```

Para probar un archivo específico:

```bash
cd include/parser
./parser_test ../../test/parser/nombre_archivo.mus
``` 