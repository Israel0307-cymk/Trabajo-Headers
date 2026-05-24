#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define SIN_MAXIMO -1
#define TAM_ENTRADA 100
#define MAX_CARACTERES_TEXTO 30

// ELIMINA EL \n DE fgets
static inline void quitarSalto(char cadena[]) {

    cadena[strcspn(cadena, "\n")] = '\0';
}

// LIMPIA CARACTERES SOBRANTES CUANDO EL USUARIO SUPERA EL TAMANO DEL BUFFER
static inline void limpiarBufferEntrada(void) {

    int caracter;

    while ((caracter = getchar()) != '\n' &&
           caracter != EOF) {
    }
}

// LECTURA SEGURA PARA EVITAR DESBORDES Y ENTRADAS CORTADAS
static inline int leerLineaSegura(const char mensaje[],
                                  char destino[],
                                  int tamano) {

    size_t longitud;

    if (destino == NULL || tamano <= 1) {
        return 0;
    }

    if (mensaje != NULL) {
        printf("%s", mensaje);
    }

    if (fgets(destino, tamano, stdin) == NULL) {
        destino[0] = '\0';
        return 0;
    }

    longitud = strlen(destino);

    if (longitud > 0 && destino[longitud - 1] == '\n') {
        quitarSalto(destino);
        return 1;
    }

    if (longitud == (size_t)(tamano - 1)) {
        limpiarBufferEntrada();
        return 0;
    }

    return 1;
}

// VALIDA QUE EL TEXTO NO ESTE VACIO Y NO SUPERE EL MAXIMO PERMITIDO
static inline int esLongitudValida(const char cadena[],
                                   int maximoCaracteres) {

    size_t longitud;

    if (cadena == NULL || maximoCaracteres <= 0) {
        return 0;
    }

    longitud = strlen(cadena);

    return longitud > 0 &&
           longitud <= (size_t)maximoCaracteres;
}

// ================= VALIDAR ENTEROS =================

static inline int esEnteroValido(const char cadena[]) {

    int i = 0;

    if (cadena == NULL || cadena[0] == '\0') {
        return 0;
    }

    if (cadena[0] == '-' || cadena[0] == '+') {
        i = 1;
    }

    if (cadena[i] == '\0') {
        return 0;
    }

    for (; cadena[i] != '\0'; i++) {

        if (!isdigit((unsigned char)cadena[i])) {
            return 0;
        }
    }

    return 1;
}

// ================= VALIDAR FLOAT =================

static inline int esFloatValido(const char cadena[]) {

    int i = 0;
    int punto = 0;
    int digitos = 0;

    if (cadena == NULL || cadena[0] == '\0') {
        return 0;
    }

    if (cadena[0] == '-' || cadena[0] == '+') {
        i = 1;
    }

    for (; cadena[i] != '\0'; i++) {

        if (isdigit((unsigned char)cadena[i])) {

            digitos++;

        } else if (cadena[i] == '.') {

            punto++;

            if (punto > 1) {
                return 0;
            }

        } else {

            return 0;
        }
    }

    return digitos > 0;
}

// ================= VALIDAR SOLO LETRAS =================

static inline int esSoloLetras(const char cadena[]) {

    int tieneLetra = 0;

    if (cadena == NULL || cadena[0] == '\0') {
        return 0;
    }

    for (int i = 0; cadena[i] != '\0'; i++) {

        unsigned char c = (unsigned char)cadena[i];

        if (isalpha(c)) {

            tieneLetra = 1;

        } else if (isspace(c)) {

            continue;

        } else {

            return 0;
        }
    }

    return tieneLetra;
}

// ================= VALIDAR NOMBRE DE PRODUCTO =================

static inline int esNombreProductoValido(const char cadena[]) {

    int tieneCaracterUtil = 0;

    if (!esLongitudValida(cadena, MAX_CARACTERES_TEXTO)) {
        return 0;
    }

    for (int i = 0; cadena[i] != '\0'; i++) {

        unsigned char c = (unsigned char)cadena[i];

        if (isalnum(c) || c >= 128) {

            tieneCaracterUtil = 1;

        } else if (isspace(c) ||
                   c == '-' ||
                   c == '_' ||
                   c == '.' ||
                   c == '#' ||
                   c == '/') {

            continue;

        } else {

            return 0;
        }
    }

    return tieneCaracterUtil;
}

// ================= VALIDAR CODIGO DE PRODUCTO =================

static inline int esCodigoProductoValido(const char cadena[]) {

    if (!esLongitudValida(cadena, MAX_CARACTERES_TEXTO)) {
        return 0;
    }

    for (int i = 0; cadena[i] != '\0'; i++) {

        unsigned char c = (unsigned char)cadena[i];

        if (!isalnum(c) &&
            c != '-' &&
            c != '_') {

            return 0;
        }
    }

    return 1;
}

// ================= LEER ENTERO =================

