# README - Sistema de optimizacion de produccion

Este proyecto implementa un programa en C para controlar una produccion basica de componentes electronicos. El programa permite registrar productos, editar sus datos, eliminarlos, mostrar la informacion guardada y calcular si una fabrica puede cumplir con una demanda segun el tiempo y los recursos disponibles.

El codigo esta organizado de forma modular en tres archivos principales:

- `mainp.c`: contiene el programa principal, el menu y el flujo general.
- `funciones.h`: contiene las declaraciones de las funciones y constantes principales.
- `funciones.c`: contiene el desarrollo de todas las funciones del sistema.
- `validaciones.h`: contiene funciones de lectura y validacion de datos.

El proyecto usa arreglos paralelos y punteros, evitando estructuras (`struct`) y archivos, tal como pide la consigna.

---

## 1. Idea general del programa

El sistema trabaja con un maximo de 5 productos. Para cada producto se guarda:

- Nombre del producto.
- Cantidad demandada.
- Tiempo de fabricacion por unidad.
- Recursos necesarios por unidad.

Como no se usan estructuras, cada dato se guarda en un arreglo diferente. A esto se le llama uso de arreglos paralelos.

Ejemplo:

```c
char nombres[MAX_PRODUCTOS][TAM_NOMBRE_PRODUCTO];
int demandas[MAX_PRODUCTOS];
float tiemposUnitarios[MAX_PRODUCTOS];
int recursosUnitarios[MAX_PRODUCTOS];
```

Si el producto esta en la posicion `0`, entonces todos sus datos estan tambien en la posicion `0` de cada arreglo:

```c
nombres[0]            -> nombre del producto 1
demandas[0]           -> demanda del producto 1
tiemposUnitarios[0]   -> tiempo por unidad del producto 1
recursosUnitarios[0]  -> recursos por unidad del producto 1
```

Esta forma mantiene los datos relacionados usando la misma posicion en cada arreglo.

---

## 2. Archivo `mainp.c`

El archivo `mainp.c` es el punto de entrada del programa. Aqui se ejecuta la funcion `main`, se crean los arreglos principales, se crean punteros hacia esos arreglos y se controla el menu principal.

### 2.1 Librerias y archivos incluidos

```c
#include <stdio.h>

#include "validaciones.h"
#include "funciones.h"
```

`stdio.h` permite usar funciones como `printf`.

`validaciones.h` se incluye para usar funciones como `leerEntero`, que evita que el usuario ingrese datos incorrectos.

`funciones.h` se incluye para que `mainp.c` conozca las funciones implementadas en `funciones.c`, como `ingresarProductos`, `mostrarProductos`, `editarProducto`, entre otras.

### 2.2 Creacion de arreglos paralelos

Dentro de `main` se crean los arreglos donde se guarda la informacion:

```c
char nombres[MAX_PRODUCTOS][TAM_NOMBRE_PRODUCTO];
int demandas[MAX_PRODUCTOS];
float tiemposUnitarios[MAX_PRODUCTOS];
int recursosUnitarios[MAX_PRODUCTOS];
```

Estos arreglos son la base del almacenamiento del programa.

`MAX_PRODUCTOS` vale `5`, por lo que se pueden registrar hasta cinco productos.

`TAM_NOMBRE_PRODUCTO` vale `31`, porque el nombre puede tener hasta 30 caracteres reales y necesita un espacio extra para el caracter final `'\0'`.

### 2.3 Uso de punteros en `mainp.c`

Luego se crean punteros hacia el inicio de cada arreglo:

```c
char (*ptrNombres)[TAM_NOMBRE_PRODUCTO] = nombres;
int *ptrDemandas = demandas;
float *ptrTiemposUnitarios = tiemposUnitarios;
int *ptrRecursosUnitarios = recursosUnitarios;
```

Estos punteros permiten enviar los arreglos a las funciones de una manera mas directa.

El caso mas especial es:

