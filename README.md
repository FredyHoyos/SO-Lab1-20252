Nombres:    
Juan Manuel Restrepo    
Fredy Hoyos Cardenas    
Dorian Garcia    

video: https://www.youtube.com/watch?v=ITRSxMZH8TY    

    
Como usarlo:    

    1. Compilar el programa:
        gcc -o reverse reverse.c    
        
    2. Usar de las siguientes formas:

       a) Leer desde teclado y mostrar invertido en pantalla:
          ./reverse
          (Escribir texto, finalizar con Ctrl+D en Linux/WSL o Ctrl+Z en Windows)

       b) Leer desde archivo y mostrar invertido en pantalla:
          ./reverse entrada.txt

       c) Leer desde archivo y guardar invertido en otro archivo:
          ./reverse entrada.txt salida.txt

    Nota: El archivo de entrada y salida no pueden ser el mismo.

Mejoras implementadas:
- Constantes definidas: Usé #define para valores mágicos como el tamaño del buffer y capacidad inicial.
- Gestión de memoria más eficiente:
  * Implementé una estrategia de crecimiento exponencial (doble de capacidad cada vez).
  * Evito llamadas frecuentes a realloc() reduciendo el overhead.
- Manejo robusto de strings:
  * Aseguro explícitamente la terminación nula después de cada copia.
  * Muestro el conteo de caracteres leídos.
- Detección de errores:
  * Agregué verificación ferror(stdin) para detectar errores de lectura.
  * Usé EXIT_SUCCESS y EXIT_FAILURE para mayor claridad.
- Código más legible:
  * Variables con nombres más descriptivos.
  * Comentarios mejorados.
  * Estructura más organizada.
- Optimización de rendimiento:
  * Menos llamadas a realloc().
  * Memoria pre-asignada para reducir fragmentación.


Desafíos encontrados y cómo se solucionaron:    
    --------------------------------------------    

    1. Lectura de líneas con diferentes longitudes:
       - Desafío: Manejar correctamente líneas muy largas o de tamaño variable sin causar desbordamientos de memoria.
       - Solución: Se utilizó getline(), que ajusta dinámicamente el tamaño del buffer de lectura según la longitud de cada línea.

    2. Gestión eficiente de la memoria:
       - Desafío: El uso de realloc() en cada inserción de línea generaba overhead y posible fragmentación de memoria.
       - Solución: Se implementó una estrategia de crecimiento exponencial para reducir el número de llamadas a realloc().

    3. Asegurar la terminación de cadenas:
       - Desafío: Algunas líneas no terminaban en '\n', lo que podía producir impresiones incorrectas o errores en la salida.
       - Solución: Se agregó lógica para verificar si la línea finaliza con salto de línea y, en caso contrario, añadirlo manualmente antes del '\0'.

    4. Errores al abrir archivos:
       - Desafío: El programa debía manejar errores al abrir archivos inexistentes o sin permisos.
       - Solución: Se añadieron validaciones con mensajes de error claros y finalización del programa con exit(EXIT_FAILURE).

    5. Evitar que entrada y salida sean el mismo archivo:
       - Desafío: Si el usuario usaba el mismo archivo como entrada y salida, se corría el riesgo de pérdida de datos.
       - Solución: Se implementó una verificación con strcmp() para impedir este caso y mostrar un error al usuario.

    6. Portabilidad entre sistemas operativos:
       - Desafío: En Linux se usa Ctrl+D y en Windows Ctrl+Z para finalizar la entrada estándar. Esto podía confundir a los usuarios.
       - Solución: Se añadió un mensaje explicativo indicando la combinación de teclas según el sistema.

