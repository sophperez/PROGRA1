#include <stdio.h>

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
float tiempoFabricacion[MAX_PRODUCTOS];
float recursosNecesarios[MAX_PRODUCTOS];
int cantidadDemandada[MAX_PRODUCTOS];
int totalProductos = 5;

// Recursos y tiempo disponibles en la fábrica
float tiempoDisponible = 1000.0;
float recursosDisponibles = 4000.0;

//Funciones
int esTextoValido(char *texto);
void limpiarBuffer();
void leerTextoValidado(char *destino, char *mensaje);
int leerEnteroPositivo(char *mensaje);
float leerFlotantePositivo(char *mensaje);

void copiarCadena(char *destino, char *origen);
int compararCadenas(char *cad1, char *cad2);
int buscarProducto(char *nombreBuscado);

void inicializarInventario();
void mostrarInventario();
void editarProducto();
void eliminarProducto();
void ingresarDemanda();
void verificarProduccion();

int main() {
    int opcion;
    inicializarInventario();
    
    printf("SISTEMA DE OPTIMIZACION DE PRODUCCION\n");
    printf("Fabrica de Componentes Electronicos\n");
    
    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Mostrar inventario de productos\n");
        printf("2. Ingresar demanda de producto\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Verificar si se puede cumplir la demanda\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        
        switch(opcion) {
            case 1:
                mostrarInventario();
                break;
            case 2:
                ingresarDemanda();
                break;
            case 3:
                editarProducto();
                break;
            case 4:
                eliminarProducto();
                break;
            case 5:
                verificarProduccion();
                break;
            case 6:
                printf("\nSaliendo del sistema.\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }
        
    } while(opcion != 6);
    
    return 0;
}

// Función para validar que solo contenga letras
int esTextoValido(char *texto) {
    int i = 0;
    int tieneCaracter = 0;
    
    while (texto[i] != '\0') {
        tieneCaracter = 1;
        if (!((texto[i] >= 'A' && texto[i] <= 'Z') || 
              (texto[i] >= 'a' && texto[i] <= 'z') || 
              texto[i] == ' ')) {
            return 0; // No es válido
        }
        i++;
    }
    return tieneCaracter; // Retorna 1 si tiene al menos un carácter
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != -1);
}

// Función para leer texto validado
void leerTextoValidado(char *destino, char *mensaje) {
    int valido = 0;
    while (!valido) {
        printf("%s", mensaje);
        scanf("%[^\n]", destino);
        limpiarBuffer();
        
        if (esTextoValido(destino)) {
            valido = 1;
        } else {
            printf("Error. Intente nuevamente.\n");
        }
    }
}

// Función para validar y leer un número entero positivo
int leerEnteroPositivo(char *mensaje) {
    int numero;
    int valido = 0;
    
    while (!valido) {
        printf("%s", mensaje);
        if (scanf("%d", &numero) == 1 && numero >= 0) {
            valido = 1;
        } else {
            printf("Error: Debe ingresar un numero entero positivo.\n");
            limpiarBuffer();
        }
    }
    limpiarBuffer();
    return numero;
}

// Función para validar y leer un número flotante positivo
float leerFlotantePositivo(char *mensaje) {
    float numero;
    int valido = 0;
    
    while (!valido) {
        printf("%s", mensaje);
        if (scanf("%f", &numero) == 1 && numero > 0) {
            valido = 1;
        } else {
            printf("Error: Debe ingresar un numero positivo mayor que 0.\n");
            limpiarBuffer();
        }
    }
    limpiarBuffer();
    return numero;
}

// Función para copiar cadenas
void copiarCadena(char *destino, char *origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// Función para comparar cadenas, retorna 1 si son iguales
int compararCadenas(char *cad1, char *cad2) {
    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0') {
        // Comparar ignorando mayúsculas/minúsculas
        char c1 = cad1[i];
        char c2 = cad2[i];
        // Convertir a minúsculas si son mayúsculas
        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;
        
        if (c1 != c2) {
            return 0;
        }
        i++;
    }
    return (cad1[i] == '\0' && cad2[i] == '\0');
}

// Función para buscar un producto por nombre usando punteros
int buscarProducto(char *nombreBuscado) {
    int i;
    char *nombre;
    for (i = 0; i < totalProductos; i++) {
        nombre = nombres[i];
        if (compararCadenas(nombre, nombreBuscado)) {
            return i;
        }
    }
    return -1;
}

void inicializarInventario() {
    int i;
    
    // Producto 1: Laptop
    for (i = 0; i < MAX_NOMBRE; i++) nombres[0][i] = '\0';
    nombres[0][0] = 'L'; nombres[0][1] = 'a'; nombres[0][2] = 'p';
    nombres[0][3] = 't'; nombres[0][4] = 'o'; nombres[0][5] = 'p';
    tiempoFabricacion[0] = 5.0;
    recursosNecesarios[0] = 150.0;
    cantidadDemandada[0] = 0;
    
    // Producto 2: Mouse
    for (i = 0; i < MAX_NOMBRE; i++) nombres[1][i] = '\0';
    nombres[1][0] = 'M'; nombres[1][1] = 'o'; nombres[1][2] = 'u';
    nombres[1][3] = 's'; nombres[1][4] = 'e';
    tiempoFabricacion[1] = 1.5;
    recursosNecesarios[1] = 25.0;
    cantidadDemandada[1] = 0;
    
    // Producto 3: Teclado
    for (i = 0; i < MAX_NOMBRE; i++) nombres[2][i] = '\0';
    nombres[2][0] = 'T'; nombres[2][1] = 'e'; nombres[2][2] = 'c';
    nombres[2][3] = 'l'; nombres[2][4] = 'a'; nombres[2][5] = 'd';
    nombres[2][6] = 'o';
    tiempoFabricacion[2] = 2.0;
    recursosNecesarios[2] = 40.0;
    cantidadDemandada[2] = 0;
    
    // Producto 4: Flash
    for (i = 0; i < MAX_NOMBRE; i++) nombres[3][i] = '\0';
    nombres[3][0] = 'F'; nombres[3][1] = 'l'; nombres[3][2] = 'a';
    nombres[3][3] = 's'; nombres[3][4] = 'h';
    tiempoFabricacion[3] = 0.8;
    recursosNecesarios[3] = 10.0;
    cantidadDemandada[3] = 0;
    
    // Producto 5: Celular
    for (i = 0; i < MAX_NOMBRE; i++) nombres[4][i] = '\0';
    nombres[4][0] = 'C'; nombres[4][1] = 'e'; nombres[4][2] = 'l';
    nombres[4][3] = 'u'; nombres[4][4] = 'l'; nombres[4][5] = 'a';
    nombres[4][6] = 'r';
    tiempoFabricacion[4] = 4.0;
    recursosNecesarios[4] = 120.0;
    cantidadDemandada[4] = 0;
}

void mostrarInventario() {
    int i;
    char *nombre;
    float *tiempo = tiempoFabricacion;
    float *recursos = recursosNecesarios;
    int *demanda = cantidadDemandada;
    
    printf("\nINVENTARIO DE PRODUCTOS\n");
    for (i = 0; i < totalProductos; i++) {
        nombre = nombres[i];
        printf("\n%d. Producto: %s\n", i + 1, nombre);
        printf("Tiempo de fabricacion: %.2f horas\n", tiempo[i]);
        printf("Recursos necesarios: %.2f unidades\n", recursos[i]);
        printf("Cantidad demandada: %d unidades\n", demanda[i]);
    }
}

void editarProducto() {
    char nombreBuscar[MAX_NOMBRE];
    int indice, opcion;
    char *nombre;
    float *tiempo;
    float *recursos;
    int *demanda;
    
    leerTextoValidado(nombreBuscar, "\nIngrese el nombre del producto a editar: ");
    indice = buscarProducto(nombreBuscar);
    
    if (indice == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }
    
    nombre = nombres[indice];
    tiempo = &tiempoFabricacion[indice];
    recursos = &recursosNecesarios[indice];
    demanda = &cantidadDemandada[indice];
    
    printf("\nProducto encontrado: %s\n", nombre);
    printf("\nQue desea editar?\n");
    printf("1. Nombre del producto\n");
    printf("2. Tiempo de fabricacion\n");
    printf("3. Recursos necesarios\n");
    printf("4. Cantidad demandada\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    limpiarBuffer();
    
    if (opcion == 1) {
        leerTextoValidado(nombre, "Nuevo nombre: ");
        printf("Nombre actualizado correctamente.\n");
    } else if (opcion == 2) {
        *tiempo = leerFlotantePositivo("Nuevo tiempo de fabricacion (horas): ");
        printf("Tiempo actualizado correctamente.\n");
    } else if (opcion == 3) {
        *recursos = leerFlotantePositivo("Nuevos recursos necesarios: ");
        printf("Recursos actualizados correctamente.\n");
    } else if (opcion == 4) {
        *demanda = leerEnteroPositivo("Nueva cantidad demandada: ");
        printf("Cantidad actualizada correctamente.\n");
    } else {
        printf("Opcion invalida.\n");
    }
}

void eliminarProducto() {
    char nombreBuscar[MAX_NOMBRE];
    int indice, i;
    char *nombreOrigen, *nombreDestino;
    float *tiempo = tiempoFabricacion;
    float *recursos = recursosNecesarios;
    int *demanda = cantidadDemandada;
    
    leerTextoValidado(nombreBuscar, "\nIngrese el nombre del producto a eliminar: ");
    
    indice = buscarProducto(nombreBuscar);
    
    if (indice == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }
    
    printf("\nProducto '%s' eliminado\n", nombres[indice]);
    
    for (i = indice; i < totalProductos - 1; i++) {
        nombreDestino = nombres[i];
        nombreOrigen = nombres[i + 1];
        copiarCadena(nombreDestino, nombreOrigen);
        
        tiempo[i] = tiempo[i + 1];
        recursos[i] = recursos[i + 1];
        demanda[i] = demanda[i + 1];
    }
    
    totalProductos--;
    printf("Producto eliminado correctamente.\n");
}

void ingresarDemanda() {
    char nombreProducto[MAX_NOMBRE];
    int cantidad, indice;
    
    leerTextoValidado(nombreProducto, "\nIngrese el nombre del producto: ");
    
    indice = buscarProducto(nombreProducto);
    
    if (indice == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }
    
    cantidad = leerEnteroPositivo("Ingrese la cantidad demandada: ");
    
    cantidadDemandada[indice] = cantidad;
    printf("\nDemanda registrada correctamente para %s.\n", nombres[indice]);
}

void verificarProduccion() {
    float tiempoTotal = 0.0;
    float recursosTotal = 0.0;
    int i;
    int puedeCumplir = 1;
    float *tiempo = tiempoFabricacion;
    float *recursos = recursosNecesarios;
    int *demanda = cantidadDemandada;
    
    printf("\nANALISIS DE PRODUCCION\n");
    
    // Calcular totales
    for (i = 0; i < totalProductos; i++) {
        if (demanda[i] > 0) {
            float tiempoProducto = tiempo[i] * demanda[i];
            float recursosProducto = recursos[i] * demanda[i];
            
            tiempoTotal += tiempoProducto;
            recursosTotal += recursosProducto;
            
            printf("\n%s:\n", nombres[i]);
            printf("  Cantidad: %d unidades\n", demanda[i]);
            printf("  Tiempo requerido: %.2f horas\n", tiempoProducto);
            printf("  Recursos requeridos: %.2f unidades\n", recursosProducto);
        }
    }
    
    printf("\nTOTALES\n");
    printf("Tiempo total requerido: %.2f horas\n", tiempoTotal);
    printf("Tiempo disponible: %.2f horas\n", tiempoDisponible);
    printf("Recursos totales requeridos: %.2f unidades\n", recursosTotal);
    printf("Recursos disponibles: %.2f unidades\n", recursosDisponibles);
    
    // Verificar si se puede cumplir
    printf("\nRESULTADO\n");
    if (tiempoTotal > tiempoDisponible) {
        printf("No hay suficiente tiempo de produccion.\n");
        printf("Faltante: %.2f horas\n", tiempoTotal - tiempoDisponible);
        puedeCumplir = 0;
    }
    
    if (recursosTotal > recursosDisponibles) {
        printf("No hay suficientes recursos.\n");
        printf("Faltante: %.2f unidades\n", recursosTotal - recursosDisponibles);
        puedeCumplir = 0;
    }
    
    if (puedeCumplir) {
        printf("\nLa fabrica puede cumplir con la demanda!\n");
        printf("Tiempo sobrante: %.2f horas\n", tiempoDisponible - tiempoTotal);
        printf("Recursos sobrantes: %.2f unidades\n", recursosDisponibles - recursosTotal);
    } else {
        printf("\nLa fabrica no puede cumplir con la demanda\n");
    }
}