```c
char (*ptrNombres)[TAM_NOMBRE_PRODUCTO] = nombres;
```

Este puntero apunta a un arreglo de caracteres de tamano `TAM_NOMBRE_PRODUCTO`. Se usa asi porque `nombres` no es un arreglo simple, sino una matriz de texto:

```c
char nombres[5][31];
```

Cada posicion de `nombres` es una cadena de texto.

### 2.4 Variables de control

```c
int totalProductos = 0;
int opcion;
int salir = 0;
```

`totalProductos` guarda cuantos productos se han registrado realmente.

`opcion` guarda la opcion seleccionada en el menu.

`salir` controla si el ciclo principal debe terminar.

### 2.5 Inicializacion de arreglos

```c
inicializarProductos(MAX_PRODUCTOS,
                     ptrNombres,
                     ptrDemandas,
                     ptrTiemposUnitarios,
                     ptrRecursosUnitarios);
```

Esta funcion limpia todos los espacios disponibles antes de empezar.

La inicializacion evita trabajar con datos basura. Por ejemplo, coloca:

- Nombre vacio.
- Demanda en `0`.
- Tiempo en `0`.
- Recursos en `0`.

Esta funcion esta en `funciones.c` y trabaja directamente sobre los arreglos recibidos.

### 2.6 Ciclo principal del programa

El programa usa un ciclo `do while`:

```c
do {
    ...
} while (!salir);
```

Esto significa que el menu se muestra al menos una vez y se repite mientras `salir` sea `0`.

Cuando el usuario selecciona la opcion `6`, la variable `salir` cambia a `1` y el ciclo termina.

### 2.7 Menu principal

Dentro del ciclo se llama:

```c
mostrarMenu();
```

Esta funcion imprime las opciones disponibles:

1. Ingresar productos.
2. Mostrar productos.
3. Editar producto.
4. Eliminar producto.
5. Analizar produccion.
6. Salir.

### 2.8 Lectura validada de la opcion

```c
opcion = leerEntero(
    "Seleccione una opcion: ",
    1,
    6
);
```

Aqui se usa `leerEntero`, que esta en `validaciones.h`.

Esta funcion obliga al usuario a ingresar un numero entero entre `1` y `6`. Si el usuario escribe letras, simbolos o un numero fuera del rango, el programa muestra un error y vuelve a pedir el dato.

### 2.9 Uso del `switch`

El `switch` ejecuta una accion diferente segun la opcion ingresada.

#### Opcion 1: ingresar productos

```c
ingresarProductos(&totalProductos,
                  MAX_PRODUCTOS,
                  ptrNombres,
                  ptrDemandas,
                  ptrTiemposUnitarios,
                  ptrRecursosUnitarios);
```

Esta opcion permite registrar productos desde cero.

Se envia `&totalProductos` porque la funcion necesita modificar directamente la cantidad de productos registrados. Al enviar la direccion de memoria, la funcion puede cambiar el valor original.

Tambien se envian los arreglos donde se guardaran los datos ingresados.

#### Opcion 2: mostrar productos

```c
mostrarProductos(totalProductos,
                 ptrNombres,
                 ptrDemandas,
                 ptrTiemposUnitarios,
                 ptrRecursosUnitarios);
```

Esta opcion muestra todos los productos registrados.

Tambien calcula por cada producto:

- Tiempo total requerido.
- Recursos totales requeridos.

#### Opcion 3: editar producto

```c
editarProducto(totalProductos,
               ptrNombres,
               ptrDemandas,
               ptrTiemposUnitarios,
               ptrRecursosUnitarios);
```

Esta opcion busca un producto por nombre y permite modificar:

- Nombre.
- Cantidad demandada.
- Tiempo por unidad.
- Recursos por unidad.
- Todos los datos.

#### Opcion 4: eliminar producto

```c
eliminarProducto(&totalProductos,
                 ptrNombres,
                 ptrDemandas,
                 ptrTiemposUnitarios,
                 ptrRecursosUnitarios);
```

