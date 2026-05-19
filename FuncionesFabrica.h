#ifndef FUNCIONESFABRICA_H
#define FUNCIONESFABRICA_H

#define Rojo     "\033[31m"
#define Verde    "\033[32m"
#define Amarillo "\033[33m"
#define Cyan     "\033[36m"
#define Reset    "\033[0m"
#define Negrita  "\033[1m"

void menu_principal(int *op);
void ingresar_productos(char nombres[5][60], float datos[5][5], int *num_p);
void ver_productos_agregados(char nombres[5][60], float datos[5][5], int num_p);
void editar_producto(char nombres[5][60], float datos[5][5], int num_p);
void eliminar_producto(char nombres[5][60], float datos[5][5], int *num_p);
void gestionar_recursos_fabrica(float *recursos);
void analizar_demanda_y_factibilidad(char nombres[5][60], float datos[5][5], int num_p, float *recursos);
void configurar_capacidad_tiempo(float *recursos);
int comparar_nombres(char *busqueda, char *existente);
void buscar_producto(char nombres[5][60], int num_p, int *posicion);

#endif