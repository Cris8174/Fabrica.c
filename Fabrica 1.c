#include <stdio.h>
#include "FuncionesFabrica.h"

int main() {
    char nombres[5][60];
    float datos[5][5]; 
    float recursos[4] = {0,0,0,0};
    int opcion = 0;
    int num_p = 0;
do {
    menu_principal(&opcion);
    switch (opcion) {
        case 1: ingresar_productos(nombres, datos, &num_p); break;
        case 2: ver_productos_agregados(nombres, datos, num_p); break;
        case 3: editar_producto(nombres, datos, num_p); break;
        case 4: eliminar_producto(nombres, datos, &num_p); break;
        case 5: gestionar_recursos_fabrica(recursos); break;
        case 6: analizar_demanda_y_factibilidad(nombres, datos, num_p, recursos); break;
        case 7: configurar_capacidad_tiempo(recursos); break;
        }
    } while (opcion != 8);
    return 0;
}