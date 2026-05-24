#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "funciones.h"
#include "validaciones.h"

// ================= COMPARAR TEXTOS =================

static int textosIguales(const char *texto1,
                         const char *texto2) {

    const char *p1 = texto1;
    const char *p2 = texto2;

    if (texto1 == NULL || texto2 == NULL) {
        return 0;
    }

    while (*p1 != '\0' && *p2 != '\0') {

        unsigned char c1 = (unsigned char)*p1;
        unsigned char c2 = (unsigned char)*p2;

        if (tolower(c1) != tolower(c2)) {
            return 0;
        }

        p1++;
        p2++;
    }

    return *p1 == '\0' && *p2 == '\0';
}

// ================= LIMPIAR PRODUCTO =================

static void limpiarProducto(char (*nombre)[TAM_NOMBRE_PRODUCTO],
                            int *demanda,
                            float *tiempoUnitario,
                            int *recursoUnitario) {

    if (nombre != NULL) {
        (*nombre)[0] = '\0';
    }

    if (demanda != NULL) {
        *demanda = 0;
    }

    if (tiempoUnitario != NULL) {
        *tiempoUnitario = 0;
    }

    if (recursoUnitario != NULL) {
        *recursoUnitario = 0;
    }
}

// ================= COPIAR PRODUCTO =================

static void copiarProducto(char (*nombreDestino)[TAM_NOMBRE_PRODUCTO],
                           int *demandaDestino,
                           float *tiempoDestino,
                           int *recursoDestino,
                           const char (*nombreOrigen)[TAM_NOMBRE_PRODUCTO],
                           const int *demandaOrigen,
                           const float *tiempoOrigen,
                           const int *recursoOrigen) {

    strcpy(*nombreDestino, *nombreOrigen);
    *demandaDestino = *demandaOrigen;
    *tiempoDestino = *tiempoOrigen;
    *recursoDestino = *recursoOrigen;
}

// ================= IMPRIMIR PRODUCTO =================

static void imprimirProducto(int numeroProducto,
                             const char (*nombre)[TAM_NOMBRE_PRODUCTO],
                             const int *demanda,
                             const float *tiempoUnitario,
                             const int *recursoUnitario) {

    float tiempoTotal;
    int recursosTotales;

    tiempoTotal = (*demanda) * (*tiempoUnitario);
    recursosTotales = (*demanda) * (*recursoUnitario);

    printf("\nProducto %d\n", numeroProducto);
    printf("Nombre: %s\n", *nombre);
    printf("Cantidad demandada: %d\n", *demanda);
    printf("Tiempo por unidad: %.2f\n", *tiempoUnitario);
    printf("Recursos por unidad: %d\n", *recursoUnitario);
    printf("Tiempo total requerido: %.2f\n", tiempoTotal);
    printf("Recursos totales requeridos: %d\n", recursosTotales);
}

// ================= INICIALIZAR PRODUCTOS =================

void inicializarProductos(int totalEspacios,
                          char (*nombres)[TAM_NOMBRE_PRODUCTO],
                          int *demandas,
                          float *tiemposUnitarios,
                          int *recursosUnitarios) {

    char (*nombreActual)[TAM_NOMBRE_PRODUCTO] = nombres;
    int *demandaActual = demandas;
    float *tiempoActual = tiemposUnitarios;
    int *recursoActual = recursosUnitarios;

    for (int i = 0; i < totalEspacios; i++) {

        limpiarProducto(nombreActual,
                        demandaActual,
                        tiempoActual,
                        recursoActual);

        nombreActual++;
        demandaActual++;
        tiempoActual++;
        recursoActual++;
    }
}

// ================= INGRESAR UN PRODUCTO =================

