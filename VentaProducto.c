// Génesis Barreiro y Sophia Pérez
#include <stdio.h>

int main() {
    int id, stock, opcion, unidades, agregar;
    float precio, descuento, precioFinal, totalVenta, ganancias = 0;
    int ventas[100];      // unidades vendidas
    float totales[100];   // total de cada venta
    int numVentas = 0;    // contador de ventas
    char nombre[50];  // 50 espacios para escribir el nombre

    printf("Sistema de ventas de un producto\n");

    printf("Ingrese el ID del producto: ");
    scanf("%d", &id);

    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]", nombre);   // para q acepte un espacio (Ej. leche de soya)

    printf("Ingrese la cantidad en stock: ");
    scanf("%d", &stock);

    printf("Ingrese el precio unitario: ");
    scanf("%f", &precio);

    do {
        printf("\nMENU\n");
        printf("1.Vender producto\n");
        printf("2.Reabastecer stock\n");
        printf("3.Consultar producto\n");
        printf("4.Ver ganancias\n");
        printf("5.Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (stock <= 0) {
                    printf("No hay stock disponible.\n");
                } else {
                    printf("Ingrese la cantidad a vender: ");
                    scanf("%d", &unidades);

                    if (unidades > stock) {
                        printf("No puede vender más de lo disponible (%d).\n", stock);
                    } else if (unidades <= 0) {
                        printf("Cantidad inválida.\n");
                    } else {
                        printf("Ingrese el descuento (0 a 100): ");
                        scanf("%f", &descuento);

                        if (descuento < 0 || descuento > 100) {
                            printf("Descuento inválido.\n");
                        } else {
                            precioFinal = precio - (precio * descuento / 100);
                            totalVenta = precioFinal * unidades;
                            stock -= unidades; // se resta al stock las unidades vendidas
                            ganancias += totalVenta; // se suma el dinero de la venta a las ganancias

                            ventas[numVentas] = unidades; //guarda en el arreglo la cantidad de unidades que se vendieron
                            totales[numVentas] = totalVenta; //guarda en el arreglo el dinero de la venta
                            numVentas++; // Aumenta el contador de ventas

                            printf("Venta realizada con éxito.\n");
                            printf("Total vendido: $%.2f\n", totalVenta);
                            printf("Stock restante: %d\n", stock);
                        }
                    }
                }
                break;

            case 2:
                printf("Ingrese la cantidad a agregar al stock: ");
                scanf("%d", &agregar);
                if (agregar > 0) {
                    stock += agregar;
                    printf("Stock actualizado: %d\n", stock);
                } else {
                    printf("Cantidad inválida.\n");
                }
                break;

            case 3:
                printf("\nInformacion del producto\n");
                printf("ID: %d\n", id);
                printf("Nombre: %s\n", nombre);
                printf("Precio unitario: %.2f\n", precio);
                printf("Stock actual: %d\n", stock);
                printf("Ganancias: %.2f\n", ganancias);
                printf("Número de ventas: %d\n", numVentas);
                break;

            case 4:
                printf("\nHistorial de ventas\n");
                if (numVentas == 0) {
                    printf("Aún no hay ventas.\n");
                } else {
                    for (int i = 0; i < numVentas; i++) {
                        printf("Venta %d: %d unidades y Total: $%.2f\n",
                               i + 1, ventas[i], totales[i]);
                    }
                }
                printf("Ganancia total: %.2f\n", ganancias);
                break;

            case 5:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 5);

    printf("\nInformación final\n");
    printf("Producto: %s (ID %d)\n", nombre, id);
    printf("Unidades vendidas: %d\n", numVentas);
    printf("Ganancia total: %.2f\n", ganancias);
    printf("Stock final: %d\n", stock);
    
    return 0;
}