//Génesis Barreiro y Sophia Pérez
#include <stdio.h>

//ESTUDIANTES: 5
//ASIGNATURAS: 3
//APROBADO: 6.0

int main() {
    float notas[5][3];
    float promEst[5];
    float promAsig[3];
    float mayorEst[5], menorEst[5];
    float mayorAsig[3], menorAsig[3];
    int aprobados[3], reprobados[3];
    int opcion;
    int i, j;

    do {
        printf("\nMENU\n");
        printf("1. Ingresar notas\n");
        printf("2. Mostrar resultados\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {

            case 1:
                for (i = 0; i < 5; i++) {
                    printf("\nEstudiante %d\n", i + 1);
                    for (j = 0; j < 3; j++) {
                        do {
                            printf("Ingresa nota de asignatura %d: ", j + 1);
                            if (scanf("%f", &notas[i][j]) != 1) {  //scanf devuelve el 1 si leyó el número, 0 si leyó letras.
                                printf("Error: ingresa solo numeros.\n");
                                while (getchar() != '\n'); // limpia buffer
                                notas[i][j] = -1;
                            } else if (notas[i][j] < 0 || notas[i][j] > 10 ) {
                                printf("Error: nota inválida.\n");
                            }
                        } while (notas[i][j] < 0 || notas[i][j] > 10);
                    }
                }
                printf("\nNotas registradas correctamente.\n");
                break;

            case 2:
                // Aquí inicializamos promedios y contadores
                for (i = 0; i < 5; i++) {
                    mayorEst[i] = notas[i][0];
                    menorEst[i] = notas[i][0];
                }
                for (j = 0; j < 3; j++) {
                    mayorAsig[j] = notas[0][j];
                    menorAsig[j] = notas[0][j];
                    aprobados[j] = 0;
                    reprobados[j] = 0;
                }

                // Calculamos promedios por estudiante
                for (i = 0; i < 5; i++) {
                    float suma = 0;
                    for (j = 0; j < 3; j++) {
                        suma += notas[i][j];
                        if (notas[i][j] > mayorEst[i]) mayorEst[i] = notas[i][j];
                        if (notas[i][j] < menorEst[i]) menorEst[i] = notas[i][j];
                    }
                    promEst[i] = suma / 3;
                }

                // Calculamos promedios por asignatura
                for (j = 0; j < 3; j++) {
                    float suma = 0;
                    for (i = 0; i < 5; i++) {
                        suma += notas[i][j];
                        if (notas[i][j] > mayorAsig[j]) mayorAsig[j] = notas[i][j];
                        if (notas[i][j] < menorAsig[j]) menorAsig[j] = notas[i][j];

                        if (notas[i][j] >= 6.0)
                            aprobados[j]++;
                        else
                            reprobados[j]++;
                    }
                    promAsig[j] = suma / 5;
                }

                // Mostrar resultados
                printf("\nPromedios por estudiante\n");
                for (i = 0; i < 5; i++) {
                    printf("Estudiante %d: Su promedio es: %.2f | Nota mas alta: %.2f | Nota mas baja: %.2f\n",
                           i + 1, promEst[i], mayorEst[i], menorEst[i]);
                }

                printf("\nPromedios por asignatura\n");
                for (j = 0; j < 3; j++) {
                    printf("Asignatura %d: Promedio: %.2f | Nota mas alta: %.2f | Nota mas baja: %.2f | Aprobados: %d y Reprobados: %d\n",
                           j + 1, promAsig[j], mayorAsig[j], menorAsig[j], aprobados[j], reprobados[j]);
                }

                break;

            case 3:
                printf("\nSaliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 3);

    return 0;
}