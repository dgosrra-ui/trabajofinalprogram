#include <stdio.h>
#include <string.h>
#include "empleados.h"
#include "archivos.h"
void menuPrincipal(Empleado empleados[], int *cantidad) {
    int opcion = 0;

    do {
        printf("\n=========================================\n");
        printf("    SISTEMA DE GESTION DE EMPLEADOS      \n");
        printf("=========================================\n");
        printf("1. Registrar Empleado\n");
        printf("2. Listar Empleados\n");
        printf("3. Buscar Empleado\n");
        printf("4. Actualizar Empleado\n");
        printf("5. Eliminar Empleado\n");
        printf("6. Guardar Cambios en Archivo\n");
        printf("7. Salir\n");
        printf("=========================================\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf(" Entrada invalida. Por favor, ingrese un numero entero.\n");
            opcion = 0;
        }
        char c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch(opcion) {
            case 1:
                registrarEmpleado(empleados, cantidad);
                break;
            case 2:
                listarEmpleados(empleados, *cantidad); 
                break;
            case 3:
                buscarEmpleado(empleados, *cantidad); 
                break;
            case 4:
                actualizarEmpleado(empleados, *cantidad); 
                break;
            case 5: {
                    char codEliminar[16];
                    printf("\nIngrese el codigo del empleado a eliminar: ");
                    fgets(codEliminar, sizeof(codEliminar), stdin);
                    limpiarSaltoLinea(codEliminar);
                    eliminarEmpleado(empleados, cantidad, codEliminar);
                }
                break;
            case 6:
                guardarEnArchivo(empleados, *cantidad);
                break;
            case 7:
                printf("\nGuardando automaticamente en 'empleados.csv' y saliendo...\n");
                guardarEnArchivo(empleados, *cantidad);
                printf(" Sistema cerrado correctamente!\n");
                break;
            default:
                if (opcion != 0) {
                    printf(" Opcion no valida. Intente de nuevo.\n");
                }
        }
    } while(opcion != 7);
}

int main() {
    Empleado empleados[MAX_EMPLEADOS];
    int cantidad = 0;
    cargarDesdeArchivo(empleados, &cantidad);
    menuPrincipal(empleados, &cantidad);
    return 0;
}