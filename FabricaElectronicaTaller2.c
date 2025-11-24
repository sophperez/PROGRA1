#include <stdio.h>

#define MAX 50
#define TAM 50

// Cadena con punteros 
void copiar(char *destino, char *origen) {
    while (*origen != '\0') {
        *destino = *origen;
        destino++;
        origen++;
    }
    *destino = '\0';
}

// Comparar cadenas con punteros
// Devuelve 1 si son iguales, 0 si son diferentes
int iguales(char *a, char *b) {
    while (*a != '\0' || *b != '\0') {
        if (*a != *b) return 0;
        a++;
        b++;
    }
    return 1;
}

//Aquí se valida que el nombre solo tenga letras
void ingresarNombre(char texto[]) {
    int valido;

    do {
        valido = 1;
        printf("Ingrese el nombre (solo letras): ");
        scanf("%s", texto);

        for (int i = 0; texto[i] != '\0'; i++) {
            char c = texto[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
                printf("Error: el nombre solo puede tener letras.\n");
                valido = 0;
                break;
            }
        }

    } while (!valido);
}

//Valida entero positivo
int ingresarEnteroPositivo(char mensaje[]) {
    int valor;
    int leido;

    do {
        printf("%s (entero positivo): ", mensaje);
        leido = scanf("%d", &valor);

        if (leido != 1) {
            printf("Error: debe ingresar números, no letras.\n");
        } else if (valor < 0) {
            printf("Error: el número no puede ser negativo.\n");
        }

        while (getchar() != '\n'); // limpiar basura del teclado

    } while (leido != 1 || valor < 0);

    return valor;
}

//Valida flotante positivo
float ingresarFlotantePositivo(char mensaje[]) {
    float valor;
    int leido;

    do {
        printf("%s (mayor o igual a 0): ", mensaje);
        leido = scanf("%f", &valor);

        if (leido != 1) {
            printf("Error: ingrese un número válido.\n");
        } else if (valor < 0) {
            printf("Error: el número no puede ser negativo.\n");
        }

        while (getchar() != '\n');

    } while (leido != 1 || valor < 0);

    return valor;
}

// Buscar producto por nombre usando punteros a arreglo
int buscar(char (*nombres)[TAM], int cantidadProductos, char *nombreBuscado) {
    for (int i = 0; i < cantidadProductos; i++) {
        if (iguales(*(nombres + i), nombreBuscado)) {
            return i;
        }
    }
    return -1;
}

//Programa principal

int main() {

    char nombres[MAX][TAM];
    int cantidad[MAX];
    float tiempo[MAX];
    float recurso[MAX];
    int totalProductos = 0;

    int opcion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Agregar producto\n");
        printf("2. Listar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular total y verificar\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        while(getchar()!='\n');

        if (opcion == 1) {
            ingresarNombre(nombres[totalProductos]);
            cantidad[totalProductos] = ingresarEnteroPositivo("Cantidad");
            tiempo[totalProductos]   = ingresarFlotantePositivo("Tiempo por unidad");
            recurso[totalProductos]  = ingresarFlotantePositivo("Recurso por unidad");

            totalProductos++;
            printf("Producto agregado.\n");
        }

        else if (opcion == 2) {
            printf("\nLISTA DE PRODUCTOS\n");

            if (totalProductos == 0) {
                printf("No hay productos registrados.\n");
            } else {
                for (int i = 0; i < totalProductos; i++) {
                    printf("%d) %s - Cant: %d - Tiempo/u: %.2f - Recurso/u: %.2f\n",
                        i+1, nombres[i], cantidad[i], tiempo[i], recurso[i]);
                }
            }
        }

        else if (opcion == 3) {
            char nombreBuscado[TAM];
            printf("\nNombre del producto a editar: ");
            scanf("%s", nombreBuscado);

            int indice = buscar(nombres, totalProductos, nombreBuscado);

            if (indice == -1) {
                printf("Error: el producto no existe.\n");
            } else {

                ingresarNombre(nombres[indice]);
                cantidad[indice] = ingresarEnteroPositivo("Nueva cantidad");
                tiempo[indice]   = ingresarFlotantePositivo("Nuevo tiempo por unidad");
                recurso[indice]  = ingresarFlotantePositivo("Nuevo recurso por unidad");

                printf("Producto editado.\n");
            }
        }

        else if (opcion == 4) {
            char nombreBuscado[TAM];
            printf("\nNombre del producto a eliminar: ");
            scanf("%s", nombreBuscado);

            int indice = buscar(nombres, totalProductos, nombreBuscado);

            if (indice == -1) {
                printf("Error: ese producto no existe.\n");
            } else {

                for (int i = indice; i < totalProductos - 1; i++) {
                    copiar(nombres[i], nombres[i+1]);
                    cantidad[i] = cantidad[i+1];
                    tiempo[i] = tiempo[i+1];
                    recurso[i] = recurso[i+1];
                }

                totalProductos--;
                printf("Producto eliminado.\n");
            }
        }

        else if (opcion == 5) {
            float totalTiempo = 0, totalRecurso = 0;

            for (int i = 0; i < totalProductos; i++) {
                totalTiempo += cantidad[i] * tiempo[i];
                totalRecurso += cantidad[i] * recurso[i];
            }

            printf("\nTiempo total requerido: %.2f\n", totalTiempo);
            printf("Recurso total requerido: %.2f\n", totalRecurso);

            float tiempoDisponible  = ingresarFlotantePositivo("Tiempo disponible");
            float recursoDisponible = ingresarFlotantePositivo("Recurso disponible");

            if (totalTiempo <= tiempoDisponible && totalRecurso <= recursoDisponible) {
                printf("\n✔ Sí se puede cumplir con la producción.\n");
            } else {
                printf("\n✘ No se puede cumplir, faltan recursos o tiempo.\n");
            }
        }

    } while (opcion != 6);

    printf("Saliendo...\n");

    return 0;
}