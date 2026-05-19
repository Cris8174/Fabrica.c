#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include "FuncionesFabrica.h"

void menu_principal(int *op) {
    printf(Amarillo Negrita "\n--- Sistema de produccion electronica ---\n\n" Reset);
    printf(Cyan "1. Ingresar Productos\n" Reset);
    printf(Cyan "2. Ver Productos Agregados\n" Reset);
    printf(Cyan "3. Editar Producto (Busqueda)\n" Reset);
    printf(Cyan "4. Eliminar Producto\n" Reset);
    printf(Cyan "5. Ingresar Inventario de Materiales\n" Reset);
    printf(Cyan "6. Analizar Demanda y Factibilidad\n" Reset);
    printf(Cyan "7. Configurar Capacidad (Horas)\n" Reset);
    printf(Rojo "8. Salir\n" Reset);
    printf("\nSeleccione una opcion: ");
    
    if (scanf("%d", op) != 1) {
        printf(Rojo "\nError: Ingrese un numero valido.\n" Reset);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        *op = 0; 
    }
}

int comparar_nombres(char *busqueda, char *existente) {
    int coincidencias = 0;
    int len1 = strlen(busqueda);
    int len2 = strlen(existente);
    
    if (len1 == 0) return 0;

    for (int i = 0; i < len1 && i < len2; i++) {
        if (tolower(busqueda[i]) == tolower(existente[i])) {
            coincidencias++;
        }
    }
    
    if (coincidencias >= (len1 * 0.7)) {
        return 1;
    }
    return 0;
}

void buscar_producto(char nombres[5][60], int num_p, int *posicion) {
    char termino[60];
    printf(Amarillo "\n--- Busqueda de producto ---\n" Reset);
    printf("Ingrese el nombre del producto a buscar: ");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    fgets(termino, 60, stdin);
    termino[strcspn(termino, "\n")] = 0;

    *posicion = -1;
    for (int i = 0; i < num_p; i++) {
        if (comparar_nombres(termino, nombres[i])) {
            *posicion = i;
            printf(Verde "Producto encontrado: %s\n" Reset, nombres[i]);
            return;
        }
    }
    printf(Rojo "No se encontro ningun producto similar a '%s'.\n" Reset, termino);
}

