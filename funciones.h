#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 5
#define TAM_NOMBRE_PRODUCTO 31

void inicializarProductos(int totalEspacios,
                          char (*nombres)[TAM_NOMBRE_PRODUCTO],
                          int *demandas,
                          float *tiemposUnitarios,
                          int *recursosUnitarios);

void ingresarProducto(int indice,
                      char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      int *demandas,
                      float *tiemposUnitarios,
                      int *recursosUnitarios);

void ingresarProductos(int *totalProductos,
                       int maxProductos,
                       char (*nombres)[TAM_NOMBRE_PRODUCTO],
                       int *demandas,
                       float *tiemposUnitarios,
                       int *recursosUnitarios);

void mostrarProducto(int indice,
                     const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                     const int *demandas,
                     const float *tiemposUnitarios,
                     const int *recursosUnitarios);

void mostrarProductos(int totalProductos,
                      const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      const int *demandas,
                      const float *tiemposUnitarios,
                      const int *recursosUnitarios);

int buscarProducto(int totalProductos,
                   const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                   const char *nombreBuscado);

int pedirProducto(int totalProductos,
                  const char (*nombres)[TAM_NOMBRE_PRODUCTO]);

void editarProducto(int totalProductos,
                    char (*nombres)[TAM_NOMBRE_PRODUCTO],
                    int *demandas,
                    float *tiemposUnitarios,
                    int *recursosUnitarios);

void eliminarProducto(int *totalProductos,
                      char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      int *demandas,
                      float *tiemposUnitarios,
                      int *recursosUnitarios);

float calcularTiempoTotal(int totalProductos,
                          const int *demandas,
                          const float *tiemposUnitarios);

int calcularRecursos(int totalProductos,
                     const int *demandas,
                     const int *recursosUnitarios);

int esProduccionPosible(float tiempoTotal,
                        int recursosTotales,
                        float tiempoDisponible,
                        int recursosDisponibles);

void evaluarProduccion(int totalProductos,
                       const int *demandas,
                       const float *tiemposUnitarios,
                       const int *recursosUnitarios);

void mostrarMenu(void);

#endif
