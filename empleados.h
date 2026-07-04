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

#endif