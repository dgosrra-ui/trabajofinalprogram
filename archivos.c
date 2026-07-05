#include <stdio.h>
#include <string.h>
#include "empleados.h"

void guardarArchivo(Empleado empleados[], int cantidad) {
    FILE *archivo = fopen("empleados.csv", "w");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para guardar.\n");
        return;
    }
    
    fprintf(archivo, "codigo,nombre,cargo,sueldoBase,horasExtra\n");
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s,%s,%s,%.2f,%d\n", 
                empleados[i].codigo, empleados[i].nombre, empleados[i].cargo,
                empleados[i].sueldoBase, empleados[i].horasExtra);
    }
    fclose(archivo);
    printf("Datos guardados en empleados.csv\n");
}

int cargarArchivo(Empleado empleados[]) {
    FILE *archivo = fopen("empleados.csv", "r");
    if (archivo == NULL) {
        printf("Archivo no encontrado. Iniciando con datos vacios.\n");
        return 0;
    }
    
    char linea[200];
    int cantidad = 0;
    fgets(linea, sizeof(linea), archivo);
    
    while (fgets(linea, sizeof(linea), archivo) != NULL && cantidad < MAX_EMPLEADOS) {
        sscanf(linea, "%[^,],%[^,],%[^,],%f,%d",
               empleados[cantidad].codigo, empleados[cantidad].nombre, empleados[cantidad].cargo,
               &empleados[cantidad].sueldoBase, &empleados[cantidad].horasExtra);
        cantidad++;
    }
    fclose(archivo);
    return cantidad;
}
