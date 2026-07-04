#include <stdio.h>
#include <string.h>
#include "empleados.h"
float calcularSueldoTotal(Empleado e)
{
    float sueldoTotal = e.sueldoBase + (e.horasExtra * 3.02); // asumiendo $3.02 por hora extra
    return sueldoTotal;
}
//funcion para listar empleados
void listarEmpleados(Empleado empleados[], int cantidad)
{
    printf("Listado de Empleados:\n");
    printf("Codigo\tNombre\tCargo\tSueldo Base\tHoras Extra\tSueldo Total\n");
    for(int i = 0; i < cantidad; i++)
    {
        float sueldoTotal = calcularSueldoTotal(empleados[i]);
        printf("%s\t%s\t%s\t%.2f\t%d\t%.2f\n", empleados[i].codigo, empleados[i].nombre, empleados[i].cargo, empleados[i].sueldoBase, empleados[i].horasExtra, sueldoTotal);
    }
}