void ingresarProducto(int indice,
                      char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      int *demandas,
                      float *tiemposUnitarios,
                      int *recursosUnitarios) {

    char mensaje[120];
    char (*nombreProducto)[TAM_NOMBRE_PRODUCTO] = nombres + indice;
    int *demandaProducto = demandas + indice;
    float *tiempoProducto = tiemposUnitarios + indice;
    int *recursoProducto = recursosUnitarios + indice;

    printf("\n======= INGRESO DEL PRODUCTO %d =======\n",
           indice + 1);

    sprintf(mensaje,
            "Ingrese el nombre del producto %d: ",
            indice + 1);

    leerNombreProducto(mensaje,
                       *nombreProducto,
                       TAM_NOMBRE_PRODUCTO);

    *demandaProducto = leerEntero(
        "Ingrese la cantidad demandada: ",
        0,
        SIN_MAXIMO
    );

    *tiempoProducto = leerFloat(
        "Ingrese el tiempo de fabricacion por unidad: ",
        0,
        0
    );

    *recursoProducto = leerEntero(
        "Ingrese los recursos requeridos por unidad: ",
        1,
        SIN_MAXIMO
    );
}

// ================= INGRESAR PRODUCTOS =================

void ingresarProductos(int *totalProductos,
                       int maxProductos,
                       char (*nombres)[TAM_NOMBRE_PRODUCTO],
                       int *demandas,
                       float *tiemposUnitarios,
                       int *recursosUnitarios) {

    if (totalProductos == NULL) {
        return;
    }

    if (maxProductos <= 0 || maxProductos > MAX_PRODUCTOS) {
        maxProductos = MAX_PRODUCTOS;
    }

    *totalProductos = leerEntero(
        "Ingrese la cantidad de productos a registrar: ",
        1,
        maxProductos
    );

    for (int i = 0; i < *totalProductos; i++) {
        ingresarProducto(i,
                         nombres,
                         demandas,
                         tiemposUnitarios,
                         recursosUnitarios);
    }
}

// ================= MOSTRAR UN PRODUCTO =================

void mostrarProducto(int indice,
                     const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                     const int *demandas,
                     const float *tiemposUnitarios,
                     const int *recursosUnitarios) {

    imprimirProducto(indice + 1,
                     nombres + indice,
                     demandas + indice,
                     tiemposUnitarios + indice,
                     recursosUnitarios + indice);
}

// ================= MOSTRAR PRODUCTOS =================

void mostrarProductos(int totalProductos,
                      const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      const int *demandas,
                      const float *tiemposUnitarios,
                      const int *recursosUnitarios) {

    const char (*nombreActual)[TAM_NOMBRE_PRODUCTO] = nombres;
    const int *demandaActual = demandas;
    const float *tiempoActual = tiemposUnitarios;
    const int *recursoActual = recursosUnitarios;

    if (totalProductos <= 0) {

        printf("\nNo existen productos registrados.\n");
        return;
    }

    printf("\n======= LISTA DE PRODUCTOS =======\n");

    for (int i = 0; i < totalProductos; i++) {

        imprimirProducto(i + 1,
                         nombreActual,
                         demandaActual,
                         tiempoActual,
                         recursoActual);

        nombreActual++;
        demandaActual++;
        tiempoActual++;
        recursoActual++;
    }
}

// ================= BUSCAR PRODUCTO =================

int buscarProducto(int totalProductos,
                   const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                   const char *nombreBuscado) {

    const char (*nombreActual)[TAM_NOMBRE_PRODUCTO] = nombres;

    for (int i = 0; i < totalProductos; i++) {

        if (textosIguales(*nombreActual, nombreBuscado)) {
            return i;
        }

        nombreActual++;
    }

    return -1;
}

// ================= BUSCAR PRODUCTO INTERACTIVO =================

int pedirProducto(int totalProductos,
                  const char (*nombres)[TAM_NOMBRE_PRODUCTO]) {

    char nombreBuscado[TAM_NOMBRE_PRODUCTO];
    int posicion;

    if (totalProductos <= 0) {

        printf("\nNo existen productos registrados.\n");
        return -1;
    }

    leerNombreProducto(
        "Ingrese el nombre del producto a buscar: ",
        nombreBuscado,
        TAM_NOMBRE_PRODUCTO
    );

    posicion = buscarProducto(totalProductos,
                              nombres,
                              nombreBuscado);

    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
    }

    return posicion;
}