Esta opcion busca un producto por nombre y lo elimina.

Se envia `&totalProductos` porque al eliminar un producto, la cantidad total debe disminuir.

La funcion tambien reordena los arreglos para no dejar espacios vacios en medio.

#### Opcion 5: analizar produccion

```c
evaluarProduccion(totalProductos,
                   ptrDemandas,
                   ptrTiemposUnitarios,
                   ptrRecursosUnitarios);
```

Esta opcion calcula:

- Tiempo total necesario para producir toda la demanda.
- Recursos totales necesarios.

Luego pide al usuario:

- Tiempo disponible.
- Recursos disponibles.

Finalmente, indica si la fabrica puede o no cumplir con la demanda.

#### Opcion 6: salir

```c
salir = 1;
printf("\nGracias por usar el sistema de produccion.\n");
```

Esta opcion termina el programa.

---

## 3. Archivo `funciones.c`

El archivo `funciones.c` contiene la logica del sistema. Aqui se desarrollan las funciones declaradas en `funciones.h`.

Este archivo es el mas importante para la parte funcional del proyecto, porque aqui se procesa la informacion, se recorren los arreglos y se hacen los calculos.

---

## 4. Funciones auxiliares internas

Algunas funciones en `funciones.c` tienen la palabra `static`.

Esto significa que solo se pueden usar dentro de `funciones.c`. No estan pensadas para ser llamadas desde `mainp.c`.

Sirven como apoyo para que el codigo principal quede mas ordenado.

### 4.1 `textosIguales`

```c
static int textosIguales(const char *texto1,
                         const char *texto2)
```

Esta funcion compara dos cadenas de texto recorriendo sus caracteres.

Recibe:

- `texto1`: primer texto.
- `texto2`: segundo texto.

Devuelve:

- `1` si los textos son iguales.
- `0` si son diferentes.

La comparacion no distingue entre mayusculas y minusculas. Por ejemplo:

```text
Resistencia
resistencia
```

se consideran iguales.

Dentro de la funcion se crean dos variables auxiliares de tipo `char *`:

```c
const char *p1 = texto1;
const char *p2 = texto2;
```

Luego se recorren ambos textos caracter por caracter:

```c
while (*p1 != '\0' && *p2 != '\0')
```

`*p1` significa "el caracter al que apunta p1".

Despues de comparar un caracter, ambas posiciones avanzan:

```c
p1++;
p2++;
```

Esto es aritmetica de punteros.

### 4.2 `limpiarProducto`

```c
static void limpiarProducto(char (*nombre)[TAM_NOMBRE_PRODUCTO],
                            int *demanda,
                            float *tiempoUnitario,
                            int *recursoUnitario)
```

Esta funcion limpia un producto especifico recibiendo las direcciones de sus datos.

Coloca:

- Nombre vacio.
- Demanda en `0`.
- Tiempo en `0`.
- Recurso en `0`.

Ejemplo:

```c
*demanda = 0;
*tiempoUnitario = 0;
*recursoUnitario = 0;
```

El asterisco se usa para modificar directamente el valor almacenado en la direccion recibida.

### 4.3 `copiarProducto`

```c
static void copiarProducto(...)
```

Esta funcion copia todos los datos de un producto origen hacia un producto destino.

Se usa principalmente al eliminar un producto.

Por ejemplo, si se elimina el producto de la posicion `1`, el producto de la posicion `2` debe pasar a la posicion `1`, el de la posicion `3` pasa a la posicion `2`, y asi sucesivamente.

La funcion copia:

- Nombre.
- Demanda.
- Tiempo unitario.
- Recurso unitario.

El nombre se copia con:

```c
strcpy(*nombreDestino, *nombreOrigen);
```

Los valores numericos se copian por direccion:

```c
*demandaDestino = *demandaOrigen;
*tiempoDestino = *tiempoOrigen;
*recursoDestino = *recursoOrigen;
```

### 4.4 `imprimirProducto`

```c
static void imprimirProducto(...)
```

Esta funcion muestra un producto recibiendo directamente las direcciones de sus datos.

Calcula:

```c
tiempoTotal = (*demanda) * (*tiempoUnitario);
recursosTotales = (*demanda) * (*recursoUnitario);
```

Aqui se obtiene cada valor desde su direccion:

- `*demanda` obtiene la cantidad demandada.
- `*tiempoUnitario` obtiene el tiempo por unidad.
- `*recursoUnitario` obtiene los recursos por unidad.

Luego imprime toda la informacion del producto.

---

## 5. Funciones principales de `funciones.c`

Estas funciones si estan declaradas en `funciones.h`, por lo tanto pueden ser llamadas desde `mainp.c`.

### 5.1 `inicializarProductos`

```c
void inicializarProductos(int totalEspacios,
                          char (*nombres)[TAM_NOMBRE_PRODUCTO],
                          int *demandas,
                          float *tiemposUnitarios,
                          int *recursosUnitarios)
```

Esta funcion inicializa todos los arreglos del sistema.

Recibe:

- `totalEspacios`: cuantos espacios se van a limpiar.
- `nombres`: puntero al arreglo de nombres.
- `demandas`: puntero al arreglo de demandas.
- `tiemposUnitarios`: puntero al arreglo de tiempos.
- `recursosUnitarios`: puntero al arreglo de recursos.

Dentro de la funcion se crean variables auxiliares:

```c
char (*nombreActual)[TAM_NOMBRE_PRODUCTO] = nombres;
int *demandaActual = demandas;
float *tiempoActual = tiemposUnitarios;
int *recursoActual = recursosUnitarios;
```

Estas variables apuntan al producto actual.

Luego se usa un ciclo:

```c
for (int i = 0; i < totalEspacios; i++)
```

En cada vuelta se limpia un producto y luego se avanza al siguiente:

```c
nombreActual++;
demandaActual++;
tiempoActual++;
recursoActual++;
```

Esto evita escribir `nombres[i]`, `demandas[i]`, etc. y muestra otra forma de recorrer arreglos.

### 5.2 `ingresarProducto`

```c
void ingresarProducto(int indice,
                      char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      int *demandas,
                      float *tiemposUnitarios,
                      int *recursosUnitarios)
```

Esta funcion registra un solo producto.

Recibe el indice del producto y los arreglos donde se guarda la informacion.

Dentro se calculan las direcciones exactas del producto:

```c
char (*nombreProducto)[TAM_NOMBRE_PRODUCTO] = nombres + indice;
int *demandaProducto = demandas + indice;
float *tiempoProducto = tiemposUnitarios + indice;
int *recursoProducto = recursosUnitarios + indice;
```

Por ejemplo, si `indice` vale `2`, entonces:

```c
demandas + 2
```

apunta a la demanda del tercer producto.

La funcion pide:

- Nombre del producto.
- Cantidad demandada.
- Tiempo de fabricacion por unidad.
- Recursos por unidad.

Cada dato se guarda directamente en la posicion correspondiente.

Ejemplo:

```c
*demandaProducto = leerEntero(...);
*tiempoProducto = leerFloat(...);
*recursoProducto = leerEntero(...);
```

### 5.3 `ingresarProductos`

```c
void ingresarProductos(int *totalProductos,
                       int maxProductos,
                       char (*nombres)[TAM_NOMBRE_PRODUCTO],
                       int *demandas,
                       float *tiemposUnitarios,
                       int *recursosUnitarios)
```

Esta funcion registra varios productos.

Recibe `totalProductos` como puntero:

```c
int *totalProductos
```

Esto permite modificar el valor original que esta en `mainp.c`.

Primero pregunta cuantos productos se van a registrar:

```c
*totalProductos = leerEntero(...);
```

