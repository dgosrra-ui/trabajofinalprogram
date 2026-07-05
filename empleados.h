#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#define MAX_EMPLEADOS 100

typedef struct{
    char codigo[16];
    char nombre[50];
    char cargo[50];
    float sueldoBase;
    int horasExtra;
}Empleado;

float calcularSueldoTotal(Empleado e);

void listarEmpleados(Empleado empleados[], int cantidad);

int eliminarEmpleado(Empleado empleados[], int *cantidad, char codigo[]);


void menuPrincipal(Empleado empleados[], int *cantidad);
void registrarEmpleado(Empleado empleados[], int *cantidad);
void buscarEmpleado(Empleado empleados[], int cantidad);
void actualizarEmpleado(Empleado empleados[], int cantidad);

// Funciones para cumplir con el requisito de "Validaciones"
void limpiarSaltoLinea(char *cadena);
int esCodigoUnico(Empleado empleados[], int cantidad, const char *codigo);
int esAlfanumericoSinEspacios(const char *cadena);

#endif