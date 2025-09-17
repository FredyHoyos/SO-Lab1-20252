#include <stdio.h>   // Librería estándar de entrada y salida
#include <stdlib.h>  // Librería estándar (malloc, free, exit, etc.)
#include <string.h>  // Librería para manejo de cadenas (strcmp, memcpy, etc.)

int main(int argc, char *argv[]) {
    // Si hay más de 2 argumentos (además del nombre del programa), se muestra un error de uso.
    if (argc > 3) { 
        fprintf(stderr, "usage: reverse <input> <output>\n"); 
        exit(1); 
    }

    // Se inicializan punteros de archivo. Por defecto son stdin y stdout.
    FILE *in = stdin, *out = stdout;

    // Si se pasa al menos un argumento (archivo de entrada):
    if (argc >= 2) {
        in = fopen(argv[1], "r");   // Se abre el archivo en modo lectura
        if (!in) { 
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]); 
            exit(1); 
        }
    }

    // Si se pasa un segundo argumento (archivo de salida):
    if (argc == 3) {
        // Se verifica que los archivos de entrada y salida no sean el mismo
        if (strcmp(argv[1], argv[2]) == 0) { 
            fprintf(stderr, "El archivo de entrada y salida deben diferir\n"); 
            if (in != stdin) fclose(in); 
            exit(1); 
        }
        out = fopen(argv[2], "w");   // Se abre el archivo en modo escritura
        if (!out) { 
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]); 
            if (in != stdin) fclose(in); 
            exit(1); 
        }
    }

    // Si no se pasa ningún archivo, se solicita entrada por teclado
    if (argc == 1) 
        printf("Introduce texto (Ctrl+D en Linux/WSL, Ctrl+Z en Windows):\n");

    // Variables para lectura de líneas
    char *line = NULL;     // Línea actual leída
    size_t cap = 0;        // Capacidad del buffer
    ssize_t r;             // Número de caracteres leídos por getline
    char **lines = NULL;   // Arreglo dinámico para almacenar las líneas
    size_t n = 0;          // Cantidad de líneas almacenadas

    // Se leen todas las líneas del archivo/entrada estándar
    while ((r = getline(&line, &cap, in)) != -1) {
        int has_nl = (r > 0 && line[r-1] == '\n');   // Verifica si la línea termina en salto de línea
        size_t alloc = r + (has_nl ? 1 : 2);         // Se reserva espacio adicional si no hay '\n'
        char *copy = malloc(alloc);                  // Copia de la línea
        if (!copy) { 
            fprintf(stderr, "malloc failed\n"); 
            free(line); 
            exit(1); 
        }

        memcpy(copy, line, r);   // Copia el contenido de la línea

        // Se asegura que la línea tenga un '\0' al final (y añade '\n' si no lo tenía)
        if (has_nl) copy[r] = '\0';
        else { 
            copy[r] = '\n'; 
            copy[r+1] = '\0'; 
        }

        // Se redimensiona el arreglo de punteros para almacenar la nueva línea
        char **tmp = realloc(lines, (n + 1) * sizeof(char *));
        if (!tmp) { 
            fprintf(stderr, "malloc failed\n"); 
            free(copy); 
            free(line); 
            exit(1); 
        }

        lines = tmp; 
        lines[n++] = copy;  // Se añade la línea al arreglo
    }

    free(line);  // Se libera el buffer usado por getline

    // Si la salida es la consola y hay líneas, se imprime un salto de línea inicial
    if (out == stdout && n > 0) 
        fprintf(stdout, "\n");

    // Se recorren las líneas en orden inverso y se escriben en la salida
    size_t i = n;
    while (i--) {
        fprintf(out, "%s", lines[i]);  // Imprime la línea
        free(lines[i]);                // Libera la memoria de la línea
    }
    free(lines);   // Libera el arreglo de punteros

    // Se cierran los archivos si no son stdin/stdout
    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);

    return 0;  // Fin del programa
}
