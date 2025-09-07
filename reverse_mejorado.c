#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define INITIAL_CAPACITY 1024

int main() {
    char buffer[BUFFER_SIZE];     // Buffer temporal para cada lectura
    char *texto = NULL;           // Aquí guardaremos todo el texto
    size_t total = 0;             // Tamaño acumulado sin el nulo
    size_t capacidad = 0;         // Capacidad actual del buffer
    
    printf("Escribe texto (Ctrl+D para terminar en Linux / Ctrl+Z en Windows):\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        
        // Verificar si necesitamos más memoria
        if (total + len + 1 > capacidad) {
            // Calcular nueva capacidad (doble del actual o mínimo INITIAL_CAPACITY)
            size_t nueva_capacidad = capacidad == 0 ? 
                INITIAL_CAPACITY : capacidad * 2;
            
            // Asegurar que la nueva capacidad sea suficiente
            while (nueva_capacidad < total + len + 1) {
                nueva_capacidad *= 2;
            }
            
            char *tmp = realloc(texto, nueva_capacidad);
            if (!tmp) {
                perror("Error reservando memoria");
                free(texto);
                return EXIT_FAILURE;
            }
            texto = tmp;
            capacidad = nueva_capacidad;
        }
        
        // Copiar el nuevo contenido
        memcpy(texto + total, buffer, len);
        total += len;
        texto[total] = '\0'; // Asegurar terminación nula
    }
    
    // Verificar errores de lectura
    if (ferror(stdin)) {
        perror("Error leyendo la entrada");
        free(texto);
        return EXIT_FAILURE;
    }
    
    // Mostrar resultados
    if (total > 0) {
        printf("\n--- Texto completo leído (%zu caracteres) ---\n%s", 
               total, texto);
        free(texto);
    } else {
        printf("No se ingresó texto.\n");
    }
    
    return EXIT_SUCCESS;
}