Luego usa un ciclo para llamar varias veces a `ingresarProducto`:

```c
for (int i = 0; i < *totalProductos; i++)
```

Se usa `*totalProductos` porque `totalProductos` es un puntero y se necesita acceder a su valor.

### 5.4 `mostrarProducto`

```c
void mostrarProducto(int indice,
                     const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                     const int *demandas,
                     const float *tiemposUnitarios,
                     const int *recursosUnitarios)
```

Muestra un producto especifico.

Usa el indice para llegar a la posicion correcta:

```c
nombres + indice
demandas + indice
tiemposUnitarios + indice
recursosUnitarios + indice
```

Luego llama a `imprimirProducto`.

Esta funcion no modifica datos, por eso algunos parametros son `const`.

`const` significa que la funcion solo puede leer esos datos, no cambiarlos.

### 5.5 `mostrarProductos`

```c
void mostrarProductos(int totalProductos,
                      const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      const int *demandas,
                      const float *tiemposUnitarios,
                      const int *recursosUnitarios)
```

Muestra todos los productos registrados.

Primero valida si hay productos:

```c
if (totalProductos <= 0)
```

Si no hay productos, muestra un mensaje y termina.

Si hay productos, recorre los arreglos avanzando posicion por posicion:

```c
nombreActual++;
demandaActual++;
tiempoActual++;
recursoActual++;
```

En cada posicion llama a `imprimirProducto`.

### 5.6 `buscarProducto`

```c
int buscarProducto(int totalProductos,
                            const char (*nombres)[TAM_NOMBRE_PRODUCTO],
                            const char *nombreBuscado)
```

Busca un producto comparando su nombre.

Recorre el arreglo de nombres con un puntero:

```c
const char (*nombreActual)[TAM_NOMBRE_PRODUCTO] = nombres;
```

En cada vuelta compara:

```c
textosIguales(*nombreActual, nombreBuscado)
```

Si encuentra el producto, devuelve su posicion.

Si no lo encuentra, devuelve `-1`.

### 5.7 `pedirProducto`

```c
int pedirProducto(int totalProductos,
                              const char (*nombres)[TAM_NOMBRE_PRODUCTO])
```

Esta funcion pide al usuario el nombre del producto que desea buscar.

Primero valida que existan productos registrados.

Luego lee el nombre usando:

```c
leerNombreProducto(...)
```

Despues llama a:

```c
buscarProducto(...)
```

Si el producto existe, devuelve su posicion.

Si no existe, muestra un mensaje y devuelve `-1`.

### 5.8 `editarProducto`

```c
void editarProducto(int totalProductos,
                    char (*nombres)[TAM_NOMBRE_PRODUCTO],
                    int *demandas,
                    float *tiemposUnitarios,
                    int *recursosUnitarios)
```

Permite modificar la informacion de un producto.

Primero llama a `pedirProducto` para encontrar el producto.

Si no se encuentra, termina.

Si se encuentra, se calculan direcciones directas a sus datos:

```c
nombreProducto = nombres + posicion;
demandaProducto = demandas + posicion;
tiempoProducto = tiemposUnitarios + posicion;
recursoProducto = recursosUnitarios + posicion;
```

Despues muestra un menu de edicion:

1. Nombre.
2. Cantidad demandada.
3. Tiempo de fabricacion por unidad.
4. Recursos requeridos por unidad.
5. Todos los datos.

Segun la opcion elegida, modifica el dato correspondiente.

Ejemplo:

```c
*demandaProducto = leerEntero(...);
```

Esto cambia directamente el valor dentro del arreglo original.

### 5.9 `eliminarProducto`

```c
void eliminarProducto(int *totalProductos,
                      char (*nombres)[TAM_NOMBRE_PRODUCTO],
                      int *demandas,
                      float *tiemposUnitarios,
                      int *recursosUnitarios)
```

Elimina un producto del sistema.

