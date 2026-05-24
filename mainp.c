#include <stdio.h>

#include "validaciones.h"
#include "funciones.h"



int main(void) {

    // Arreglos paralelos para guardar la informacion de los productos.
    char nombres[MAX_PRODUCTOS][TAM_NOMBRE_PRODUCTO];
    int demandas[MAX_PRODUCTOS];
    float tiemposUnitarios[MAX_PRODUCTOS];
    int recursosUnitarios[MAX_PRODUCTOS];

    // Punteros que apuntan al inicio de cada arreglo paralelo.
    char (*ptrNombres)[TAM_NOMBRE_PRODUCTO] = nombres;
    int *ptrDemandas = demandas;
    float *ptrTiemposUnitarios = tiemposUnitarios;
    int *ptrRecursosUnitarios = recursosUnitarios;

    // Variables de control del programa.
    int totalProductos = 0;
    int opcion;
    int salir = 0;

    // Inicializa los arreglos para empezar sin datos basura.
    inicializarProductos(MAX_PRODUCTOS, ptrNombres, ptrDemandas,ptrTiemposUnitarios,ptrRecursosUnitarios);

    // Ciclo principal: muestra el menu hasta que el usuario decida salir.
    do {

        mostrarMenu();

        // Lee la opcion usando validacion para aceptar solo numeros del 1 al 6.
        opcion = leerEntero(
            "Seleccione una opcion: ",
            1,
            6
        );

        switch (opcion) {

            case 1:

                // Permite registrar los productos y sus datos de produccion.
                ingresarProductos(&totalProductos, MAX_PRODUCTOS, ptrNombres,ptrDemandas, ptrTiemposUnitarios,ptrRecursosUnitarios);

                break;

            case 2:

                // Muestra todos los productos registrados con sus calculos.
                mostrarProductos(totalProductos, ptrNombres, ptrDemandas, ptrTiemposUnitarios, ptrRecursosUnitarios);

                break;

            case 3:

                // Busca un producto por nombre y permite modificar sus datos.
                editarProducto(totalProductos, ptrNombres, ptrDemandas,ptrTiemposUnitarios, ptrRecursosUnitarios);

                break;

            case 4:

                // Busca un producto por nombre y lo elimina del arreglo.
                eliminarProducto(&totalProductos, ptrNombres, ptrDemandas, ptrTiemposUnitarios,ptrRecursosUnitarios);

                break;

            case 5:

                // Calcula tiempo, recursos y determina si se cumple la demanda.
                evaluarProduccion(totalProductos, ptrDemandas, ptrTiemposUnitarios, ptrRecursosUnitarios);

                break;

            case 6:

                // Termina el ciclo principal y finaliza el programa.
                salir = 1;
                printf("\nGracias por usar el sistema de produccion.\n");

                break;
        }

    } while (!salir);

    return 0;
}