void ingresar_productos(char nombres[5][60], float datos[5][5], int *num_p) {
    if (*num_p >= 5) {
        printf(Rojo "\n Limite de 5 productos alcanzado.\n" Reset);
        return;
    }
    int i = *num_p;
    printf(Amarillo "\n--- Registro de Nuevo producto ---\n" Reset);
    
    printf("Ingresar nombre del producto: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(nombres[i], 60, stdin);
    nombres[i][strcspn(nombres[i], "\n")] = 0;
    
    printf("Tiempo de fabricacion (horas): "); scanf("%f", &datos[i][0]);
    printf("Cantidad de Metales: "); scanf("%f", &datos[i][1]);
    printf("Cantidad de Plasticos: "); scanf("%f", &datos[i][2]);
    printf("Cantidad de Componentes electronicos: "); scanf("%f", &datos[i][3]);
    
    (*num_p)++;
    printf(Verde "\n Producto '%s' guardado con exito.\n" Reset, nombres[i]);
}

void eliminar_producto(char nombres[5][60], float datos[5][5], int *num_p) {
    int posicion;
    char respuesta[10]; 
    int entrada_valida = 0;

    buscar_producto(nombres, *num_p, &posicion);

    if (posicion != -1) {
        printf(Verde "\nResultado: %s encontrado.\n" Reset, nombres[posicion]);
        
        // Bucle de validación de respuesta
        do {
            printf(Amarillo "¿Esta seguro que desea eliminar este producto? (si/no): " Reset);
            scanf("%s", respuesta);

            // Convertir respuesta a minusculas para comparar
            for(int i = 0; respuesta[i]; i++) {
                respuesta[i] = tolower(respuesta[i]);
            }

            if (strcmp(respuesta, "si") == 0) {
                // Lógica de eliminación (desplazar elementos)
                for (int i = posicion; i < (*num_p) - 1; i++) {
                    strcpy(nombres[i], nombres[i+1]);
                    for (int j = 0; j < 5; j++) datos[i][j] = datos[i+1][j];
                }
                (*num_p)--; 
                printf(Verde "\nProducto eliminado correctamente.\n" Reset);
                entrada_valida = 1;
            } 
            else if (strcmp(respuesta, "no") == 0) {
                printf(Cyan "\nOperacion cancelada.\n" Reset);
                entrada_valida = 1;
            } 
            else {
                printf(Rojo "Error: Por favor responda unicamente 'si' o 'no'.\n" Reset);
            }
        } while (!entrada_valida);
    }
}

void ver_productos_agregados(char nombres[5][60], float datos[5][5], int num_p) {
    if (num_p == 0) {
        printf(Rojo "\nNo hay productos registrados.\n" Reset);
        return;
    }
    printf(Amarillo "\n--- Lista de productos ---\n" Reset);
    for (int i = 0; i < num_p; i++) {
        printf(Cyan "\nID: %d | Producto: %s\n" Reset, i+1, nombres[i]);
        printf(" -> Horas: %.1f | Metales: %.1f | Plasticos: %.1f | Comp: %.1f\n", 
                datos[i][0], datos[i][1], datos[i][2], datos[i][3]);
    }
}

void editar_producto(char nombres[5][60], float datos[5][5], int num_p) {
    int posicion, campo;
    buscar_producto(nombres, num_p, &posicion);
    if (posicion != -1) {
        printf(Amarillo "\n1.Horas | 2.Metales | 3.Plasticos | 4.Componentes\n" Reset);
        printf("Seleccione que dato cambiar: ");
        scanf("%d", &campo);
        if (campo >= 1 && campo <= 4) {
            printf("Nuevo valor: ");
            scanf("%f", &datos[posicion][campo-1]);
            printf(Verde "\nDatos actualizados.\n" Reset);
        }
    }
}

void gestionar_recursos_fabrica(float *recursos) {
    printf(Amarillo "\n--- Inventario Actual ---\n" Reset);
    printf("Metales: %.1f | Plasticos: %.1f | Componentes: %.1f\n", recursos[1], recursos[2], recursos[3]);
    
    printf(Amarillo "\n--- Ingresar Nuevo Inventario ---\n" Reset);
    printf("Nuevos Metales: "); scanf("%f", &recursos[1]);
    printf("Nuevos Plasticos: "); scanf("%f", &recursos[2]);
    printf("Nuevos Componentes: "); scanf("%f", &recursos[3]);
    printf(Verde "\nInventario actualizado.\n" Reset);
}

void analizar_demanda_y_factibilidad(char nombres[5][60], float datos[5][5], int num_p, float *recursos) {
    if (num_p == 0) {
        printf(Rojo "\n No hay productos para analizar.\n" Reset);
        return;
    }

    if (recursos[0] <= 0) {
        printf(Rojo "\n Error: Debe configurar la capacidad diaria (horas/dia) primero.\n" Reset);
        return;
    }

    float gasto[4] = {0,0,0,0};
    int orden[5];
    for(int i=0; i<num_p; i++) orden[i] = i;

    printf(Amarillo "\n--- Analisis de Demanda ---\n" Reset);
    for (int i = 0; i < num_p; i++) {
        float cant;
        printf("¿Unidades de '%s'?: ", nombres[i]);
        scanf("%f", &cant);
        gasto[0] += datos[i][0] * cant; 
        gasto[1] += datos[i][1] * cant; 
        gasto[2] += datos[i][2] * cant; 
        gasto[3] += datos[i][3] * cant; 
    }

    float dias_necesarios = gasto[0] / recursos[0];

    printf(Cyan "\n--- Recursos Totales Necesarios ---\n" Reset);
    printf("Horas totales: %.1f h\n", gasto[0]);
    printf("Tiempo estimado: " Amarillo "%.2f dias" Reset " (trabajando %.1f h/dia)\n", dias_necesarios, recursos[0]);
    printf("Metales totales: %.1f\n", gasto[1]);
    printf("Plasticos totales: %.1f\n", gasto[2]);
    printf("Componentes totales: %.1f\n", gasto[3]);

    for (int i = 0; i < num_p - 1; i++) {
        for (int j = 0; j < num_p - i - 1; j++) {
            if (datos[orden[j]][0] > datos[orden[j+1]][0]) {
                int temp = orden[j];
                orden[j] = orden[j+1];
                orden[j+1] = temp;
            }
        }
    }

    printf(Cyan "\n--- Prioridad sugerida ---\n" Reset);
    for(int i=0; i<num_p; i++) {
        printf("%d. %s (%.1f h)\n", i+1, nombres[orden[i]], datos[orden[i]][0]);
    }

    if (gasto[1] <= recursos[1] && gasto[2] <= recursos[2] && gasto[3] <= recursos[3]) {
        printf(Verde Negrita "\nESTADO: PRODUCCION FACTIBLE\n" Reset);
        printf("La fabrica terminara el pedido en %.2f dias.\n", dias_necesarios);
    } else {
        printf(Rojo Negrita "\nESTADO: RECURSOS INSUFICIENTES (Materiales)\n" Reset);
        if (gasto[1] > recursos[1]) printf(" -> Metales: falta %.1f\n", gasto[1] - recursos[1]);
        if (gasto[2] > recursos[2]) printf(" -> Plasticos: falta %.1f\n", gasto[2] - recursos[2]);
        if (gasto[3] > recursos[3]) printf(" -> Componentes: falta %.1f\n", gasto[3] - recursos[3]);
        printf(Amarillo "Nota: Aunque faltan materiales, el tiempo de trabajo seria de %.2f dias.\n" Reset, dias_necesarios);
    }
}

void configurar_capacidad_tiempo(float *recursos) {
    printf(Amarillo "\n--- Configuracion de Capacidad Diaria ---\n" Reset);
    printf("Capacidad actual: %.1f horas/dia\n", recursos[0]);
    printf("Ingrese las horas laborables por dia: ");
    scanf("%f", &recursos[0]);
    
    if (recursos[0] > 24) {
        printf(Rojo "Advertencia: Un dia no puede tener mas de 24 horas. Ajustado a 24.\n" Reset);
        recursos[0] = 24;
    }
    printf(Verde "\nCapacidad diaria actualizada con exito.\n" Reset);
}