Recibe `totalProductos` como puntero porque al eliminar un producto se debe disminuir la cantidad real:

```c
(*totalProductos)--;
```

Primero busca el producto por nombre.

Luego usa direcciones para desplazar los productos siguientes hacia la izquierda.

Ejemplo:

Si hay 4 productos y se elimina el producto 2:

```text
Antes:
0 -> Producto A
1 -> Producto B
2 -> Producto C
3 -> Producto D

Despues:
0 -> Producto A
1 -> Producto C
2 -> Producto D
```

El desplazamiento se hace con:

```c
copiarProducto(...)
```

Despues de copiar, las direcciones avanzan:

```c
nombreActual++;
nombreSiguiente++;
demandaActual++;
demandaSiguiente++;
tiempoActual++;
tiempoSiguiente++;
recursoActual++;
recursoSiguiente++;
```

Al final, limpia la ultima posicion para no dejar datos repetidos.

### 5.10 `calcularTiempoTotal`

```c
float calcularTiempoTotal(int totalProductos,
                          const int *demandas,
                          const float *tiemposUnitarios)
```

Calcula el tiempo total necesario para producir todos los productos.

Formula por producto:

```text
tiempo requerido = demanda * tiempo por unidad
```

La funcion recorre los arreglos a partir de sus direcciones:

```c
const int *demandaActual = demandas;
const float *tiempoActual = tiemposUnitarios;
```

En cada vuelta suma:

```c
tiempoTotal += (*demandaActual) * (*tiempoActual);
```

Luego avanza:

```c
demandaActual++;
tiempoActual++;
```

Devuelve el total como `float`.

### 5.11 `calcularRecursos`

```c
int calcularRecursos(int totalProductos,
                            const int *demandas,
                            const int *recursosUnitarios)
```

Calcula los recursos totales necesarios.

Formula por producto:

```text
recursos requeridos = demanda * recursos por unidad
```

Tambien recorre los datos de la misma forma:

```c
recursosTotales += (*demandaActual) * (*recursoActual);
```

Devuelve el total como entero.

### 5.12 `esProduccionPosible`

```c
int esProduccionPosible(float tiempoTotal,
                           int recursosTotales,
                           float tiempoDisponible,
                           int recursosDisponibles)
```

Esta funcion determina si la fabrica puede cumplir con la produccion.

Devuelve `1` cuando:

```c
tiempoTotal <= tiempoDisponible &&
recursosTotales <= recursosDisponibles
```

Devuelve `0` si falta tiempo, recursos o ambos.

### 5.13 `evaluarProduccion`

```c
void evaluarProduccion(int totalProductos,
                        const int *demandas,
                        const float *tiemposUnitarios,
                        const int *recursosUnitarios)
```

Esta funcion realiza el analisis final de produccion.

Primero verifica que existan productos registrados.

Luego calcula:

```c
tiempoTotal = calcularTiempoTotal(...);
recursosTotales = calcularRecursos(...);
```

Despues muestra esos resultados y pide al usuario:

- Tiempo disponible de produccion.
- Recursos disponibles.

Finalmente llama a:

```c
esProduccionPosible(...)
```

Si la respuesta es verdadera, muestra:

```text
La fabrica SI puede cumplir con la demanda.
```

Si no puede cumplir, muestra cuanto falta.

Puede faltar:

- Tiempo de produccion.
- Recursos.
- Ambos.

### 5.14 `mostrarMenu`

```c
void mostrarMenu(void)
```

Esta funcion solo imprime el menu principal.

Esta separacion ayuda a que `mainp.c` no tenga demasiados `printf` y se mantenga mas ordenado.

---

## 6. Archivo `funciones.h`

`funciones.h` contiene las declaraciones de las funciones.

Este archivo funciona como un contrato entre `mainp.c` y `funciones.c`.

Cuando `mainp.c` incluye:

```c
#include "funciones.h"
```

