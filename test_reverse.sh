#!/usr/bin/env bash

PROG=./reverse
INPUT=input.txt
OUTPUT=output.txt

pass() { echo "✅ $1"; }
fail() { echo "❌ $1"; }

# 1. Entrada vacía
echo -n "" > "$INPUT"
$PROG "$INPUT" "$OUTPUT"
if [ ! -s "$OUTPUT" ]; then pass "Caso 1: Entrada vacía"; else fail "Caso 1: Entrada vacía"; fi

# 2. Una sola línea con \n
echo "unico" > "$INPUT"
$PROG "$INPUT" "$OUTPUT"
if diff -q "$INPUT" "$OUTPUT" >/dev/null; then pass "Caso 2: Una sola línea"; else fail "Caso 2: Una sola línea"; fi

# 3. Una sola línea sin \n: convertimos a exadecimal od -An -t x1 y eliminamos espacios tr -d ' '. Salto de linea es 0a.
printf "ultima" > "$INPUT"
$PROG "$INPUT" "$OUTPUT"
if [ "$(tail -c 1 "$OUTPUT"| od -An -t x1 | tr -d ' ')" = $'0a' ]; then pass "Caso 3: Línea sin salto"; else fail "Caso 3: Línea sin salto"; fi

# 4. Líneas en blanco
printf "primera\n\ntercera\n\n" > "$INPUT"
$PROG "$INPUT" "$OUTPUT"
if grep -q "tercera" "$OUTPUT" && grep -q "primera" "$OUTPUT"; then pass "Caso 4: Líneas en blanco"; else fail "Caso 4: Líneas en blanco"; fi

# 5. Archivo muy largo
seq 1 10000 > "$INPUT"
$PROG "$INPUT" "$OUTPUT"
FIRST=$(head -n 1 "$OUTPUT")
LAST=$(tail -n 1 "$OUTPUT")
if [ "$FIRST" = "10000" ] && [ "$LAST" = "1" ]; then pass "Caso 5: Archivo muy largo"; else fail "Caso 5: Archivo muy largo"; fi

# 6. Línea muy larga (1MB) 1048576
head -c 1048576 /dev/zero | tr '\0' 'x' > "$INPUT"
$PROG "$INPUT" "$OUTPUT"
SIZE=$(wc -c < "$OUTPUT")
if [ "$SIZE" -eq 1048577 ]; then pass "Caso 6: Línea muy larga"; else fail "Caso 6: Línea muy larga"; fi

# 7. Archivos iguales
echo "test" > "$INPUT"
ERROR=$($PROG "$INPUT" "$INPUT" 2>&1)
if [[ "$ERROR" == *"deben diferir"* ]]; then pass "Caso 7: Entrada y salida iguales"; else fail "Caso 7: Entrada y salida iguales"; fi

# 8. Demasiados argumentos
ERROR=$($PROG a b c 2>&1)
if [[ "$ERROR" == *"usage: reverse"* ]]; then pass "Caso 8: Demasiados argumentos"; else fail "Caso 8: Demasiados argumentos"; fi

# 9. Archivo inexistente
ERROR=$($PROG no_existe.txt 2>&1)
if [[ "$ERROR" == *"error: cannot open file 'no_existe.txt'"* ]]; then pass "Caso 9: Archivo inexistente"; else fail "Caso 9: Archivo inexistente"; fi

# 10. Entrada interactiva (simulada con printf) analizamos sed -n '3p' ya que la primera es un mensaje del programa y la segunda es un salto de línea introducidos durante la ejecucion del programa.
printf "hola\nmundo\n" | $PROG > "$OUTPUT"
if [ "$(sed -n '3p' "$OUTPUT")" = "mundo" ]; then pass "Caso 10: Entrada interactiva"; else fail "Caso 10: Entrada interactiva"; fi

rm -f "$INPUT" "$OUTPUT"