// ================= EDITAR PRODUCTO =================

void editarProducto(int totalProductos,
                    char (*nombres)[TAM_NOMBRE_PRODUCTO],
                    int *demandas,
                    float *tiemposUnitarios,
                    int *recursosUnitarios) {

    int posicion;
    int opcion;
    char (*nombreProducto)[TAM_NOMBRE_PRODUCTO];
    int *demandaProducto;
    float *tiempoProducto;
    int *recursoProducto;

    posicion = pedirProducto(totalProductos,
                             nombres);

    if (posicion == -1) {
        return;
    }

    nombreProducto = nombres + posicion;
    demandaProducto = demandas + posicion;
    tiempoProducto = tiemposUnitarios + posicion;
    recursoProducto = recursosUnitarios + posicion;

    printf("\n======= PRODUCTO ENCONTRADO =======\n");
    mostrarProducto(posicion,
                    nombres,
                    demandas,
                    tiemposUnitarios,
                    recursosUnitarios);

    printf("\n======= DATOS A EDITAR =======\n");
    printf("1. Nombre\n");
    printf("2. Cantidad demandada\n");
    printf("3. Tiempo de fabricacion por unidad\n");
    printf("4. Recursos requeridos por unidad\n");
    printf("5. Todos los datos\n");

    opcion = leerEntero(
        "Seleccione una opcion: ",
        1,
        5
    );

    switch (opcion) {

        case 1:
            leerNombreProducto(
                "Ingrese el nuevo nombre: ",
                *nombreProducto,
                TAM_NOMBRE_PRODUCTO
            );
            break;

        case 2:
            *demandaProducto = leerEntero(
                "Ingrese la nueva cantidad demandada: ",
                0,
                SIN_MAXIMO
            );
            break;

        case 3:
            *tiempoProducto = leerFloat(
                "Ingrese el nuevo tiempo por unidad: ",
                0,
                0
            );
            break;

        case 4:
            *recursoProducto = leerEntero(
                "Ingrese los nuevos recursos por unidad: ",
                1,
                SIN_MAXIMO
            );
            break;

        case 5:
            ingresarProducto(posicion,
                             nombres,
                             demandas,
                             tiemposUnitarios,
                             recursosUnitarios);
            break;
    }

    printf("\nProducto editado correctamente.\n");
}

// ================= ELIMINAR PRODUCTO =================

void eliminarProducto(int *totalProductos,
                      char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      int *demandas,
                      float *tiemposUnitarios,
                      int *recursosUnitarios) {

    int posicion;
    char (*nombreActual)[TAM_NOMBRE_PRODUCTO];
    char (*nombreSiguiente)[TAM_NOMBRE_PRODUCTO];
    int *demandaActual;
    int *demandaSiguiente;
    float *tiempoActual;
    float *tiempoSiguiente;
    int *recursoActual;
    int *recursoSiguiente;

    if (totalProductos == NULL || *totalProductos <= 0) {

        printf("\nNo existen productos registrados.\n");
        return;
    }

    posicion = pedirProducto(*totalProductos,
                             nombres);

    if (posicion == -1) {
        return;
    }

    nombreActual = nombres + posicion;
    nombreSiguiente = nombreActual + 1;
    demandaActual = demandas + posicion;
    demandaSiguiente = demandaActual + 1;
    tiempoActual = tiemposUnitarios + posicion;
    tiempoSiguiente = tiempoActual + 1;
    recursoActual = recursosUnitarios + posicion;
    recursoSiguiente = recursoActual + 1;

    for (int i = posicion; i < *totalProductos - 1; i++) {

        copiarProducto(nombreActual,
                       demandaActual,
                       tiempoActual,
                       recursoActual,
                       nombreSiguiente,
                       demandaSiguiente,
                       tiempoSiguiente,
                       recursoSiguiente);

        nombreActual++;
        nombreSiguiente++;
        demandaActual++;
        demandaSiguiente++;
        tiempoActual++;
        tiempoSiguiente++;
        recursoActual++;
        recursoSiguiente++;
    }

    (*totalProductos)--;

    limpiarProducto(nombres + *totalProductos,
                    demandas + *totalProductos,
                    tiemposUnitarios + *totalProductos,
                    recursosUnitarios + *totalProductos);

    printf("\nProducto eliminado correctamente.\n");
}

