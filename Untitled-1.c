#include <stdio.h>
#include <string.h>
#include "empleados.h"
float calcularSueldoTotal(Empleado e)
{
    float sueldoTotal = e.sueldoBase + (e.horasExtra * 3.02); // asumiendo $3.02 por hora extra
    return sueldoTotal;
}
