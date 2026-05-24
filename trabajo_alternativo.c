#include <stdio.h>

#define PRODUCTOS 5
#define TAM 30

char nombres[PRODUCTOS][TAM];
int demanda[PRODUCTOS];
float tiempo[PRODUCTOS];
int recursos[PRODUCTOS];
int activo[PRODUCTOS] = {0};

void limpiarEntrada(void);
void quitarSalto(char texto[]);
int textosIguales(char primero[], char segundo[]);
int localizarProducto(char nombreBuscado[]);
void registrarProductos(void);
void listarProductos(void);
void modificarProducto(void);
void borrarProducto(void);
void evaluarProduccion(void);

int main(void) {
    int opcion;

    do {
        printf("\n===== SISTEMA DE OPTIMIZACION DE PRODUCCION =====\n");
        printf("1. Ingresar productos\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular produccion\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("OPCION NO VALIDA \n");
            limpiarEntrada();
            opcion = 0;
            continue;
        }

        limpiarEntrada();

        switch (opcion) {
            case 1:
                registrarProductos();
                break;
            case 2:
                listarProductos();
                break;
            case 3:
                modificarProducto();
                break;
            case 4:
                borrarProducto();
                break;
            case 5:
                evaluarProduccion();
                break;
            case 6:
                printf("SALIENDO DEL SISTEMA........\n");
                break;
            default:
                printf("OPCION NO VALIDA \n");
                break;
        }
    } while (opcion != 6);

    return 0;
}

void limpiarEntrada(void) {
    int caracter;

    do {
        caracter = getchar();
    } while (caracter != '\n' && caracter != EOF);
}

void quitarSalto(char texto[]) {
    int posicion = 0;

    while (texto[posicion] != '\0') {
        if (texto[posicion] == '\n') {
            texto[posicion] = '\0';
            return;
        }

        posicion++;
    }
}

int textosIguales(char primero[], char segundo[]) {
    int posicion = 0;

    while (primero[posicion] != '\0' && segundo[posicion] != '\0') {
        if (primero[posicion] != segundo[posicion]) {
            return 0;
        }

        posicion++;
    }

    return primero[posicion] == '\0' && segundo[posicion] == '\0';
}

int localizarProducto(char nombreBuscado[]) {
    int indice;

    for (indice = 0; indice < PRODUCTOS; indice++) {
        if (activo[indice] == 1 && textosIguales(nombres[indice], nombreBuscado)) {
            return indice;
        }
    }

    return -1;
}

void registrarProductos(void) {
    int indice;

    for (indice = 0; indice < PRODUCTOS; indice++) {
        printf("\n PRODUCTO N. %d\n", indice + 1);
        printf("INGRESE EL NOMBRE DEL PRODUCTO:");
        fgets(nombres[indice], TAM, stdin);
        quitarSalto(nombres[indice]);

        printf("INGRESE LA CANTIDAD DEMANDADA:");
        scanf("%d", &demanda[indice]);

        printf("INGRESE EL TIEMPO DE FABRICACION POR UNIDAD: \n");
        scanf("%f", &tiempo[indice]);

        printf("INGRESE LA CANTIDAD DE RECURSOS POR UNIDAD: \n");
        scanf("%d", &recursos[indice]);

        limpiarEntrada();
        activo[indice] = 1;
    }
}

void listarProductos(void) {
    int indice;

    printf("\n LISTA DE PRODUCTOS DISPONIBLES \n");

    for (indice = 0; indice < PRODUCTOS; indice++) {
        if (activo[indice] == 1) {
            printf("PRODUCTO %s \n", nombres[indice]);
            printf("TIENE UNA DEMANDA DE: %d UNIDADES \n", demanda[indice]);
            printf("EL TIEMPO DE FABRICACION POR UNIDAD ES DE: %.2f HORAS \n", tiempo[indice]);
            printf("LOS RECURSOS UTILIZADOS POR CADA UNIDAD SON: %d\n", recursos[indice]);
        }
    }
}

void modificarProducto(void) {
    char nombreBuscado[TAM];
    int posicion;

    printf("INGRESE EL NOMBRE DEL PRODUCTO QUE DESEA EDITAR: \n");
    fgets(nombreBuscado, TAM, stdin);
    quitarSalto(nombreBuscado);

    posicion = localizarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("PRODUCTO NO ENCONTRADO \n");
    } else {
        printf("INGRESE EL NUEVO NOMBRE DEL PRODUCTO: \n ");
        fgets(nombres[posicion], TAM, stdin);
        quitarSalto(nombres[posicion]);

        printf("INGRESE LA NUEVA CANTIDAD DEMANDADA: \n");
        scanf("%d", &demanda[posicion]);

        printf("Ingrese el nuevo tiempo por unidad: ");
        scanf("%f", &tiempo[posicion]);

        printf("Ingrese la nueva cantidad de recursos por unidad: ");
        scanf("%d", &recursos[posicion]);

        limpiarEntrada();
        printf("Producto editado correctamente.\n");
    }
}

void borrarProducto(void) {
    char nombreBuscado[TAM];
    int posicion;

    printf("\n INGRESE EL NOMBRE DEL PRODUCTO QUE DESEA ELIMINAR ");
    fgets(nombreBuscado, TAM, stdin);
    quitarSalto(nombreBuscado);

    posicion = localizarProducto(nombreBuscado);

    if (posicion == -1) {
        printf("PRODUCTO NO ENCONTRADO\n");
    } else {
        activo[posicion] = 0;
        printf("PRODUCTO ELIMINADO CORRECTAMENTE \n");
    }
}

void evaluarProduccion(void) {
    float tiempoDisponible;
    int recursosDisponibles;
    float tiempoTotal = 0;
    int recursosTotales = 0;
    int indice;

    printf("INGRESE EL TIEMPO TOTAL DISPONIBLE DE PRODUCCION: \n");
    scanf("%f", &tiempoDisponible);

    printf("INGRESE LA CANTIDAD TOTAL DE RECURSOS DISPONIBLES: \n");
    scanf("%d", &recursosDisponibles);

    limpiarEntrada();

    for (indice = 0; indice < PRODUCTOS; indice++) {
        if (activo[indice] == 1) {
            tiempoTotal += demanda[indice] * tiempo[indice];
            recursosTotales += demanda[indice] * recursos[indice];
        }
    }

    printf("\n===== RESULTADO DE PRODUCCION =====\n");
    printf("Tiempo total requerido: %.2f horas\n", tiempoTotal);
    printf("Recursos totales requeridos: %d\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("La fabrica SI puede cumplir con la demanda.\n");
    } else {
        printf("La fabrica NO puede cumplir con la demanda.\n");

        if (tiempoTotal > tiempoDisponible) {
            printf("Falta tiempo de produccion.\n");
        }

        if (recursosTotales > recursosDisponibles) {
            printf("Faltan recursos disponibles.\n");
        }
    }
}