// ================= CALCULAR TIEMPO TOTAL =================

float calcularTiempoTotal(int totalProductos,
                          const int *demandas,
                          const float *tiemposUnitarios) {

    float tiempoTotal = 0;
    const int *demandaActual = demandas;
    const float *tiempoActual = tiemposUnitarios;

    for (int i = 0; i < totalProductos; i++) {

        tiempoTotal += (*demandaActual) * (*tiempoActual);
        demandaActual++;
        tiempoActual++;
    }

    return tiempoTotal;
}

// ================= CALCULAR RECURSOS TOTALES =================

int calcularRecursos(int totalProductos,
                     const int *demandas,
                     const int *recursosUnitarios) {

    int recursosTotales = 0;
    const int *demandaActual = demandas;
    const int *recursoActual = recursosUnitarios;

    for (int i = 0; i < totalProductos; i++) {

        recursosTotales += (*demandaActual) * (*recursoActual);
        demandaActual++;
        recursoActual++;
    }

    return recursosTotales;
}

// ================= VERIFICAR FACTIBILIDAD =================

int esProduccionPosible(float tiempoTotal,
                        int recursosTotales,
                        float tiempoDisponible,
                        int recursosDisponibles) {

    return tiempoTotal <= tiempoDisponible &&
           recursosTotales <= recursosDisponibles;
}

// ================= ANALIZAR PRODUCCION =================

void evaluarProduccion(int totalProductos,
                       const int *demandas,
                       const float *tiemposUnitarios,
                       const int *recursosUnitarios) {

    float tiempoTotal;
    int recursosTotales;
    float tiempoDisponible;
    int recursosDisponibles;

    if (totalProductos <= 0) {

        printf("\nNo existen productos registrados.\n");
        return;
    }

    tiempoTotal = calcularTiempoTotal(totalProductos,
                                      demandas,
                                      tiemposUnitarios);

    recursosTotales = calcularRecursos(totalProductos,
                                       demandas,
                                       recursosUnitarios);

    printf("\n======= ANALISIS DE PRODUCCION =======\n");
    printf("Tiempo total requerido: %.2f\n", tiempoTotal);
    printf("Recursos totales requeridos: %d\n", recursosTotales);

    tiempoDisponible = leerFloat(
        "Ingrese el tiempo disponible de produccion: ",
        0,
        0
    );

    recursosDisponibles = leerEntero(
        "Ingrese los recursos disponibles: ",
        0,
        SIN_MAXIMO
    );

    if (esProduccionPosible(tiempoTotal,
                            recursosTotales,
                            tiempoDisponible,
                            recursosDisponibles)) {

        printf("\nLa fabrica SI puede cumplir con la demanda.\n");

    } else {

        printf("\nLa fabrica NO puede cumplir con la demanda.\n");

        if (tiempoTotal > tiempoDisponible) {
            printf("Falta tiempo de produccion: %.2f\n",
                   tiempoTotal - tiempoDisponible);
        }

        if (recursosTotales > recursosDisponibles) {
            printf("Faltan recursos: %d\n",
                   recursosTotales - recursosDisponibles);
        }
    }
}

// ================= MENU PRINCIPAL =================

void mostrarMenu(void) {

    printf("\n======= MENU PRINCIPAL =======\n");
    printf("1. Ingresar productos\n");
    printf("2. Mostrar productos\n");
    printf("3. Editar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Analizar produccion\n");
    printf("6. Salir\n");
}
