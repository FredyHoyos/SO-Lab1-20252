#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 3) { fprintf(stderr, "usage: reverse <input> <output>\n"); exit(1); }

    FILE *in = stdin, *out = stdout;
    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (!in) { fprintf(stderr, "error: cannot open file '%s'\n", argv[1]); exit(1); }
    }
    if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) { fprintf(stderr, "El archivo de entrada y salida deben diferir\n"); if (in != stdin) fclose(in); exit(1); }
        out = fopen(argv[2], "w");
        if (!out) { fprintf(stderr, "error: cannot open file '%s'\n", argv[2]); if (in != stdin) fclose(in); exit(1); }
    }

    if (argc == 1) printf("Introduce texto (Ctrl+D en Linux/WSL, Ctrl+Z en Windows):\n");

    char *line = NULL; size_t cap = 0;
    ssize_t r;
    char **lines = NULL; size_t n = 0;

    while ((r = getline(&line, &cap, in)) != -1) {
        int has_nl = (r > 0 && line[r-1] == '\n');
        size_t alloc = r + (has_nl ? 1 : 2);
        char *copy = malloc(alloc);
        if (!copy) { fprintf(stderr, "malloc failed\n"); free(line); exit(1); }
        memcpy(copy, line, r);
        if (has_nl) copy[r] = '\0';
        else { copy[r] = '\n'; copy[r+1] = '\0'; }
        char **tmp = realloc(lines, (n + 1) * sizeof(char *));
        if (!tmp) { fprintf(stderr, "malloc failed\n"); free(copy); free(line); exit(1); }
        lines = tmp; lines[n++] = copy;
    }
    free(line);

    if (out == stdout && n > 0) fprintf(stdout, "\n");
    size_t i = n;
    while (i--) {
        fprintf(out, "%s", lines[i]);
        free(lines[i]);
    }
    free(lines);

    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);
    return 0;
}