static inline int leerEntero(const char mensaje[],
                             int minimo,
                             int maximo) {

    char entrada[TAM_ENTRADA];
    long valorTemporal;
    int valor;

    while (1) {

        if (!leerLineaSegura(mensaje, entrada, sizeof(entrada))) {

            printf("ERROR: entrada demasiado larga.\n");
            continue;
        }

        if (!esEnteroValido(entrada)) {

            printf("ERROR: ingrese solo numeros enteros.\n");
            continue;
        }

        valorTemporal = strtol(entrada, NULL, 10);

        if (valorTemporal < INT_MIN ||
            valorTemporal > INT_MAX) {

            printf("ERROR: numero fuera del rango permitido.\n");
            continue;
        }

        valor = (int)valorTemporal;

        if (valor < minimo) {

            printf("ERROR: valor minimo permitido: %d\n",
                   minimo);

            continue;
        }

        if (maximo != SIN_MAXIMO &&
            valor > maximo) {

            printf("ERROR: valor maximo permitido: %d\n",
                   maximo);

            continue;
        }

        return valor;
    }
}

// ================= LEER FLOAT =================

static inline float leerFloat(const char mensaje[],
                              float minimo,
                              int permiteMinimo) {

    char entrada[TAM_ENTRADA];
    float valor;

    while (1) {

        if (!leerLineaSegura(mensaje, entrada, sizeof(entrada))) {

            printf("ERROR: entrada demasiado larga.\n");
            continue;
        }

        if (!esFloatValido(entrada)) {

            printf("ERROR: ingrese un numero decimal valido.\n");
            continue;
        }

        valor = strtof(entrada, NULL);

        if (permiteMinimo) {

            if (valor < minimo) {

                printf("ERROR: valor minimo permitido: %.2f\n",
                       minimo);

                continue;
            }

        } else {

            if (valor <= minimo) {

                printf("ERROR: el valor debe ser mayor que %.2f\n",
                       minimo);

                continue;
            }
        }

        return valor;
    }
}

// ================= LEER SOLO LETRAS =================

static inline void leerTextoSoloLetras(const char mensaje[],
                                       char destino[],
                                       int tamano) {

    char entrada[TAM_ENTRADA];

    if (destino == NULL ||
        tamano < MAX_CARACTERES_TEXTO + 1) {

        printf("ERROR: el arreglo destino debe tener al menos %d espacios.\n",
               MAX_CARACTERES_TEXTO + 1);

        return;
    }

    while (1) {

        if (!leerLineaSegura(mensaje, entrada, sizeof(entrada))) {

            printf("ERROR: entrada demasiado larga.\n");
            continue;
        }

        if (!esLongitudValida(entrada, MAX_CARACTERES_TEXTO)) {

            printf("ERROR: ingrese entre 1 y %d caracteres.\n",
                   MAX_CARACTERES_TEXTO);

            continue;
        }

        if (!esSoloLetras(entrada)) {

            printf("ERROR: ingrese solo letras y espacios.\n");
            continue;
        }

        strcpy(destino, entrada);
        break;
    }
}

// ================= LEER NOMBRE DE PRODUCTO =================

static inline void leerNombreProducto(const char mensaje[],
                                      char destino[],
                                      int tamano) {

    char entrada[TAM_ENTRADA];

    if (destino == NULL ||
        tamano < MAX_CARACTERES_TEXTO + 1) {

        printf("ERROR: el arreglo destino debe tener al menos %d espacios.\n",
               MAX_CARACTERES_TEXTO + 1);

        return;
    }

    while (1) {

        if (!leerLineaSegura(mensaje, entrada, sizeof(entrada))) {

            printf("ERROR: entrada demasiado larga.\n");
            continue;
        }

        if (!esNombreProductoValido(entrada)) {

            printf("ERROR: ingrese un nombre valido de 1 a %d caracteres.\n",
                   MAX_CARACTERES_TEXTO);

            printf("Use letras, numeros, espacios o simbolos - _ . # /\n");
            continue;
        }

        strcpy(destino, entrada);
        break;
    }
}

// ================= LEER CODIGO DE PRODUCTO =================

static inline void leerCodigoProducto(const char mensaje[],
                                      char destino[],
                                      int tamano) {

    char entrada[TAM_ENTRADA];

    if (destino == NULL ||
        tamano < MAX_CARACTERES_TEXTO + 1) {

        printf("ERROR: el arreglo destino debe tener al menos %d espacios.\n",
               MAX_CARACTERES_TEXTO + 1);

        return;
    }

    while (1) {

        if (!leerLineaSegura(mensaje, entrada, sizeof(entrada))) {

            printf("ERROR: entrada demasiado larga.\n");
            continue;
        }

        if (!esCodigoProductoValido(entrada)) {

            printf("ERROR: ingrese un codigo de 1 a %d caracteres.\n",
                   MAX_CARACTERES_TEXTO);

            printf("Use solo letras, numeros, guion o guion bajo.\n");
            continue;
        }

        strcpy(destino, entrada);
        break;
    }
}

// ================= LEER S/N =================

static inline char leerSN(const char mensaje[]) {

    char entrada[TAM_ENTRADA];

    while (1) {

        if (!leerLineaSegura(mensaje, entrada, sizeof(entrada))) {

            printf("ERROR: entrada demasiado larga.\n");
            continue;
        }

        if (strlen(entrada) == 1 &&
            (entrada[0] == 'S' ||
             entrada[0] == 's' ||
             entrada[0] == 'N' ||
             entrada[0] == 'n')) {

            return entrada[0];
        }

        printf("ERROR: ingrese solamente S o N.\n");
    }
}

#endif
