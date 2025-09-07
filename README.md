Mejoras implementadas:
Constantes definidas: Usé #define para valores mágicos como el tamaño del buffer y capacidad inicial.

Gestión de memoria más eficiente:

Implementé una estrategia de crecimiento exponencial (doble de capacidad cada vez)

Evito llamadas frecuentes a realloc() reduciendo el overhead

Manejo robusto de strings:

Aseguro explícitamente la terminación nula después de cada copia

Muestro el conteo de caracteres leídos

Detección de errores:

Agregué verificación ferror(stdin) para detectar errores de lectura

Usé EXIT_SUCCESS y EXIT_FAILURE para mayor claridad

Código más legible:

Variables con nombres más descriptivos

Comentarios mejorados

Estructura más organizada

Optimización de rendimiento:

Menos llamadas a realloc()

Memoria pre-asignada para reducir fragmentación