puede usar todas las funciones declaradas alli.

Tambien se definen constantes:

```c
#define MAX_PRODUCTOS 5
#define TAM_NOMBRE_PRODUCTO 31
```

`MAX_PRODUCTOS` limita el proyecto a 5 productos.

`TAM_NOMBRE_PRODUCTO` permite nombres de hasta 30 caracteres mas el caracter final `'\0'`.

---

## 7. Archivo `validaciones.h`

Este archivo contiene funciones para leer datos de forma segura.

Algunas validaciones importantes son:

- Leer solo enteros.
- Leer numeros decimales.
- Leer nombres de productos.
- Controlar textos de maximo 30 caracteres.
- Evitar que queden caracteres sobrantes en el buffer.

Por ejemplo:

```c
leerEntero("Seleccione una opcion: ", 1, 6);
```

obliga a ingresar un entero entre `1` y `6`.

La funcion:

```c
leerNombreProducto(...)
```

controla que el nombre del producto tenga entre 1 y 30 caracteres.

---

## 8. Uso de punteros en el proyecto

El proyecto usa punteros de varias formas:

### 8.1 Para modificar valores originales

Ejemplo:

```c
ingresarProductos(&totalProductos, ...);
```

Se envia la direccion de `totalProductos` porque la funcion debe cambiar su valor.

Dentro de la funcion se modifica con:

```c
*totalProductos = leerEntero(...);
```

### 8.2 Para recorrer arreglos

Ejemplo:

```c
demandaActual++;
tiempoActual++;
```

Esto mueve el puntero a la siguiente posicion del arreglo.

### 8.3 Para acceder a una posicion especifica

Ejemplo:

```c
int *demandaProducto = demandas + indice;
```

Si `indice` vale `3`, el puntero apunta a la cuarta posicion del arreglo.

### 8.4 Para manejar matrices de caracteres

El arreglo de nombres es una matriz:

```c
char nombres[5][31];
```

Por eso se usa:

```c
char (*ptrNombres)[TAM_NOMBRE_PRODUCTO]
```

Este tipo significa:

```text
puntero a un arreglo de caracteres de tamano TAM_NOMBRE_PRODUCTO
```

---

## 9. Como compilar el proyecto

Desde la carpeta donde esta el proyecto, se puede compilar con:

```bash
gcc .\proyecto_headers\mainp.c .\proyecto_headers\funciones.c -o .\proyecto_headers\proyecto.exe
```

Para compilar mostrando advertencias:

```bash
gcc -Wall -Wextra .\proyecto_headers\mainp.c .\proyecto_headers\funciones.c -o .\proyecto_headers\proyecto.exe
```

---

## 10. Como ejecutar el programa

Luego de compilar, se ejecuta:

```bash
.\proyecto_headers\proyecto.exe
```

El programa mostrara el menu principal.

---

## 11. Flujo recomendado de uso

1. Seleccionar `1. Ingresar productos`.
2. Registrar los datos de los productos.
3. Seleccionar `2. Mostrar productos` para revisar la informacion.
4. Si hay un error, usar `3. Editar producto`.
5. Si se desea quitar un producto, usar `4. Eliminar producto`.
6. Seleccionar `5. Analizar produccion`.
7. Ingresar tiempo disponible y recursos disponibles.
8. Revisar si la fabrica puede cumplir la demanda.
9. Seleccionar `6. Salir`.

---

## 12. Resumen del funcionamiento

El programa guarda los productos en arreglos paralelos. `mainp.c` se encarga de controlar el menu y llamar a las funciones necesarias. `funciones.c` contiene la logica para registrar, mostrar, buscar, editar, eliminar y analizar los productos. `validaciones.h` protege las entradas del usuario para evitar datos incorrectos.

El uso de direcciones de memoria permite que las funciones modifiquen directamente los arreglos originales y recorran la informacion de manera mas tecnica, cumpliendo con el enfoque solicitado para el proyecto.
