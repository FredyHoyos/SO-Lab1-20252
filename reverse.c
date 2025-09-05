#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[256];     // Buffer temporal para cada lectura
    char *texto = NULL;   // Aquí guardaremos todo el texto
    size_t total = 0;     // Tamaño acumulado

    // Lee entrada o también puede leer un .txt de esta manera: ./reverse < texto.txt
    printf("Escribe texto (Ctrl+D para terminar en Linux / Ctrl+Z en Windows):\n");

    // Repetimos hasta que no haya más líneas o el usuario termine la entrada
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        // Obtener la longitud del texto leído por fila, se activa cada vez que se da enter
        size_t len = strlen(buffer); 

        // Reservar más memoria (total + len + 1 para '\0'). El +1 es para el carácter nulo de fin de cadena
        char *tmp = realloc(texto, total + len + 1);

        // Verificar si realloc fue exitoso
        if (!tmp) {
            // Mensaje de error
            perror("Error reservando memoria");
            // Liberar memoria previamente asignada antes de salir
            free(texto);
            // Exit con error
            return 1;
        }
        // Actualizar el puntero si realloc fue exitoso
        texto = tmp;

        // Copiar lo leído al final del texto acumulado
        // memcpy(destino, origen, tamaño) copia memoria de un lugar a otro
        memcpy(texto + total, buffer, len + 1); 

        // Actualizar el tamaño total
        total += len;
    }

    // Mostrar el texto completo leído
    if (texto) {
        printf("\n--- Texto completo leído ---\n%s", texto);

        // Liberar la memoria asignada
        free(texto);
    } else {

        // Si no se ingresó texto
        printf("No se ingresó texto.\n");
    }

    // Salida exitosa
    return 0;
}